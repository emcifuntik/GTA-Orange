#include "stdafx.h"

int lua_CreateBlipForAll(lua_State *L)
{
	lua_pushnumber(L, API::Get().CreateBlipForAll(lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4), lua_tointeger(L, 5), lua_tointeger(L, 6)));
	return 0;// 1;
}