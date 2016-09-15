#include "stdafx.h"
#if _DEBUG
#define DEBUG_TEXT " - Debug. " __TIME__ " - " __DATE__
#else
#define DEBUG_TEXT
#endif

WNDPROC	oWndProc;
LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved )
{
	if (reason == DLL_PROCESS_ATTACH) {
#if _DEBUG
		HWND window = nullptr;
		window = FindWindowA("grcWindow", NULL);
		SetWindowTextA(window, "HighFive Multiplayer" DEBUG_TEXT);
#endif

		//rage::hookFunction();

		CMemory::Init();
		// Disable intro

		MemoryHook::retn((*GTA::CAddress::Get())[SOME_STRANGE_HOOK]);
		MemoryHook::retn((*GTA::CAddress::Get())[DISABLE_WANTED_GENERATION_1]);
		(*MemoryHook::value<unsigned short*>((*GTA::CAddress::Get())[DISABLE_WANTED_GENERATION_2])) = 0xE990;
		//
		MemoryHook::nop((*GTA::CAddress::Get())[LOAD_SCREENS]);
		(*MemoryHook::value<DWORD*>((*GTA::CAddress::Get())[LOAD_SINGLE_PLAYER1] + 0x3B)) = 
			(*GTA::CAddress::Get())[LOAD_SINGLE_PLAYER2] - (*GTA::CAddress::Get())[LOAD_SINGLE_PLAYER1] - 0x3F;
		MemoryHook::retn((*GTA::CAddress::Get())[DISABLE_LOGO]);
		MemoryHook::retn((*GTA::CAddress::Get())[SHOW_TOOL_TIPS]);
		MemoryHook::retn((*GTA::CAddress::Get())[SOCIAL_CLUB_NEWS]);
		MemoryHook::nop((*GTA::CAddress::Get())[DISABLE_PAUSE_ESC]);
		MemoryHook::nop((*GTA::CAddress::Get())[DISABLE_NORTH_BLIP], 46);
		MemoryHook::retn((*GTA::CAddress::Get())[DISABLE_VEH_POPULATION1]);
		MemoryHook::nop((*GTA::CAddress::Get())[DISABLE_VEH_POPULATION4]);
		//MemoryHook::nop((*GTA::CAddress::Get())[CRASH_LOAD_MODELS_TOO_QUICKLY], 23);
		//MemoryHook::nop((*GTA::CAddress::Get())[INTENTIONAL_CRASH]);
		//MemoryHook::retn((*GTA::CAddress::Get())[CREATE_NETWORK_EVENT_BINDINGS]);
		MemoryHook::retn((*GTA::CAddress::Get())[LOAD_NEW_GAME]);
		//MemoryHook::retn((*GTA::CAddress::Get())[OPEN_CHEAT_WINDOW]);
		MemoryHook::retn((*GTA::CAddress::Get())[RESET_VEHICLE_DENSITY_LAST_FRAME]);
		MemoryHook::retn((*GTA::CAddress::Get())[SET_CLOCK_FORWARD_AFTER_DEATH]);
		MemoryHook::retn((*GTA::CAddress::Get())[DISABLE_LOADING_MP_DLC_CONTENT]);
		MemoryHook::nop((*GTA::CAddress::Get())[VAR_VEHICLE_DENSITY_NOP], 30);
		MemoryHook::nop((*GTA::CAddress::Get())[PED_DENSITY_NOP], 40);

		MemoryHook::nop((*GTA::CAddress::Get())[MULTIPLAYER_MENU], 9);
		MemoryHook::retn((*GTA::CAddress::Get())[SET_PED_RUMBLE_REACTION]);
		/*MemoryHook::nop((*GTA::CAddress::Get())[GTAMP_NOP1]);
		MemoryHook::nop((*GTA::CAddress::Get())[GTAMP_NOP2]);
		MemoryHook::nop((*GTA::CAddress::Get())[GTAMP_NOP3]);*/

		(*MemoryHook::value<float*>((*GTA::CAddress::Get())[VAR_VEHICLE_DENSITY1])) = 0.0f;
		(*MemoryHook::value<float*>((*GTA::CAddress::Get())[VAR_VEHICLE_DENSITY2])) = 0.0f;
		(*MemoryHook::value<float*>((*GTA::CAddress::Get())[VAR_VEHICLE_DENSITY3])) = 0.0f;
		(*MemoryHook::value<float*>((*GTA::CAddress::Get())[PED_DENSITY1])) = 0.0f;
		(*MemoryHook::value<float*>((*GTA::CAddress::Get())[PED_DENSITY2])) = 0.0f;
		(*MemoryHook::value<float*>((*GTA::CAddress::Get())[PED_DENSITY3])) = 0.0f;
		(*MemoryHook::value<float*>((*GTA::CAddress::Get())[PED_DENSITY4])) = 0.0f;

		MemoryHook::jmp((*GTA::CAddress::Get())[NEW_EVENT_HOOK], (intptr_t)&eventHook);

		scriptRegister(hModule, InitGameScript);
		scriptRegisterAdditionalThread(hModule, ChatRendering);
		scriptRegisterAdditionalThread(hModule, NetworkTick);
		scriptRegisterAdditionalThread(hModule, LocalTick);

		keyboardHandlerRegister(CChat::Get()->ScriptKeyboardMessage);
		keyboardHandlerRegister(OnKeyboardMessage);
#if _DEBUG
		AllocConsole();
		SetConsoleTitleA("HighFive Multiplayer Console" DEBUG_TEXT);

		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
#endif
	}
	if (reason == DLL_PROCESS_DETACH) {
		scriptUnregister(hModule);
#if _DEBUG
		FreeConsole();
#endif
	}
	return TRUE;
}

LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	/*if(uMsg != 0x7f && uMsg != 0xff && uMsg != 0x200 && uMsg != 0x20 && uMsg != 0x84)
		log_debug << std::hex << uMsg << ", " << wParam << ", " << lParam << std::endl;*/
	return CallWindowProc(oWndProc, hwnd, uMsg, wParam, lParam);
}

