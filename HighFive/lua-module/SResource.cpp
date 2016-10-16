#include "stdafx.h"

const char* name;
lua_State *m_lua;

static const struct luaL_Reg gfunclib[] = {
	{ "print", lua_print },
	{ NULL, NULL }
};

static const struct luaL_Reg mfunclib[] = {
	{ "PlayerExists", lua_PlayerExists },
	{ "CreateBlipForAll", lua_CreateBlipForAll },
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

SResource::~SResource()
{
}