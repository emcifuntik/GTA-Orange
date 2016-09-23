#include "stdafx.h"

using POINTER_TYPE = ULONGLONG;

#ifndef DYNAMIC_PE_ALLOC
unsigned char pe[0x6000000];
#endif

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
#ifndef DYNAMIC_PE_ALLOC
	unsigned char * code = pe;
	DWORD unused;
	VirtualProtect(code, old_header->OptionalHeader.SizeOfImage, PAGE_READWRITE, &unused);
#else
	LPVOID code = (unsigned char *)VirtualAlloc((LPVOID)(old_header->OptionalHeader.ImageBase), old_header->OptionalHeader.SizeOfImage, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
#endif

	this->code = HMODULE(code);
	if (code == NULL)
	{
#ifndef DYNAMIC_PE_ALLOC
		throw std::runtime_error("Out of memory");
#else
		code = (unsigned char *)VirtualAlloc(NULL, old_header->OptionalHeader.SizeOfImage, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		if (code == NULL)
		{
			SetLastError(ERROR_OUTOFMEMORY);
			throw std::runtime_error("Out of memory");
		}
#endif
	}
	
#ifndef DYNAMIC_PE_ALLOC
	unsigned char * headers = (unsigned char *)pe;
	VirtualProtect(headers, old_header->OptionalHeader.SizeOfHeaders, PAGE_READWRITE, &unused);
#else
	LPVOID headers = VirtualAlloc(code, old_header->OptionalHeader.SizeOfHeaders, MEM_COMMIT, PAGE_READWRITE);
#endif
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
			HMODULE handle = m_libraryLoader((LPCSTR)(result_headers->OptionalHeader.ImageBase + importDesc->Name));

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
					*funcRef = (FARPROC)m_functionResolver(handle, (LPCSTR)&((PIMAGE_IMPORT_BY_NAME)(result_headers->OptionalHeader.ImageBase + (*thunkRef)))->Name);
			}
		}
	}
}

void PELoader::ApplyPermissions()
{
	ULONGLONG imageOffset = (result_headers->OptionalHeader.ImageBase & 0xffffffff00000000);
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

		if (executable)
		{
			if (readable)
			{
				protect = PAGE_EXECUTE_READWRITE;
				if (!writeable)
					protect = PAGE_EXECUTE_READ;
			}
			else
			{
				protect = PAGE_EXECUTE_WRITECOPY;
				if (!writeable)
					protect = PAGE_EXECUTE;
			}
		}
		else if (readable)
		{
			protect = PAGE_READWRITE;
			if (!writeable)
				protect = PAGE_READONLY;
		}
		else
		{
			protect = PAGE_WRITECOPY;
			if (!writeable)
				protect = PAGE_NOACCESS;
		}

		if (section->Characteristics & IMAGE_SCN_MEM_NOT_CACHED)
			protect |= PAGE_NOCACHE;

		DWORD size = section->SizeOfRawData;
		if (size == 0)
			if (section->Characteristics & IMAGE_SCN_CNT_INITIALIZED_DATA)
				size = result_headers->OptionalHeader.SizeOfInitializedData;
			else if (section->Characteristics & IMAGE_SCN_CNT_UNINITIALIZED_DATA)
				size = result_headers->OptionalHeader.SizeOfUninitializedData;

		if (size > 0 && VirtualProtect((LPVOID)((POINTER_TYPE)section->Misc.PhysicalAddress | imageOffset), size, protect, &protect) == 0)
			printf_s("VirtualProtect error. Section: %s\n", section->Name);
	}
}

void PELoader::DoTLS()
{
	HANDLE module = GetModuleHandle(NULL);
	PIMAGE_DOS_HEADER targetHeader = (PIMAGE_DOS_HEADER)module;
	IMAGE_NT_HEADERS* targetNtHeader = (IMAGE_NT_HEADERS*)((int64_t)module + targetHeader->e_lfanew);
	if (targetNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].Size)
	{
		PIMAGE_TLS_DIRECTORY targetTls = (PIMAGE_TLS_DIRECTORY)(targetNtHeader->OptionalHeader.ImageBase + targetNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress);
		PIMAGE_TLS_DIRECTORY sourceTls = (PIMAGE_TLS_DIRECTORY)(result_headers->OptionalHeader.ImageBase + result_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress);
		PIMAGE_TLS_DIRECTORY tlsBase = (PIMAGE_TLS_DIRECTORY)__readgsqword(0x58);

#ifndef DYNAMIC_PE_ALLOC
		auto startAddr = /*sourceTls->StartAddressOfRawData - (0x140000000) + */intptr_t(result_headers->OptionalHeader.ImageBase) + 0xA44A878;
		auto endAddr = /*sourceTls->EndAddressOfRawData - (0x140000000) + */intptr_t(result_headers->OptionalHeader.ImageBase) + 0xA44A878 + 2170;
#else
		auto startAddr = sourceTls->StartAddressOfRawData;
		auto endAddr = sourceTls->EndAddressOfRawData;
#endif

		memcpy((LPVOID)tlsBase->StartAddressOfRawData, (LPVOID)startAddr, endAddr - startAddr);
		memcpy((LPVOID)targetTls->StartAddressOfRawData, (LPVOID)startAddr, endAddr - startAddr);
	}
	if (result_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].Size)
	{
#ifndef DYNAMIC_PE_ALLOC
		auto addressOfCallbacks = /*sourceTls->StartAddressOfRawData - (0x140000000) + */intptr_t(result_headers->OptionalHeader.ImageBase) + 0xA44A878 - 2170;
		PIMAGE_TLS_CALLBACK* callback = (PIMAGE_TLS_CALLBACK *)addressOfCallbacks;
#else
		PIMAGE_TLS_DIRECTORY tls = (PIMAGE_TLS_DIRECTORY)(result_headers->OptionalHeader.ImageBase + result_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress);
		PIMAGE_TLS_CALLBACK* callback = (PIMAGE_TLS_CALLBACK *)tls->AddressOfCallBacks;
#endif
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
	FILE* file = nullptr;
	errno_t error = fopen_s(&file, filename, "rb");

	if (error)
	{
		printf_s("Failed to open remote executable. Please check if executable exists %s", filename);
		return -1;
	}

	uint32 length = 0;

	fseek(file, 0, SEEK_END);
	length = ftell(file);

	data = new uint8[length];

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

	/*PRUNTIME_FUNCTION exceptions = (PRUNTIME_FUNCTION)(result_headers->OptionalHeader.ImageBase + result_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].VirtualAddress);
	auto exceptionsSize = result_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].Size / sizeof(RUNTIME_FUNCTION);
	m_module = GetModuleHandle(NULL);
	if (!RtlAddFunctionTable(exceptions, (unsigned int)exceptionsSize, (DWORD64)m_module))
	{
		printf_s("Can't install exception handler!\n");
	}*/

	DWORD oldProtect;
	VirtualProtect(result_headers, 0x1000, PAGE_EXECUTE_READWRITE, &oldProtect);

	result_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT] = old_header->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
	memcpy((void *)result_headers, (const void *)old_header, sizeof(IMAGE_SECTION_HEADER) * old_header->FileHeader.NumberOfSections + sizeof(IMAGE_NT_HEADERS));
	entryPoint = ((void(*)(void))(result_headers->OptionalHeader.ImageBase + result_headers->OptionalHeader.AddressOfEntryPoint));
	CGlobals::Get().baseAddr = (LPVOID)result_headers->OptionalHeader.ImageBase;
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
#ifndef DYNAMIC_PE_ALLOC
				DWORD unused;
				unsigned char * dest = static_cast<unsigned char *>(pe + section->VirtualAddress);
				VirtualProtect(dest, section->SizeOfRawData, PAGE_READWRITE, &unused);
#else
				unsigned char * dest = static_cast<unsigned char *>(VirtualAlloc((LPVOID)(result_headers->OptionalHeader.ImageBase
				+ section->VirtualAddress), result_headers->OptionalHeader.SectionAlignment, MEM_COMMIT, PAGE_READWRITE));
#endif

				section->Misc.PhysicalAddress = (DWORD)(POINTER_TYPE)dest;

				memset(dest, 0, result_headers->OptionalHeader.SectionAlignment);
			}
		}
		else
		{
			DWORD unused;
#ifndef DYNAMIC_PE_ALLOC
			unsigned char * dest = static_cast<unsigned char *>(pe + section->VirtualAddress);
			VirtualProtect(dest, section->SizeOfRawData, PAGE_READWRITE, &unused);
#else
			unsigned char * dest = static_cast<unsigned char *>(VirtualAlloc((LPVOID)(result_headers->OptionalHeader.ImageBase + section->VirtualAddress),
				section->SizeOfRawData, MEM_COMMIT, PAGE_READWRITE));
#endif
			memcpy(dest, &data[section->PointerToRawData], section->SizeOfRawData);
			section->Misc.PhysicalAddress = (DWORD)(POINTER_TYPE)dest;
			VirtualProtect(dest, section->SizeOfRawData, PAGE_EXECUTE_READWRITE, &unused);
		}
	}
}

void PELoader::Relocate()
{
	DWORD locationDelta = static_cast<DWORD>(result_headers->OptionalHeader.ImageBase - old_header->OptionalHeader.ImageBase);
	//utils::hooking::hooking_helpers::SetBaseDiffer(locationDelta);
	if (result_headers->OptionalHeader.ImageBase != old_header->OptionalHeader.ImageBase)
	{
		if (locationDelta)
		{
			PIMAGE_BASE_RELOCATION relocation = (PIMAGE_BASE_RELOCATION)(result_headers->OptionalHeader.ImageBase
				+ result_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
			
			while (relocation->VirtualAddress > 0)
			{
				unsigned char *dest = (unsigned char *)(result_headers->OptionalHeader.ImageBase + relocation->VirtualAddress);
				unsigned short *relInfo = (unsigned short *)((unsigned char *)relocation + sizeof(IMAGE_BASE_RELOCATION));

				for (DWORD i = 0; i < ((relocation->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / 2); i++, relInfo++)
				{
					ULONGLONG *patchAddr64;
					int type, offset;

					type = *relInfo >> 12;
					offset = *relInfo & 0xfff;

					if (type == IMAGE_REL_BASED_HIGHLOW)
						*(DWORD *)(dest + offset) += locationDelta;
					if (type == IMAGE_REL_BASED_DIR64) {
						patchAddr64 = (ULONGLONG *)(dest + offset);
						*patchAddr64 += (ULONGLONG)locationDelta;
					}
				}

				relocation = (PIMAGE_BASE_RELOCATION)(((char *)relocation) + relocation->SizeOfBlock);
			}
		}
	}
}