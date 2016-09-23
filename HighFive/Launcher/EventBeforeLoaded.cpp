#include "stdafx.h"

void Initialize()
{
	HUDInit();
}

static bool OnLookAlive()
{
	if (!initialized)
	{
		Initialize();
		initialized = true;
	}
	CEvent::Trigger("onGameFrame");
	return g_origLookAlive();
}

class CEventBeforeLoaded :
	public CEvent
{
	std::string Type()
	{
		return "onBeforeLoaded";
	}
	bool Action()
	{
		// ignore launcher requirement
		auto mem = CMemory::Find("E8 ? ? ? ? 84 C0 75 ? B2 01 B9 2F A9 C2 F4");
		mem.put(0xEB90909090909090);
		try {
			mem = CMemory::Find("FF 15 ? ? ? ? 84 C0 74 0C B2 01 B9 91 32 25 31 E8");
			mem.nop(6);
			(mem + 2).put(0xEBi8);
		}
		catch (...)
		{

		}

		mem = CMemory::Find("48 85 C9 0F 84 ? 00 00 00 48 8D 55 A7 E8");
		auto mem2 = mem + 13;
		mem2.put(0x01B0i16);
		mem2.nop(3);

		mem = CMemory::Find("8D 4A 03 E8 ? ? ? ? E8 ? ? ? ? 84 C0 75 1E");
		(mem + 2).put(0x08i8);

		mem = CMemory::Find("A8 FC 75 06 80 7F 36 04");
		(mem - 74).retn();

		mem = CMemory::Find("E8 ? ? ? ? 8B CB 40 88 2D ? ? ? ?");
		mem.nop(5);

		mem = CMemory::Find("48 83 EC 28 85 D2 78 71 75 0F");
		mem2 = CMemory::Find("48 83 EC 28 B9 ? ? ? ? E8 ? ? ? ? B9 ? ? ? ? E8 ? ? ? ? B1 01");
		(mem + 0x3B).put(DWORD(mem2.getFunc() - mem.getFunc() - 0x3F));

		mem = CMemory::Find("48 89 5C 24 ? 57 48 83 EC 20 8B F9 8B DA");
		mem.retn();

		mem = CMemory::Find("48 89 5C 24 08 57 48 83 EC 20 48 8B 05 ? ? ? ? 33 DB 48 85 C0 74 39");
		auto callToMem = mem();
		mem.farJmp(OnLookAlive);

		auto lookFrame = (CMemory::Find("48 81 EC 60 01 00 00 E8 ? ? ? ? 33 F6 48 8D") + 7);
		auto lookMem = lookFrame();
		g_origLookAlive = lookFrame.get_call<LookAlive>();
		(lookFrame + 1).put(DWORD(callToMem - lookMem - 5));

		mem = CMemory::Find("45 33 F6 41 8D 56 27 44 89") - 0x23;
		HUDInit = InitHUD(mem.get<void>(0));
		return true;
	}
} _ev;

