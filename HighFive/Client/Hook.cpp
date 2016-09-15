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

void MemoryHook::jmp(intptr_t address, intptr_t jumpto)
{
	address += (intptr_t)GetModuleHandle(NULL);
	DWORD dwOldProtect, dwBkup;
	VirtualProtect((LPVOID*)address, 13, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	*((WORD*)address) = 0xB848;
	*((intptr_t *)(address + 2)) = jumpto;
	*((WORD*)(address + 10)) = 0xE0FF;
	*((BYTE*)(address + 12)) = 0xC3;
	VirtualProtect((LPVOID*)address, 13, dwOldProtect, &dwBkup);
}
