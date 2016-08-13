#include "stdafx.h"
#if _DEBUG
#define DEBUG_TEXT " - Debug. " __TIME__ " " __DATE__
#else
#define DEBUG_TEXT
#endif

WNDPROC	oWndProc;
LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved )
{
	if (reason == DLL_PROCESS_ATTACH) {
#if _DEBUG
		AllocConsole();
		SetConsoleTitleA("HighFive Multiplayer Console" DEBUG_TEXT);

		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
#endif

		HWND window = nullptr;
		while (!window)
		{
			window = FindWindowA("grcWindow", NULL);
			Sleep(10);
		}
		SetWindowTextA(window, "HighFive Multiplayer" DEBUG_TEXT);

		#pragma region Install WndProc Hook
		oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
		if (oWndProc == NULL) {

			log_error << "Failed to attach input hook" << std::endl;
		}
		else {
			log_info << "Input hook attached: WndProc 0x" << (DWORD_PTR)oWndProc << std::endl;
		}
		#pragma endregion

		CMemory::Init();
		// Disable intro
		CMemory *m = CMemory::Find_t("platform:/movies/rockstar_logos");
		if (m != nullptr)
			m->put("./nonexistingfilenonexistingfil");
		delete m;

		m = CMemory::Find("72 1F E8 ? ? ? ? 8B 0D");
		m->nop(2);
		delete m;
		
		m = CMemory::Find("70 6C 61 74 66 6F 72 6D 3A");
		m->nop(1);
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

bool ignore = false;

LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if(uMsg != 0x7f && uMsg != 0xff && uMsg != 0x200 && uMsg != 0x20 && uMsg != 0x84)
		log_debug << std::hex << uMsg << ", " << wParam << ", " << lParam << std::endl;
	/*if (uMsg == WM_INPUTLANGCHANGE)
	{
		DefWindowProc(hwnd, uMsg, wParam, lParam);
		if (!ignore)
		{
			ActivateKeyboardLayout((HKL)1, KLF_RESET);
			ignore = !ignore;
		}
		else
			ignore = !ignore;
		return 0;
	}*/
	return CallWindowProc(oWndProc, hwnd, uMsg, wParam, lParam);
}

