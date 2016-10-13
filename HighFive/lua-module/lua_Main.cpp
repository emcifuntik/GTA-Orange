#include "stdafx.h"

int lua_print(lua_State *L)
{
	API::Get().Print(lua_tostring(L, 1));
	return 0;
}