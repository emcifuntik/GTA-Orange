#include "stdafx.h"
#include <gdiplus.h>

#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;

PELoader loader;


extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}
extern "C"
{
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

static TCHAR szWindowClass[] = "highfive_app";
Image* pBitmap = NULL;


float loadProgress = 0.0;
std::string splashText = "Starting launcher";
HWND splashHwnd = NULL;

void UpdateSplash(std::string text, float progress)
{
	splashText = text;
	loadProgress = progress;
	::RECT rect;
	rect.left = 0;
	rect.top = 200;
	rect.right = 300;
	rect.bottom = 226;
	InvalidateRect(splashHwnd, &rect, false);
}


void InitializeDummies();

#pragma region antiAntiDebug
static void* origCloseHandle;

typedef struct _OBJECT_HANDLE_ATTRIBUTE_INFORMATION
{
	BOOLEAN Inherit;
	BOOLEAN ProtectFromClose;
} OBJECT_HANDLE_ATTRIBUTE_INFORMATION, *POBJECT_HANDLE_ATTRIBUTE_INFORMATION;

#pragma comment(lib, "ntdll.lib")

struct NtCloseHook : public jitasm::Frontend
{
	NtCloseHook()
	{

	}

	static NTSTATUS ValidateHandle(HANDLE handle)
	{
		char info[16];

		if (NtQueryObject(handle, (OBJECT_INFORMATION_CLASS)4, &info, sizeof(OBJECT_HANDLE_ATTRIBUTE_INFORMATION), nullptr) >= 0)
		{
			return 0;
		}
		else
		{
			return STATUS_INVALID_HANDLE;
		}
	}

	void InternalMain()
	{
		push(rcx);

		mov(rax, (uint64_t)&ValidateHandle);
		call(rax);

		pop(rcx);

		cmp(eax, STATUS_INVALID_HANDLE);
		je("doReturn");

		mov(rax, (uint64_t)origCloseHandle);
		push(rax); // to return here, as there seems to be no jump-to-rax in jitasm

		L("doReturn");
		ret();
	}
};

class NtdllHooks
{
private:
	UserLibrary m_ntdll;

private:
	void HookHandleClose();

	void HookQueryInformationProcess();

public:
	NtdllHooks(const wchar_t* ntdllPath);

	void Install();
};

NtdllHooks::NtdllHooks(const wchar_t* ntdllPath)
	: m_ntdll(ntdllPath)
{
}

void NtdllHooks::Install()
{
	HookHandleClose();
	HookQueryInformationProcess();
}

void NtdllHooks::HookHandleClose()
{
	// hook NtClose (STATUS_INVALID_HANDLE debugger detection)
	uint8_t* code = (uint8_t*)GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "NtClose");

	origCloseHandle = VirtualAlloc(nullptr, 1024, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	memcpy(origCloseHandle, m_ntdll.GetExportCode("NtClose"), 1024);

	NtCloseHook* hook = new NtCloseHook;
	hook->Assemble();

	DWORD oldProtect;
	VirtualProtect(code, 15, PAGE_EXECUTE_READWRITE, &oldProtect);

	*(uint8_t*)code = 0x48;
	*(uint8_t*)(code + 1) = 0xb8;

	*(uint64_t*)(code + 2) = (uint64_t)hook->GetCode();

	*(uint16_t*)(code + 10) = 0xE0FF;
}

static void* origQIP;
static DWORD explorerPid;

#include <ntstatus.h>

typedef NTSTATUS(*NtQueryInformationProcessType)(IN HANDLE ProcessHandle, IN PROCESSINFOCLASS ProcessInformationClass, OUT PVOID ProcessInformation, IN ULONG ProcessInformationLength, OUT PULONG ReturnLength OPTIONAL);

static NTSTATUS NtQueryInformationProcessHook(IN HANDLE ProcessHandle, IN PROCESSINFOCLASS ProcessInformationClass, OUT PVOID ProcessInformation, IN ULONG ProcessInformationLength, OUT PULONG ReturnLength OPTIONAL)
{
	NTSTATUS status = ((NtQueryInformationProcessType)origQIP)(ProcessHandle, ProcessInformationClass, ProcessInformation, ProcessInformationLength, ReturnLength);

	if (NT_SUCCESS(status))
	{
		if (ProcessInformationClass == ProcessBasicInformation)
		{
			((PPROCESS_BASIC_INFORMATION)ProcessInformation)->Reserved3 = (PVOID)explorerPid;
		}
		else if (ProcessInformationClass == 30) // ProcessDebugObjectHandle
		{
			*(HANDLE*)ProcessInformation = 0;

			return STATUS_PORT_NOT_SET;
		}
		else if (ProcessInformationClass == 7) // ProcessDebugPort
		{
			*(HANDLE*)ProcessInformation = 0;
		}
		else if (ProcessInformationClass == 31)
		{
			*(ULONG*)ProcessInformation = 1;
		}
	}

	return status;
}

void NtdllHooks::HookQueryInformationProcess()
{
	uint8_t* code = (uint8_t*)GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "NtQueryInformationProcess");

	HWND shellWindow = GetShellWindow();
	GetWindowThreadProcessId(shellWindow, &explorerPid);

	origQIP = VirtualAlloc(nullptr, 1024, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	memcpy(origQIP, m_ntdll.GetExportCode("NtQueryInformationProcess"), 1024);

	/*NtQueryInformationProcessHook* hook = new NtQueryInformationProcessHook;
	hook->Assemble();*/

	DWORD oldProtect;
	VirtualProtect(code, 15, PAGE_EXECUTE_READWRITE, &oldProtect);

	*(uint8_t*)code = 0x48;
	*(uint8_t*)(code + 1) = 0xb8;

	*(uint64_t*)(code + 2) = (uint64_t)NtQueryInformationProcessHook;

	*(uint16_t*)(code + 10) = 0xE0FF;
}
#pragma endregion

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
	HWND hWnd = CreateWindowExW(dwExStyle, lpClassName, WINDOWTITLE, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
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

BOOL FileExists(LPCTSTR szPath)
{
	DWORD dwAttrib = GetFileAttributes(szPath);

	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

BOOL IsDebuggerPresentEx()
{
	return false;
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

LRESULT CALLBACK WndProc2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		Graphics g(hdc);
		g.DrawImage(pBitmap, 0, 0);
		SolidBrush backPen(Gdiplus::Color(255, 192, 0));
		SolidBrush frontPen(Gdiplus::Color(255, 130, 0));
		g.FillRectangle(&backPen, 67, 220, 168, 6);
		g.FillRectangle(&frontPen, 67, 220, (int)round(168 * loadProgress), 6);
		::RECT rect;
		rect.left = 0;
		rect.top = 200;
		rect.right = 300;
		rect.bottom = 220;

		HFONT font = CreateFont(18, 0, 0, 0, 300, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Segoe UI");
		HFONT hFontOld = (HFONT)SelectObject(hdc, font);
		DrawText(hdc, splashText.c_str(), splashText.length(), &rect, DT_CENTER | DT_VCENTER);
		SelectObject(hdc, hFontOld);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc2;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));
	return RegisterClassEx(&wcex);
}


ULONG_PTR m_gdiplusToken;

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	pBitmap = Bitmap::FromResource(hInstance, MAKEINTRESOURCEW(IDB_BITMAP1));

	splashHwnd = CreateWindow(szWindowClass, "", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 300, 300, nullptr, nullptr, hInstance, nullptr);
	SetWindowLong(splashHwnd, GWL_STYLE, 0);

	if (!splashHwnd)
	{
		return FALSE;
	}

	ShowWindow(splashHwnd, nCmdShow);
	UpdateWindow(splashHwnd);

	return TRUE;
}

void PELoad()
{
	InitializeDummies();
	/*CEF::Window::Init();
	auto windows = new CEF::Window(
	"https://google.com",
	{ 800, 600 },
	{ 0, 0 },
	true,
	true
	);*/
	UpdateSplash("Hooking libraries", 0.05);

	loader.SetLibraryLoader([](const char* libName)
	{
		if (!_stricmp(libName, "xlive.dll"))
			return (HMODULE)INVALID_HANDLE_VALUE;
		if (!_stricmp(libName, "steam_api64.dll"))
			CGlobals::Get().isSteam = true;
		return LoadLibraryA(libName);
	});

	UpdateSplash("Hooking libraries functions", 0.1);

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
#pragma region Steam hook
		/*else if (!_stricmp(functionName, "SteamAPI_RegisterCallback"))
		{
		return SteamAPI_RegisterCallback;
		}
		else if (!_stricmp(functionName, "SteamAPI_UnregisterCallback"))
		{
		return SteamAPI_UnregisterCallback;
		}
		else if (!_stricmp(functionName, "SteamApps"))
		{
		return SteamApps;
		}
		else if (!_stricmp(functionName, "SteamUserStats"))
		{
		return SteamUserStats;
		}
		else if (!_stricmp(functionName, "SteamUtils"))
		{
		return SteamUtils;
		}*/
		else if (!_stricmp(functionName, "SteamFriends"))
		{
			return SteamFriends;
		}
		/*else if (!_stricmp(functionName, "SteamAPI_Init"))
		{
		return SteamAPI_Init;
		}*/
		else if (!_stricmp(functionName, "SteamAPI_RestartAppIfNecessary"))
		{
			return SteamAPI_RestartAppIfNecessary;
		}
		/*else if (!_stricmp(functionName, "SteamAPI_RunCallbacks"))
		{
		return SteamAPI_RunCallbacks;
		}*/
		else if (!_stricmp(functionName, "SteamUser"))
		{
			return SteamUser;
		}
		else if (!_stricmp(functionName, "IsDebuggerPresent"))
		{
			return IsDebuggerPresentEx;
		}
#pragma endregion
		return (LPVOID)GetProcAddress(module, functionName);
	});

	UpdateSplash("Trying to find GTA5 folder", 0.15);

	char GamePath[MAX_PATH] = { 0 };
	bool social = true;
	if (!CConfig::Get()->gtaPath.length())
	{
		if (!CRegistry::Read(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Rockstar Games\\Grand Theft Auto V", "InstallFolder", GamePath, MAX_PATH))
		{
			social = false;
			if (!CRegistry::Read(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Rockstar Games\\GTAV", "InstallFolderSteam", GamePath, MAX_PATH))
				strcpy_s(GamePath, CConfig::Get()->gtaPath.c_str());
			else
				CConfig::Get()->gtaPath = std::string(GamePath);
		}
		else
			CConfig::Get()->gtaPath = std::string(GamePath);
	}
	else
		strcpy_s(GamePath, CConfig::Get()->gtaPath.c_str());

	while (1)
	{
		SetCurrentDirectory(GamePath);
		SetEnvironmentVariable("PATH", GamePath);
		if (!FileExists("GTA5.exe"))
		{
			std::string fldr = BrowseFolder("");
			if (!fldr.compare(""))
			{
				TerminateProcess(GetCurrentProcess(), 0);
				return;
			}
			strcpy_s(GamePath, MAX_PATH, fldr.c_str());
			continue;
		}
		else
		{
			CConfig::Get()->gtaPath = std::string(GamePath);
			CConfig::Get()->Save();
			break;
		}
	}

	PPEB peb = (PPEB)__readgsqword(0x60);
	peb->BeingDebugged = false;

	// set GlobalFlags
	*(DWORD*)((char*)peb + 0xBC) &= ~0x70;

	{
		// user library stuff ('safe' ntdll hooking callbacks)
		wchar_t ntdllPath[MAX_PATH];
		GetModuleFileNameW(GetModuleHandleW(L"ntdll.dll"), ntdllPath, _countof(ntdllPath));

		NtdllHooks hooks(ntdllPath);
		hooks.Install();
	}

	//if (CoreIsDebuggerPresent())
	//{
	//	// NOP OutputDebugStringA; the debugger doesn't like multiple async exceptions
	//	uint8_t* func = (uint8_t*)OutputDebugStringA;

	//	DWORD oldProtect;
	//	VirtualProtect(func, 1, PAGE_EXECUTE_READWRITE, &oldProtect);

	//	*func = 0xC3;

	//	VirtualProtect(func, 1, oldProtect, &oldProtect);
	//}
	UpdateSplash("Loading GTA5.exe", 0.20);

	auto b = loader.LoadFile("GTA5.exe");
	if (b != 0)
	{
		MessageBoxA(NULL, "PELoad failed", "PELoad failed", 0);
		printf_s("PELoad failed");
		TerminateProcess(GetCurrentProcess(), 0);
		return;
	}

	loader.Run();
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow) {
	
	if (!_strcmpi(lpCmdLine, "-debug"))
	{
		CGlobals::Get().isDebug = true;
	}
	else if (!_strcmpi(lpCmdLine, "-developer"))
	{
		CGlobals::Get().isDeveloper = true;
	}


	Icon = LPARAM(LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)));

	char _hfPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, _hfPath);
	CGlobals::Get().highFivePath = std::string(_hfPath);
	
	std::thread(PELoad).detach();

	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

	MSG msg;

	// Цикл основного сообщения:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	Gdiplus::GdiplusShutdown(m_gdiplusToken);

	return (int)msg.wParam;
};
