// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//

#pragma once

#include "targetver.h"

#pragma comment (lib,"LUA.lib")

#define WIN32_LEAN_AND_MEAN             // »сключите редко используемые компоненты из заголовков Windows
// ‘айлы заголовков Windows:
#include <windows.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <functional>
#include "API.h"

#include "mysql.h"

#include "SResource.h"

#include "lua.hpp"
#include "lua_Main.h"


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
	int getInt() { if (type == M_INT) return *(int*)ptr; return NULL; };
	int getBool() { if (type == M_BOOL) return *(bool*)ptr; return NULL; };
	double getDouble() { if (type == M_DOUBLE) return *(double*)ptr; return NULL; };

	bool isString() { return type == M_STRING; };
	bool isInt() { return type == M_INT; };
	bool isBool() { return type == M_BOOL; };
	bool isDouble() { return type == M_DOUBLE; };

	char type;
private:
	__int64 ptr;
};

extern Player players[256];
