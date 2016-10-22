#include "stdafx.h"

int lua_PlayerExists(lua_State *L)
{
	lua_pushboolean(L, !!API::Get().GetPlayerModel(lua_tointeger(L, 1)));

	return 1;
}

int lua_GetPlayerName(lua_State *L)
{
	std::string name = API::Get().GetPlayerName(lua_tointeger(L, 1));

	API::Get().Print(name.c_str());

	lua_pushstring(L, name.c_str());

	return 1;
}

int lua_GetPlayerCoords(lua_State *L)
{
	CVector3 pos = API::Get().GetPlayerPosition(lua_tointeger(L, 1));

	lua_pushnumber(L, pos.fX);
	lua_pushnumber(L, pos.fY);
	lua_pushnumber(L, pos.fZ);

	return 3;
}

