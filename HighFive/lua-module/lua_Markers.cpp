#include "stdafx.h"

int lua_CreateMarkerForAll(lua_State *L)
{
	lua_pushnumber(L, API::Get().CreateMarkerForAll(lua_tonumber(L, 1), lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4), lua_tonumber(L, 5)));
	return 1;
}