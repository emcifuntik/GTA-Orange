// stdafx.h: ���������� ���� ��� ����������� ��������� ���������� ������
// ��� ���������� ������ ��� ����������� �������, ������� ����� ������������, ��
// �� ����� ����������
//

#pragma once

#include "targetver.h"

#pragma comment (lib,"LUA.lib")

#define WIN32_LEAN_AND_MEAN             // ��������� ����� ������������ ���������� �� ���������� Windows
// ����� ���������� Windows:
#include <windows.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "API.h"

#include "SResource.h"

#include "lua.hpp"
#include "lua_Main.h"
