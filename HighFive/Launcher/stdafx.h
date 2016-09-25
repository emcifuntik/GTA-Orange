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
#include "resource.h"
#include "tinyxml2.h"
#include "CVector3.h"
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
#include "Natives.h"
#pragma endregion
#include "Utils.h"
#include "Console\CConsole.h"
#include "Console\CLog.h"
#include "Registry.h"
#include "CMemory.h"
#include "Common.h"
#include "PELoader.h"
#include "Game.h"
#include "Globals.h"

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

static LookAlive g_origLookAlive;
static GameStateChange_ g_gameStateChange;
static InitHUD HUDInit;
static bool initialized = false;
static LPARAM Icon;
