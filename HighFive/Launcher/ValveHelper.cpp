
#include "ValveHelper.h"

void SteamHelper::Initialize()
{
	if (IsSteamRunning(true))
	{
		std::string steamDllPath = GetSteamDllPath();
		std::string steamDirectory = steamDllPath.substr(0, steamDllPath.rfind(L'\\'));

		// add Steam to the process path
		static char pathBuffer[65536];
		GetEnvironmentVariableA("PATH", pathBuffer, sizeof(pathBuffer));

		strcat(pathBuffer, ";");
		strcat(pathBuffer, steamDirectory.c_str());

		SetEnvironmentVariableA("PATH", pathBuffer);

		// load steamclient*.dll
		m_hSteamClient = LoadLibraryA(steamDllPath.c_str());

		LoadGameOverlayRenderer(steamDllPath);
	}
}

CreateInterface_t SteamHelper::GetCreateInterfaceFunc()
{
	return GetProcAddress<CreateInterface_t>("CreateInterface");
}

void* SteamHelper::GetProcAddressInternal(const char* name)
{
	void* func = nullptr;

	if (m_hSteamClient)
	{
		func = ::GetProcAddress(m_hSteamClient, name);
	}

	return func;
}

bool SteamHelper::IsSteamRunning(bool ignoreCreateFunc)
{
	bool retval = false;
	uint32_t pid = GetSteamProcessId();

	if (pid != 0)
	{
		HANDLE steamProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);

		if (steamProcess != INVALID_HANDLE_VALUE)
		{
			CloseHandle(steamProcess);

			retval = true;
		}
	}

	// safety check to see if CreateInterface is callable
	if (!GetCreateInterfaceFunc() && !ignoreCreateFunc)
	{
		retval = false;
	}

	return retval;
}

uint32_t SteamHelper::GetSteamProcessId()
{
	DWORD pid;
	DWORD pidSize = sizeof(pid);

	if (RegGetValueA(HKEY_CURRENT_USER, "Software\\Valve\\Steam\\ActiveProcess", "pid", RRF_RT_REG_DWORD, nullptr, &pid, &pidSize) == ERROR_SUCCESS)
	{
		return pid;
	}

	return 0;
}

#ifndef _M_AMD64
#define STEAMCLIENT_DLL "SteamClientDll"
#else
#define STEAMCLIENT_DLL "SteamClientDll64"
#endif

std::string SteamHelper::GetSteamDllPath()
{
	char pathString[512];
	DWORD pathStringSize = sizeof(pathString);

	if (RegGetValueA(HKEY_CURRENT_USER, "Software\\Valve\\Steam\\ActiveProcess", STEAMCLIENT_DLL, RRF_RT_REG_SZ, nullptr, pathString, &pathStringSize) == ERROR_SUCCESS)
	{
		return pathString;
	}

	return "";
}

#ifndef _M_AMD64
#define OVERLAYRENDERER_DLL "GameOverlayRenderer.dll"
#else
#define OVERLAYRENDERER_DLL "GameOverlayRenderer64.dll"
#endif

void SteamHelper::LoadGameOverlayRenderer(const std::string& baseDllPath)
{
	std::string overlayDllPath = baseDllPath.substr(0, baseDllPath.rfind('\\')) + "\\" OVERLAYRENDERER_DLL;

	LoadLibraryA(overlayDllPath.c_str());
}