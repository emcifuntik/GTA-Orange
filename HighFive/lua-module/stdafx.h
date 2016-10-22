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
#include "API.h"

#include "SResource.h"

#include "lua.hpp"
#include "lua_Main.h"
