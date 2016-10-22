#include "stdafx.h"

const char* name;
lua_State *m_lua;

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
	{ NULL, NULL }
};

SResource::SResource(const char * _name)
{
	name = _name;
}

bool SResource::Start()
{
	m_lua = luaL_newstate();

	char path[64];
	char respath[64];

	sprintf_s(path, 64, "resources//%s//", name);
	sprintf_s(respath, 64, "%smain.lua", path);

	std::stringstream ss;
	ss << "[LUA] Starting resource " << name;
	API::Get().Print(ss.str().c_str());

	luaL_openlibs(m_lua);

	lua_getglobal(m_lua, "_G");
	luaL_setfuncs(m_lua, gfunclib, 0);
	lua_pop(m_lua, 1);

	lua_newtable(m_lua);
	luaL_setfuncs(m_lua, mfunclib, 0);
	lua_setglobal(m_lua, "__orange__");

	if (luaL_dofile(m_lua, "modules//lua-module//API.lua")) {
		std::stringstream ss;
		ss << "[LUA] " << lua_tostring(m_lua, -1);
		API::Get().Print(ss.str().c_str());
	}
	
	if (luaL_loadfile(m_lua, respath) || lua_pcall(m_lua, 0, 0, 0)) {
		std::stringstream ss;
		ss << "[LUA] Could not load main.lua for resource " << name;
		API::Get().Print(ss.str().c_str());
		return false;
	}
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
	lua_getglobal(m_lua, "__OnTick");

	if (lua_pcall(m_lua, 0, 0, 0)) API::Get().Print("Error in OnTick callback");

	return true;
}

SResource::~SResource()
{
}
