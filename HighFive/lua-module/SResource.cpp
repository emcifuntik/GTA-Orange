#include "stdafx.h"

lua_State *m_lua;
std::function<void()> tick;
SResource *SResource::singleInstance = nullptr;

static const struct luaL_Reg gfunclib[] = {
	{ "print", lua_print },
	{ NULL, NULL }
};

static const struct luaL_Reg mfunclib[] = {
	{ "CreateBlipForAll", lua_CreateBlipForAll },
	{ "GetPlayerCoords", lua_GetPlayerCoords },
	{ "GetPlayerName", lua_GetPlayerName },
	{ "PlayerExists", lua_PlayerExists },
	{ "SetPlayerInfoMsg", lua_SetPlayerInfoMsg },
	{ "OnTick", lua_tick },
	{ "SQLEnv", luaopen_luasql_mysql },
	{ NULL, NULL }
};

SResource *SResource::Get()
{
	if (!singleInstance) {
		singleInstance = new SResource();
	}
	return singleInstance;
}
SResource::SResource()
{
}

bool SResource::Init()
{
	m_lua = luaL_newstate();

	luaL_openlibs(m_lua);

	lua_getglobal(m_lua, "_G");
	luaL_setfuncs(m_lua, gfunclib, 0);
	lua_pop(m_lua, 1);

	lua_newtable(m_lua);
	luaL_setfuncs(m_lua, mfunclib, 0);
	lua_setglobal(m_lua, "__orange__");

	if (luaL_loadfile(m_lua, "modules//lua-module//API.lua") || lua_pcall(m_lua, 0, 0, 0)) {
		std::stringstream ss;
		ss << "[LUA] " << lua_tostring(m_lua, -1);
		API::Get().Print(ss.str().c_str());
		return false;
	}
	return true;
}

bool SResource::Start(const char* name)
{
	char path[64];
	char respath[64];

	sprintf_s(path, 64, "resources//%s//", name);
	sprintf_s(respath, 64, "%smain.lua", path);

	std::stringstream ss;
	ss << "[LUA] Starting resource " << name;
	API::Get().Print(ss.str().c_str());
	
	if (luaL_loadfile(m_lua, respath) || lua_pcall(m_lua, 0, 0, 0)) {
		std::stringstream ss;
		ss << "[LUA] Could not load main.lua for resource " << name;
		API::Get().Print(ss.str().c_str());
		return false;
	}
	return true;
}

bool SResource::OnPlayerConnect(long playerid)
{
	lua_getglobal(m_lua, "__OnPlayerConnect");
	lua_pushinteger(m_lua, playerid);

	if (lua_pcall(m_lua, 1, 0, 0))
	{
		API::Get().Print("Error in OnPlayerConnect callback");
		API::Get().Print(lua_tostring(m_lua, -1));
	}

	return true;
}

bool SResource::OnTick()
{
	tick();

	return true;
}

void SResource::SetTick(const std::function<void()>& t)
{
	tick = t;
}

char* SResource::OnHTTPRequest(const char* method, const char* url, const char* query, const char* body)
{
	lua_getglobal(m_lua, "__OnHTTPRequest");

	lua_pushstring(m_lua, method);
	lua_pushstring(m_lua, url);
	lua_pushstring(m_lua, query);
	lua_pushstring(m_lua, body);
	
	if (lua_pcall(m_lua, 4, 1, 0)) API::Get().Print("Error in OnHTTPRequest callback");
	if (lua_isnil(m_lua, -1)) {
		lua_pop(m_lua, 1);
		return NULL;
	}

	char* res = _strdup(lua_tostring(m_lua, -1));
	lua_pop(m_lua, 1);

	return res;
}

SResource::~SResource()
{
}
