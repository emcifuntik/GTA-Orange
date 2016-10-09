// python-module.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"

API * API::instance = nullptr;

extern "C"
{
	__declspec(dllexport) bool Validate(API * api)
	{
		API::Set(api);
		return true;
	}

	__declspec(dllexport) void OnModuleInit()
	{
		API::Get().Print("Python module loaded");
	}

	__declspec(dllexport) bool OnPlayerConnect(long playerid)
	{
		std::stringstream ss;
		ss << "Player " << API::Get().GetPlayerName(playerid) << "[" << playerid << "] connected to server";
		API::Get().BroadcastClientMessage(ss.str().c_str(), 0x00AA00FF);
		API::Get().SetPlayerPosition(playerid, -634.78f, -719.33f, 31.55f);
		return true;
	}

	__declspec(dllexport) bool OnServerCommand(std::string command)
	{

		return true;
	}

	__declspec(dllexport) bool OnPlayerDisconnect(long playerid, int reason)
	{
		std::stringstream ss;
		ss << "Player [" << playerid << "] left the server(" << ((reason == 1) ? "Disconnected" : "Timeout") << ")";
		API::Get().BroadcastClientMessage(ss.str().c_str(), 0x00AA00FF);
		return true;
	}

	__declspec(dllexport) bool OnPlayerUpdate(long playerid)
	{

		return true;
	}

	__declspec(dllexport) bool OnPlayerCommand(long playerid, const char * command)
	{

		return true;
	}

	__declspec(dllexport) bool OnPlayerText(long playerid, const char * text)
	{

		return true;
	}
}

