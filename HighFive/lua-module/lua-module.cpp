// lua-module.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"

API * API::instance = nullptr;
std::vector<SResource*> Res;

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
		SResource *_res = new SResource(resource);
		if (_res->Start()) Res.push_back(_res);
		return true;
	}
	__declspec(dllexport) void OnModuleInit()
	{
		API::Get().Print("Lua module loaded");
	}

	__declspec(dllexport) bool OnPlayerConnect(long playerid)
	{
		return true;
	}

	__declspec(dllexport) bool OnServerCommand(std::string command)
	{

		return true;
	}

	__declspec(dllexport) bool OnPlayerDisconnect(long playerid, int reason)
	{
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

