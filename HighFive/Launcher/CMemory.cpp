#include "stdafx.h"

ptrdiff_t CMemory::baseDiff;
bool CMemory::initialized = false;

CMemory::CMemory(UINT64 address)
{
	this->address = (void*)address;
}

CMemory::~CMemory()
{
}

void CMemory::put(const char * value)
{
	unsigned long dwProtectOld;
	VirtualProtect((LPVOID)address, 2, PAGE_EXECUTE_READWRITE, &dwProtectOld);
	memcpy(address, value, strlen(value));
	VirtualProtect((LPVOID)address, 2, dwProtectOld, NULL);
}

bool CMemory::memoryCompare(const BYTE *data, const BYTE *pattern, size_t length)
{
	for (size_t i = 0; i < length; ++i, ++data, ++pattern)
		if (*data != *pattern)
			return false;
	return true;
}

bool CMemory::memoryCompare(const BYTE *data, const BYTE *pattern, const char *mask)
{
	for (; *mask; ++mask, ++data, ++pattern)
		if (*mask == '1' && *data != *pattern)
			return false;
	return (*mask) == NULL;
}

void CMemory::nop(size_t length)
{
	unsigned long dwProtectOld;

	VirtualProtect((LPVOID)address, length, PAGE_EXECUTE_READWRITE, &dwProtectOld);
	memset(address, 0x90, length);
	VirtualProtect((LPVOID)address, length, dwProtectOld, NULL);
	address = (LPVOID)((uint64_t)address + length);
}

void CMemory::farJmp(LPVOID func)
{
	DWORD dwOldProtect, dwBkup;
	VirtualProtect((LPVOID*)address, 13, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	*((WORD*)address) = 0xB848;
	*((intptr_t *)(uintptr_t(address) + 2)) = (uintptr_t)func;
	*((WORD*)(uintptr_t(address) + 10)) = 0xE0FF;
	*((BYTE*)(uintptr_t(address) + 12)) = 0xC3;
	VirtualProtect((LPVOID*)address, 13, dwOldProtect, &dwBkup);
}

CMemory& CMemory::Find(const char * pattern)
{
	if (!initialized)
	{
		Init();
		initialized = true;
	}
	std::stringstream buff(pattern);



	std::string search;
	std::string mask;
	while (!buff.eof())
	{
		std::string tmp;
		buff >> tmp;
		if (!tmp.compare("?"))
		{
			mask += "0";
			search += (char)0;
		}
		else
		{
			size_t error;
			char val = (char)std::stoi(tmp, &error, 16);
			mask += "1";
			search += val;
		}
	}

	


	UINT64 i;
	UINT64 size;
	UINT64 address;

	address = (UINT64)((uintptr_t)CGlobals::Get().baseAddr);
	size = (UINT64)0x6000000i64;

	DWORD offset;
	if (CMemoryCache::Get().TryGetOffset(pattern, offset))
	{
		if(Check(search, mask, offset))
			return *(new CMemory((UINT64)(address + offset)));
	}

	UINT64 patternAddress = 0;
	for (i = 0; i < size; ++i) {
		if (CMemory::memoryCompare((BYTE *)(address + i), (BYTE *)search.c_str(), mask.c_str())) {
			patternAddress = address + i;
			break;
		}
	}
	
	if (patternAddress)
	{
		CMemoryCache::Get().AddOffset(pattern, DWORD(i));
		return *(new CMemory((UINT64)(address + i)));
	}
	else
		throw std::exception("Pattern not found!");
}

bool CMemory::Check(std::string search, std::string mask, DWORD offset)
{
	UINT64 address = (UINT64)((uintptr_t)CGlobals::Get().baseAddr);

	if (CMemory::memoryCompare((BYTE *)(address + offset), (BYTE *)search.c_str(), mask.c_str()))
		return true;
	return false;
}

void CMemory::Init()
{
	uintptr_t addressDiff = ((uintptr_t)CGlobals::Get().baseAddr - 0x140000000);
	baseDiff = *(ptrdiff_t*)&addressDiff;
}
