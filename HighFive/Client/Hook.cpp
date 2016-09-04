#include "stdafx.h"

void MemoryHook::nop(intptr_t address, int count)
{
	address += (uintptr_t)GetModuleHandle(NULL);
	unsigned long dwProtectOld;
	VirtualProtect((LPVOID)address, 2, PAGE_EXECUTE_READWRITE, &dwProtectOld);
	memset((void*)address, 0x90, count);
	VirtualProtect((LPVOID)address, 2, dwProtectOld, NULL);
}

void MemoryHook::retn(intptr_t address)
{
	address += (uintptr_t)GetModuleHandle(NULL);
	unsigned long dwProtectOld;
	VirtualProtect((LPVOID)address, 2, PAGE_EXECUTE_READWRITE, &dwProtectOld);
	memset((void*)address, 0xC3, 1);
	VirtualProtect((LPVOID)address, 2, dwProtectOld, NULL);
}
