#include "stdafx.h"

using POINTER_TYPE = ULONGLONG;

void PELoader::VerifyPE()
{
	dosHeader = (PIMAGE_DOS_HEADER)(data);
	if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE)
		throw std::runtime_error("Invalid DOS Signature");

	old_header = (PIMAGE_NT_HEADERS)(&data[dosHeader->e_lfanew]);
	if (old_header->Signature != IMAGE_NT_SIGNATURE)
		throw std::runtime_error("Invalid NT Signature");

#if IS64BIT
	if (old_header->FileHeader.Machine == IMAGE_FILE_MACHINE_I386) {
		throw std::runtime_error("You cannot load a x32 executable into a x64 executable");
	}
#else
	if (old_header->FileHeader.Machine == IMAGE_FILE_MACHINE_AMD64) {
		throw std::runtime_error("You cannot load a x64 executable into a x32 executable");
	}
	else if (old_header->FileHeader.Machine != IMAGE_FILE_MACHINE_I386) {
		throw std::runtime_error("You can only load I386 executables");
	}
#endif
}

void PELoader::LoadHeaders()
{
	// Try to allocate the code
	unsigned char * code = (unsigned char *)VirtualAlloc((LPVOID)(old_header->OptionalHeader.ImageBase), old_header->OptionalHeader.SizeOfImage, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	
	if (code == NULL)
	{
		code = (unsigned char *)VirtualAlloc(NULL, old_header->OptionalHeader.SizeOfImage, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		if (code == NULL)
		{
			SetLastError(ERROR_OUTOFMEMORY);
			throw std::runtime_error("Out of memory");
		}
	}

	unsigned char * headers = (unsigned char *)VirtualAlloc(code, old_header->OptionalHeader.SizeOfHeaders, MEM_COMMIT, PAGE_READWRITE);

	memcpy(headers, data, old_header->OptionalHeader.SizeOfHeaders);

	result_headers = (PIMAGE_NT_HEADERS)&((const unsigned char *)(headers))[dosHeader->e_lfanew];
	result_headers->OptionalHeader.ImageBase = (POINTER_TYPE)code;
}

void PELoader::BuildIAT()
{
	//BuildImportTable
	PIMAGE_DATA_DIRECTORY directory = GetHeaderDictionary(IMAGE_DIRECTORY_ENTRY_IMPORT);

	if (directory->Size > 0)
	{
		PIMAGE_IMPORT_DESCRIPTOR importDesc = (PIMAGE_IMPORT_DESCRIPTOR)(result_headers->OptionalHeader.ImageBase + directory->VirtualAddress);
		for (; !IsBadReadPtr(importDesc, sizeof(IMAGE_IMPORT_DESCRIPTOR)) && importDesc->Name; importDesc++)
		{
			HMODULE handle = LoadLibraryA((LPCSTR)(result_headers->OptionalHeader.ImageBase + importDesc->Name));

			if (handle == NULL)
			{
				SetLastError(ERROR_MOD_NOT_FOUND);
				break;
			}

			POINTER_TYPE * thunkRef = (POINTER_TYPE *)(result_headers->OptionalHeader.ImageBase + importDesc->OriginalFirstThunk);
			FARPROC * funcRef = (FARPROC *)(result_headers->OptionalHeader.ImageBase + importDesc->FirstThunk);

			if (!importDesc->OriginalFirstThunk) // no hint table
				thunkRef = (POINTER_TYPE *)(result_headers->OptionalHeader.ImageBase + importDesc->FirstThunk);

			for (; *thunkRef, *funcRef; thunkRef++, funcRef++)
			{
				if (IMAGE_SNAP_BY_ORDINAL(*thunkRef))
					*funcRef = GetProcAddress(handle, (LPCSTR)IMAGE_ORDINAL(*thunkRef));
				else
					*funcRef = GetProcAddress(handle, (LPCSTR)&((PIMAGE_IMPORT_BY_NAME)(result_headers->OptionalHeader.ImageBase + (*thunkRef)))->Name);
			}
		}
	}
}

void PELoader::ApplyPermissions()
{
#ifdef _WIN64
	ULONGLONG imageOffset = (result_headers->OptionalHeader.ImageBase & 0xffffffff00000000);
#else
#define imageOffset 0
#endif
	auto section = IMAGE_FIRST_SECTION(result_headers);
	for (int i = 0; i < result_headers->FileHeader.NumberOfSections; i++, section++)
	{
		bool executable = (section->Characteristics & IMAGE_SCN_MEM_EXECUTE) != 0;
		bool readable = (section->Characteristics & IMAGE_SCN_MEM_READ) != 0;
		bool writeable = (section->Characteristics & IMAGE_SCN_MEM_WRITE) != 0;

		if (section->Characteristics & IMAGE_SCN_MEM_DISCARDABLE) // section is not needed any more and can safely be freed
		{
			VirtualFree((LPVOID)((POINTER_TYPE)section->Misc.PhysicalAddress | imageOffset), section->SizeOfRawData, MEM_DECOMMIT);
			continue;
		}

		DWORD protect = PAGE_NOACCESS;

		if (!executable)
			if (!readable)
				if (!writeable)
					protect = PAGE_NOACCESS;
				else
					protect = PAGE_WRITECOPY;
			else
				if (!writeable)
					protect = PAGE_READONLY;
				else
					protect = PAGE_READWRITE;
		else
			if (!readable)
				if (!writeable)
					protect = PAGE_EXECUTE;
				else
					protect = PAGE_EXECUTE_WRITECOPY;
			else
				if (!writeable)
					protect = PAGE_EXECUTE_READ;
				else
					protect = PAGE_EXECUTE_READWRITE;

		if (section->Characteristics & IMAGE_SCN_MEM_NOT_CACHED)
			protect |= PAGE_NOCACHE;

		DWORD size = section->SizeOfRawData;
		if (size == 0)
			if (section->Characteristics & IMAGE_SCN_CNT_INITIALIZED_DATA)
				size = result_headers->OptionalHeader.SizeOfInitializedData;
			else if (section->Characteristics & IMAGE_SCN_CNT_UNINITIALIZED_DATA)
				size = result_headers->OptionalHeader.SizeOfUninitializedData;

		if (size > 0 && VirtualProtect((LPVOID)((POINTER_TYPE)section->Misc.PhysicalAddress | imageOffset), size, protect, &protect) == 0)
			MessageBox(NULL, "Error protecting memory page", NULL, MB_OK);
	}
}

void PELoader::DoTLS()
{
	auto directory = GetHeaderDictionary(IMAGE_DIRECTORY_ENTRY_TLS);
	if (directory->VirtualAddress > 0)
	{
		PIMAGE_TLS_DIRECTORY tls = (PIMAGE_TLS_DIRECTORY)(result_headers->OptionalHeader.ImageBase + directory->VirtualAddress);
		PIMAGE_TLS_CALLBACK* callback = (PIMAGE_TLS_CALLBACK *)tls->AddressOfCallBacks;
		if (callback)
		{
			while (*callback)
			{
				(*callback)((LPVOID)result_headers->OptionalHeader.ImageBase, DLL_PROCESS_ATTACH, NULL);
				callback++;
			}
		}
	}
}

int PELoader::LoadFile(const char * filename)
{
	FILE* file = fopen(filename, "rb");

	if (!file)
	{
		MessageBox(NULL, "Failed to open remote executable.", NULL, MB_OK);
		return -1;
	}

	uint32_t length = 0;

	fseek(file, 0, SEEK_END);
	length = ftell(file);

	data = new uint8_t[length];

	fseek(file, 0, SEEK_SET);
	fread(data, 1, length, file);

	fclose(file);

	VerifyPE();
	LoadHeaders();
	LoadSections();
	Relocate();
	BuildIAT();
	ApplyPermissions();
	DoTLS();

	//utils::hooking::hooking_helpers::SetExecutableAddress(reinterpret_cast<uintptr_t>(result_headers) - dosHeader->e_lfanew);

	entryPoint = ((void(*)(void))(result_headers->OptionalHeader.ImageBase + result_headers->OptionalHeader.AddressOfEntryPoint));

	return 0;
}

void PELoader::LoadSections()
{
	PIMAGE_SECTION_HEADER section = IMAGE_FIRST_SECTION(result_headers);

	for (int i = 0; i < result_headers->FileHeader.NumberOfSections; i++, section++)
	{
		if (section->SizeOfRawData == 0)
		{
			if (result_headers->OptionalHeader.SectionAlignment > 0)
			{
				unsigned char * dest = static_cast<unsigned char *>(VirtualAlloc((LPVOID)(result_headers->OptionalHeader.ImageBase
					+ section->VirtualAddress), result_headers->OptionalHeader.SectionAlignment, MEM_COMMIT, PAGE_READWRITE));

				section->Misc.PhysicalAddress = (DWORD)(POINTER_TYPE)dest;

				memset(dest, 0, result_headers->OptionalHeader.SectionAlignment);
			}
		}
		else
		{
			unsigned char * dest = static_cast<unsigned char *>(VirtualAlloc((LPVOID)(result_headers->OptionalHeader.ImageBase + section->VirtualAddress),
				section->SizeOfRawData, MEM_COMMIT, PAGE_READWRITE));

			memcpy(dest, &data[section->PointerToRawData], section->SizeOfRawData);
			section->Misc.PhysicalAddress = (DWORD)(POINTER_TYPE)dest;
		}
	}
}

void PELoader::Relocate()
{
	DWORD locationDelta = static_cast<DWORD>(result_headers->OptionalHeader.ImageBase - old_header->OptionalHeader.ImageBase);
	//utils::hooking::hooking_helpers::SetBaseDiffer(locationDelta);
	if (locationDelta != 0)
	{
		PIMAGE_DATA_DIRECTORY directory = GetHeaderDictionary(IMAGE_DIRECTORY_ENTRY_BASERELOC);

		if (directory->Size > 0)
		{
			PIMAGE_BASE_RELOCATION relocation = (PIMAGE_BASE_RELOCATION)(result_headers->OptionalHeader.ImageBase + directory->VirtualAddress);
			while (relocation->VirtualAddress > 0)
			{
				unsigned char *dest = (unsigned char *)(result_headers->OptionalHeader.ImageBase + relocation->VirtualAddress);
				unsigned short *relInfo = (unsigned short *)((unsigned char *)relocation + sizeof(IMAGE_BASE_RELOCATION));

				for (DWORD i = 0; i < ((relocation->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / 2); i++, relInfo++)
				{
#ifdef _WIN64
					ULONGLONG *patchAddr64;
#endif
					int type, offset;

					type = *relInfo >> 12;
					offset = *relInfo & 0xfff;

					if (type == IMAGE_REL_BASED_HIGHLOW)
						*(DWORD *)(dest + offset) += locationDelta;
#ifdef _WIN64
					if (type == IMAGE_REL_BASED_DIR64) {
						patchAddr64 = (ULONGLONG *)(dest + offset);
						*patchAddr64 += (ULONGLONG)locationDelta;
					}
#endif
				}

				relocation = (PIMAGE_BASE_RELOCATION)(((char *)relocation) + relocation->SizeOfBlock);
			}
		}
	}
}