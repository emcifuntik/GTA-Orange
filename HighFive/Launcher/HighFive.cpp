#include "stdafx.h"

using namespace std;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// Here your application is laid out.
		// For this introduction, we just print out "Hello, World!"
		// in the top left corner.
		/*TextOut(hdc,
			5, 5,
			greeting, _tcslen(greeting));*/
		// End application specific layout section.

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}

static TCHAR szWindowClass[] = _T("highfive");
static TCHAR szTitle[] = _T("HighFive Launcher");

bool ProcessRunning(const char* name)
{
	HANDLE SnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (SnapShot == INVALID_HANDLE_VALUE)
		return false;

	PROCESSENTRY32 procEntry;
	procEntry.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(SnapShot, &procEntry))
		return false;

	do
	{
		if (strcmp(procEntry.szExeFile, name) == 0)
			return true;
	} while (Process32Next(SnapShot, &procEntry));

	return false;
}

void InjectDLL()
{
	const char *dllname = "HighFive.dll";
	const char *dllname2 = "ScriptHookV.dll";

	bool GameThread = false;
	char GamePath[MAX_PATH] = { 0 };
	char GameFullPath[MAX_PATH] = { 0 };
	char Params[] = "";

	if (!DoesFileExist(dllname)) {
		MessageBox(NULL, "Could not find HighFive.dll", "Fatal Error", MB_ICONERROR);
		ExitProcess(0);
		return;
	}

	if (!DoesFileExist(dllname2)) {
		MessageBox(NULL, "Could not find ScriptHook.dll", "Fatal Error", MB_ICONERROR);
		ExitProcess(0);
		return;
	}

	bool social = true;
	if (!SharedUtils::Registry::Read(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\rockstar games\\Grand Theft Auto V", "InstallFolder", GamePath, MAX_PATH))
	{
		social = false;
		if (!SharedUtils::Registry::Read(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Rockstar Games\\GTAV", "InstallFolderSteam", GamePath, MAX_PATH))
		{
			MessageBox(NULL, "Cannot find game path in registry!", "Fatal Error", MB_ICONERROR);
			ExitProcess(0);
			return;
		}
	}

	CopyFile("config.xml", (std::string(GamePath) + "\\config.xml").c_str(), false);
	// Format game paths
	sprintf_s(GameFullPath, "%s\\GTAVLauncher.exe", GamePath);

	// Predefine startup and process infos
	STARTUPINFO siStartupInfo;
	PROCESS_INFORMATION piProcessInfo;
	memset(&siStartupInfo, 0, sizeof(siStartupInfo));
	memset(&piProcessInfo, 0, sizeof(piProcessInfo));
	siStartupInfo.cb = sizeof(siStartupInfo);


	// Create game process
	if (social && !CreateProcess(GameFullPath, Params, NULL, NULL, true, CREATE_SUSPENDED, NULL, GamePath, &siStartupInfo, &piProcessInfo))
	{
		if (!ShellExecute(0, 0, "steam://run/271590", 0, 0, SW_SHOW)) {
			MessageBox(NULL, "Grand Theft Auto V was not able to start.", "Fatal Error", MB_ICONERROR);
			ExitProcess(0);
			return;
		}
	}
	else
	{
		if (!ShellExecute(0, 0, "steam://run/271590", 0, 0, SW_SHOW)) {
			MessageBox(NULL, "Grand Theft Auto V was not able to start.", "Fatal Error", MB_ICONERROR);
			ExitProcess(0);
			return;
		}
	}

	// Resume game main thread
	ResumeThread(piProcessInfo.hThread);

	bool GameStarted = false;
	bool Injected_ScriptHook = false;
	bool Injected_HighFive = false;

	while (GameThread == false) {
		HWND hWnds = FindWindowA(NULL, "Grand Theft Auto V");

		bool yes = ProcessRunning("GTA5.exe");

		if (yes != NULL) {
			Sleep(7500);
			if (GameStarted == false) {
				GameStarted = true;
			}
			else {
				if (InjectDLL("GTA5.exe", dllname2) == true) {
					Injected_ScriptHook = true;
				}
				if (InjectDLL("GTA5.exe", dllname) && Injected_ScriptHook) {
					Injected_HighFive = true;
					GameThread = true;
				}
			}
		}
	}
	ExitProcess(0);
}

//Entry
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow) {
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}


	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 500,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T(""),
			NULL);

		return 1;
	}
	SetWindowLong(hWnd, GWL_STYLE, 0);

	thread inject([]() {
		InjectDLL();
	});

	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}