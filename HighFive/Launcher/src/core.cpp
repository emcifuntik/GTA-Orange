#include "stdafx.h"

PELoader loader;

static TCHAR szWindowClass[] = "highfive_app";

void InitializeDummies();

static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{

	if (uMsg == BFFM_INITIALIZED)
	{
		std::string tmp = (const char *)lpData;
		std::cout << "path: " << tmp << std::endl;
		SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
	}

	return 0;
}

std::string BrowseFolder(std::string saved_path)
{
	TCHAR path[MAX_PATH];

	const char * path_param = saved_path.c_str();

	BROWSEINFO bi = { 0 };
	bi.lpszTitle = ("Browse for GTAV folder...");
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	bi.lpfn = BrowseCallbackProc;
	bi.lParam = (LPARAM)path_param;

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

	if (pidl != 0)
	{
		//get the name of the folder and put it in path
		SHGetPathFromIDList(pidl, path);

		//free memory used
		IMalloc * imalloc = 0;
		if (SUCCEEDED(SHGetMalloc(&imalloc)))
		{
			imalloc->Free(pidl);
			imalloc->Release();
		}

		return path;
	}

	return "";
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
	HWND hWnd = CreateWindowExW(dwExStyle, lpClassName, (LPCWSTR)WINDOWTITLE, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	SendMessage(hWnd, WM_SETICON, ICON_BIG, Icon);
	SendMessage(hWnd, WM_SETICON, ICON_SMALL, Icon);

	if (GetModuleHandle("D3D11.dll") != NULL)
	{
		CGlobals::Get().d3dloaded = true;
	}

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

//later get procadress of something, for now is this enough!
void CheckDev()
{
	if (_access("dev", 0) == 0)
	{
		CGlobals::Get().isorangedev = true;
	//	MessageBoxA(NULL, "Dev mode toolinit!", "Orange-mp", MB_OK | MB_ICONWARNING);
	}
}

BOOL FileExists(LPCTSTR szPath)
{
	DWORD dwAttrib = GetFileAttributes(szPath);

	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
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
	CheckDev();
	loader.SetLibraryLoader([](const char* libName)
	{
		if (!_stricmp(libName, "xlive.dll"))
			return (HMODULE)INVALID_HANDLE_VALUE;
		if (!_stricmp(libName, "steam_api64.dll"))
			CGlobals::Get().isSteam = true;
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
		return (LPVOID)GetProcAddress(module, functionName);
	});

	char GamePath[MAX_PATH] = { 0 };
	bool social = true;
	if (!CConfig::Get()->gtaPath.length())
	{
		if (!CRegistry::Read(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Rockstar Games\\Grand Theft Auto V", "InstallFolder", GamePath, MAX_PATH))
		{
			social = false;
			if (!CRegistry::Read(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Rockstar Games\\GTAV", "InstallFolderSteam", GamePath, MAX_PATH))
			{
				strcpy_s(GamePath, CConfig::Get()->gtaPath.c_str());
			}
			else
			{
				CConfig::Get()->gtaPath = std::string(GamePath);
			}
		}
		else
		{
			CConfig::Get()->gtaPath = std::string(GamePath);
		}
	}
	else
	{
		strcpy_s(GamePath, CConfig::Get()->gtaPath.c_str());
	}
	

	while (1)
	{
		SetCurrentDirectory(GamePath);
		SetEnvironmentVariable("PATH", GamePath);
		if (!FileExists("GTA5.exe"))
		{
			strcpy_s(GamePath, MAX_PATH, BrowseFolder("").c_str());
			continue;
		}
		else
		{
			CConfig::Get()->gtaPath = std::string(GamePath);
			CConfig::Get()->Save();
			break;
		}
	}
	
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
