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
#include <map>
#include "resource.h"
#include "tinyxml2.h"
#pragma endregion
#pragma region events
#include "Event.h"
//#include "EventBeforeLoaded.h"
#pragma endregion
#pragma region memory caching
#include "MemoryCache.h"
#pragma endregion

#include "Registry.h"
#include "CMemory.h"
#include "Common.h"
#include "PELoader.h"
#include "Game.h"
#include "Globals.h"

typedef void(*InitHUD)();
typedef bool(*LookAlive)();

static LookAlive g_origLookAlive;
static InitHUD HUDInit;
static bool initialized = false;
static LPARAM Icon;
