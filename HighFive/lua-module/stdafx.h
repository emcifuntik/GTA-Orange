
#pragma once

#ifdef _WINDOWS
#include "targetver.h"

#pragma comment (lib,"lua51.lib")

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#endif

#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <functional>
#include "API.h"

#ifdef _WINDOWS
#include "mysql.h"
#else
#include "orange/mysql/include/mysql.h"
#endif

#include "SResource.h"

#include "lua.hpp"
#include "lua_Main.h"

#ifdef __linux__
char *_strdup(const char *str);
#endif

static void luaL_setfuncs(lua_State *L, const luaL_Reg *l, int nup)
{
	luaL_checkstack(L, nup + 1, "too many upvalues");
	for (; l->name != NULL; l++) {  /* fill the table with given functions */
		int i;
		lua_pushstring(L, l->name);
		for (i = 0; i < nup; i++)  /* copy upvalues to the top */
			lua_pushvalue(L, -(nup + 1));
		lua_pushcclosure(L, l->func, nup);  /* closure with those upvalues */
		lua_settable(L, -(nup + 3));
	}
	lua_pop(L, nup);  /* remove upvalues */
};

struct Meta
{
	int ref;
	lua_State *m_lua;
};

struct Player
{
	bool exists = false;
	CVector3 pos;
	std::map<char*, Meta> metadata;
};

enum {
	M_STRING,
	M_INT,
	M_BOOL,
	M_DOUBLE
};

class MValue
{
public:
	MValue(const char* val) { ptr = (long long)&val; type = M_STRING; };
	MValue(int val) { ptr = (long long)&val; type = M_INT; };
	MValue(bool val) { ptr = (long long)&val; type = M_BOOL; }
	MValue(double val) { ptr = (long long)&val; type = M_DOUBLE; };

	char* getString() { if (type == M_STRING) return *(char**)ptr; return NULL; };
	int getInt() { if (type == M_INT) return *(int*)ptr; return 0; };
	int getBool() { if (type == M_BOOL) return *(bool*)ptr; return false; };
	double getDouble() { if (type == M_DOUBLE) return *(double*)ptr; return 0; };

	bool isString() { return type == M_STRING; };
	bool isInt() { return type == M_INT; };
	bool isBool() { return type == M_BOOL; };
	bool isDouble() { return type == M_DOUBLE; };

	char type;
private:
	long long ptr;
};

extern Player players[256];
