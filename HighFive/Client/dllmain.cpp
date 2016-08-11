#include "stdafx.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved )
{
	if (reason == DLL_PROCESS_ATTACH) {
		HWND window = FindWindowA(NULL, "Grand Theft Auto V");
		SetWindowTextA(window, "HighFive MP");
		Memory::Init();
		// Disable intro
		Memory *m = Memory::Find_t("platform:/movies/rockstar_logos");
		if (m != nullptr)
			m->put("./nonexistingfilenonexistingfil");
		delete m;

		////Usage:
		//LoadGameNow(0); //To start a new game, any other value other than 0 just seems to make the loading screen load endlessly

		//m = Memory::Find("48 85 C9 0F 84 ? 00 00 00 48 8D 55 A7 E8");
		//m += 13;
		//m->call(Memory::Return<int, 0>);
		//delete m;

		//m = Memory::Find("8D 4A 03 E8 ? ? ? ? E8 ? ? ? ? 84 C0 75 1E");
		//m += 2;
		//m->put<uint8_t>(8);
		//delete m;

		scriptRegister(hModule, InitGameScript);
		scriptRegisterAdditionalThread(hModule, ChatRendering);
		scriptRegisterAdditionalThread(hModule, NetworkTick);
		scriptRegisterAdditionalThread(hModule, LocalTick);

		keyboardHandlerRegister(CChat::Get()->ScriptKeyboardMessage);
		keyboardHandlerRegister(OnKeyboardMessage);
	}
	if (reason == DLL_PROCESS_DETACH) {
		scriptUnregister(hModule);
	}
	return TRUE;
}

