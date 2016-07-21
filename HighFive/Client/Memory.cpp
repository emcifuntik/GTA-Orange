#include "stdafx.h"

ptrdiff_t Memory::baseDiff;

Memory::Memory(UINT64 address)
{
	this->address = (void*)address;
}

Memory::~Memory()
{
}

void Memory::put(const char * value)
{
	unsigned long dwProtectOld;
	VirtualProtect((LPVOID)address, 2, PAGE_EXECUTE_READWRITE, &dwProtectOld);
	memcpy(address, value, strlen(value));
	VirtualProtect((LPVOID)address, 2, dwProtectOld, NULL);
}

bool Memory::memoryCompare(const BYTE *data, const BYTE *pattern, size_t length)
{
	for (size_t i = 0; i < length; ++i, ++data, ++pattern)
		if (*data != *pattern)
			return false;
	return true;
}

bool Memory::memoryCompare(const BYTE *data, const BYTE *pattern, const char *mask)
{
	for (; *mask; ++mask, ++data, ++pattern)
		if (*mask == '1' && *data != *pattern)
			return false;
	return (*mask) == NULL;
}

void Memory::nop(size_t length)
{
	unsigned long dwProtectOld;

	VirtualProtect((LPVOID)address, 2, PAGE_EXECUTE_READWRITE, &dwProtectOld);
	memset(address, 0x90, length);
	VirtualProtect((LPVOID)address, 2, dwProtectOld, NULL);
}

Memory * Memory::Find(const char * pattern)
{
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
	MODULEINFO info = { 0 };

	address = (UINT64)GetModuleHandle(NULL);
	GetModuleInformation(GetCurrentProcess(), GetModuleHandle(NULL), &info, sizeof(MODULEINFO));
	size = (UINT64)info.SizeOfImage;

	for (i = 0; i < size; ++i)
		if (Memory::memoryCompare((BYTE *)(address + i), (BYTE *)search.c_str(), mask.c_str()))
			return new Memory((UINT64)(address + i));
	return nullptr;
}

Memory * Memory::Find_t(const char * text)
{
	UINT64 i;
	UINT64 size;
	UINT64 address;
	MODULEINFO info = { 0 };

	address = (UINT64)GetModuleHandle(NULL);
	GetModuleInformation(GetCurrentProcess(), GetModuleHandle(NULL), &info, sizeof(MODULEINFO));
	size = (UINT64)info.SizeOfImage;

	for (i = 0; i < size; ++i)
		if (Memory::memoryCompare((BYTE *)(address + i), (BYTE *)text, strlen(text)))
			return new Memory((UINT64)(address + i));
	return nullptr;
}

void Memory::Init()
{
#ifdef _M_IX86
	uintptr_t addressDiff = ((uintptr_t)GetModuleHandle(NULL) - 0x400000);
#elif defined(_M_AMD64)
	uintptr_t addressDiff = ((uintptr_t)GetModuleHandle(NULL) - 0x140000000);
#endif

	// pointer-style cast to ensure unsigned overflow ends up copied directly into a signed value
	baseDiff = *(ptrdiff_t*)&addressDiff;
}
