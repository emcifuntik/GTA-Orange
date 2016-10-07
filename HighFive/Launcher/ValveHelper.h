#pragma once

#include "stdafx.h"

typedef void* (*CreateInterface_t)(const char* pName, int* pReturnCode);

class SteamHelper
{
private:
	HMODULE m_hSteamClient;

	uint32_t GetSteamProcessId();

	std::string GetSteamDllPath();

	void LoadGameOverlayRenderer(const std::string& baseDllPath);

	void* GetProcAddressInternal(const char* name);

public:
	void Initialize();

	bool IsSteamRunning(bool ignoreCreateFunc);

	template<typename TProcedure>
	TProcedure GetProcAddress(const char* name)
	{
		return reinterpret_cast<TProcedure>(GetProcAddressInternal(name));
	}

	CreateInterface_t GetCreateInterfaceFunc();
};