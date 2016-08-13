#include "stdafx.h"

PedFactoryHook* PedFactoryHook::singleInstance = nullptr;
VehicleFactoryHook* VehicleFactoryHook::singleInstance = nullptr;

namespace rageGlobals
{
	void AllowChangeLanguage(bool toggle)
	{
		bool *_addr = (bool*)((intptr_t)GetModuleHandle(NULL) + 0x293A657);
		(*_addr) = toggle;
	}
};