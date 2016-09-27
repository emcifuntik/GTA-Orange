#pragma once
#define WIN32_LEAN_AND_MEAN
#define DYNAMIC_PE_ALLOC

#pragma region core
#include <cstdint>
#include <windows.h>
#include <string>
#include <sstream>
#include <Psapi.h>
#include <sstream>
#include <intrin.h>
#include <vector>
#include <thread>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <locale>
#include <codecvt>
#include <TimeAPI.h>
#include <functional>
#include <queue>
#include "resource.h"
#include "tinyxml2.h"
#include "CVector3.h"
#include "Utils.h"
#include "Console\CConsole.h"
#include "Console\CLog.h"
#pragma endregion
#pragma region events
#include "Event.h"
//#include "EventBeforeLoaded.h"
#pragma endregion
#pragma region memory caching
#include "MemoryCache.h"
#pragma endregion
#pragma region CustomHook
#include "types.h"
#include "pgCollection.h"
#include "pgPtrCollection.h"
#include "nativeInvoker.h"
#include "scrThread.h"
#include "scrManager.h"
#include "scrEngine.h"
#include "nativeCaller.h"
#include "Script.h"
#pragma endregion
#include "D3D11\VIngameConsole.h"
#include "Registry.h"
#include "Memory.h"
#include "Common.h"
#include "PELoader.h"
#include "Game.h"
#include "Globals.h"
#include "UI.h"
#include "Graphics.h"
#include "Chat.h"

enum eGameState {
	GameStatePlaying,
	GameStateIntro,
	GameStateLicenseShit = 3,
	GameStateMainMenu = 5,
	GameStateLoadingSP_MP = 6
};

typedef void(*InitHUD)();
typedef bool(*LookAlive)();
typedef bool(*GameStateChange_)();

struct Color
{
	int r;
	int g;
	int b;
	int a;

	Color(int ar, int ag, int ab, int aa)
	{
		r = ar;
		g = ag;
		b = ab;
		a = aa;
	}
	UINT32 ToUINT32()
	{
		return ((UINT32)((((a) & 0xff) << 24) | (((b) & 0xff) << 16) | (((g) & 0xff) << 8) | ((r) & 0xff)));
	}
};

void D3DTextDraw(int x, int y, Color col, std::string text);

static LookAlive g_origLookAlive;
static GameStateChange_ g_gameStateChange;
static InitHUD HUDInit;
static bool initialized = false;
static LPARAM Icon;

#pragma region script macro
#define SCRIPT(x,y,z) class z:\
public CScript\
{\
public:\
	z() : CScript(\
		x\
	) {}\
protected:\
	virtual void Run() override { scriptRegister(x, y); }\
} z;
#pragma endregion
// USAGE: SCRIPT(name, function);
