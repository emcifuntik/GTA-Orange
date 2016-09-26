#include "stdafx.h"

PELoader loader;

static TCHAR szWindowClass[] = "highfive_app";

void InitializeDummies();

LONG_PTR SetWindowLongPtrAHook(HWND hWnd, int nIndex, LONG_PTR dwNewLong)
{
	
	return SetWindowLongPtrA(hWnd, nIndex, dwNewLong);
}

static HWND CreateWindowExWHook(_In_ DWORD dwExStyle,
	_In_opt_ LPCWSTR lpClassName,
	_In_opt_ LPCWSTR lpWindowName,
	_In_ DWORD dwStyle,
	_In_ int X,
	_In_ int Y,
	_In_ int nWidth,
	_In_ int nHeight,
	_In_opt_ HWND hWndParent,
	_In_opt_ HMENU hMenu,
	_In_opt_ HINSTANCE hInstance,
	_In_opt_ LPVOID lpParam)
{
	HWND hWnd = CreateWindowExW(dwExStyle, lpClassName, L"GTA:V - HighFive Multiplayer", dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	SendMessage(hWnd, WM_SETICON, ICON_BIG, Icon);
	SendMessage(hWnd, WM_SETICON, ICON_SMALL, Icon);
	CGlobals::Get().gtaHwnd = hWnd;
	return hWnd;
}

static void OutputDebugStringAHook(LPCSTR text)
{
	OutputDebugStringA(text);
	std::ofstream out(CGlobals::Get().highFivePath + "\\Logs\\GTAV_Debug.log", std::ios_base::app);
	out << DateTimeA() << " " << text;
	out.close();
}

static void OutputDebugStringWHook(LPCWSTR text)
{
	OutputDebugStringW(text);
	std::wofstream out(CGlobals::Get().highFivePath + "\\Logs\\GTAV_Debug.log", std::ios_base::app);
	out << DateTimeW() << " " << text;
	out.close();
}

static int NoWindowsHookExA(int, HOOKPROC, HINSTANCE, DWORD)
{
	return 1;
}

LPSTR GetCommandLineAHook()
{
	if (CGlobals::Get().alreadyRunned)
		return GetCommandLineA();
	CGlobals::Get().alreadyRunned = true;
	CGlobals::Get().baseAddr = loader.code;
	CEvent::Trigger("onBeforeLoaded");
	return GetCommandLineA();
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow) {
	Icon = LPARAM(LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)));

	char _hfPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, _hfPath);
	CGlobals::Get().highFivePath = std::string(_hfPath);

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	//wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			"Call to RegisterClassEx failed!",
			"Fatal error",
			NULL);

		return 1;
	}

	InitializeDummies();

	loader.SetLibraryLoader([](const char* libName)
	{
		if (!_stricmp(libName, "xlive.dll"))
		{
			return (HMODULE)INVALID_HANDLE_VALUE;
		}
		return LoadLibraryA(libName);
	});

	loader.SetFunctionResolver([](HMODULE module, const char* functionName) -> LPVOID
	{
		if (!_stricmp(functionName, "GetCommandLineA"))
		{
			return GetCommandLineAHook;
		}
		else if (!_stricmp(functionName, "SetWindowsHookExA"))
		{
			return NoWindowsHookExA;
		}
		else if (!_stricmp(functionName, "OutputDebugStringA"))
		{
			return OutputDebugStringAHook;
		}
		else if (!_stricmp(functionName, "OutputDebugStringW"))
		{
			return OutputDebugStringWHook;
		}
		else if (!_stricmp(functionName, "CreateWindowExW"))
		{
			return CreateWindowExWHook;
		}
		else if (!_stricmp(functionName, "SetWindowLongPtrA"))
		{
			return SetWindowLongPtrAHook;
		}
		return (LPVOID)GetProcAddress(module, functionName);
	});

	char GamePath[MAX_PATH] = { 0 };
	bool social = true;
	if (!CRegistry::Read(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\rockstar games\\Grand Theft Auto V", "InstallFolder", GamePath, MAX_PATH))
	{
		social = false;
		if (!CRegistry::Read(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Rockstar Games\\GTAV", "InstallFolderSteam", GamePath, MAX_PATH))
		{
			MessageBox(NULL, "Cannot find game path in registry!", "Fatal Error", MB_ICONERROR);
			ExitProcess(0);
			return 1;
		}
	}

	SetCurrentDirectory(GamePath);
	SetEnvironmentVariable("PATH", GamePath);
	auto b = loader.LoadFile("GTA5.exe");
	if (b != 0)
	{
		printf_s("PELoad failed");
		TerminateProcess(GetCurrentProcess(), 0);
		return 0;
	}
	loader.Run();
	return 0;
};
