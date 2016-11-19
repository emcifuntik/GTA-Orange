// lua-module.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"

API * API::instance = nullptr;
Player players[256];

extern "C"
{
	__declspec(dllexport) bool Validate(API * api)
	{
		API::Set(api);
		return true;
	}

	__declspec(dllexport) const char* OnResourceTypeRegister()
	{
		return "lua";
	}

	__declspec(dllexport) bool OnResourceLoad(const char* resource)
	{
		SResource::Get()->Start(resource);
		return true;
	}

	__declspec(dllexport) void OnModuleInit()
	{
		SResource::Get()->Init();
		API::Get().Print("Lua module loaded");
	}

	__declspec(dllexport) bool OnTick()
	{
		return SResource::Get()->OnTick();
	}

	__declspec(dllexport) bool OnPlayerConnect(long playerid)
	{
		return SResource::Get()->OnPlayerConnect(playerid);
	}

	__declspec(dllexport) char* OnHTTPRequest(const char* method, const char* url, const char* query, std::string body)
	{
		return SResource::Get()->OnHTTPRequest(method, url, query, body.c_str());;
	}

	__declspec(dllexport) bool OnServerCommand(std::string command)
	{
		return true;
	}

	__declspec(dllexport) bool OnPlayerDisconnect(long playerid, int reason)
	{
		players[playerid].exists = false;
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

