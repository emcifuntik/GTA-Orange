#pragma once

#define WIN32_LEAN_AND_MEAN
#define TG(x) x = !x

#if _DEBUG
#define TRACE( format, ... ) { char debug[256]; sprintf( debug,  "%s::%s(%d) " format "\n", __FILE__, __FUNCTION__,  __LINE__, __VA_ARGS__ ); log_debug << debug << std::endl;}
#define TRACEN() { char debug[256]; sprintf( debug,  "%s::%s(%d)\n", __FILE__, __FUNCTION__,  __LINE__ ); log_debug << debug << std::endl;}
#else
#define TRACE( format, ... )
#define TRACEN()
#endif

// Windows Header Files:
#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <intrin.h>
#include <string>
#include <map>
#include <cstring>
#include <vector>
#include <sstream>
#include <Psapi.h>
#include <iostream>
#include <fstream>
#include <timeapi.h>
#include <ctime>
#include <tlhelp32.h>
#include <cmath>
#include <iostream>
#include <future>
#include <algorithm>
#include <locale>
#include <codecvt>
#include <iomanip>
#include <queue>
#include <exception>

#pragma comment(lib, "Psapi.lib")
#pragma comment(lib, "winmm.lib")

// RakNet
#include <MessageIdentifiers.h>
#include <RakPeerInterface.h>
#include <RakNetStatistics.h>
#include <RakNetTypes.h>
#include <BitStream.h>
#include <RakSleep.h>
#include <PacketLogger.h>
#include <Kbhit.h>
#include <Gets.h>
#include <WindowsIncludes.h>
#include <GetTime.h>
#include <RPC4Plugin.h>
using namespace RakNet;

// Call hook
#include <Hook.h>

// Console
#include <Console\CConsole.h>
#include <Console\CLog.h>

// XML
#include <tinyxml2.h>

// ScriptHook
#include <natives.h>
#include <types.h>
#include <enums.h>
#include <sh_main.h>

// Client
#include "main.h"

// Math
#include "CMath.h"
#include "CVector3.h"

// Game Functions
#include "GameScripts.h"
#include "CUI.h"
#include "CGraphics.h"


#include "../../Shared/NetworkTypes.h"
#include "../../Shared/Models.h"
#include "CConfig.h"

// Utils
#include "Utils.h"

// Modification
#include "Commands.h"
#include "CMemory.h"

// Interface
#include "CChat.h"
#include <d3dtypes.h>

// RAGE Stuff
#include "GTA\CAddress.h"
#include "sysAllocator.h"
#include "VTasks.h"
#include "GTA\CEntity.h"
#include "GTA\CPed.h"
#include "GTA\CWeaponInfo.h"
#include "GTA\CHandlingData.h"
#include "CRage.h"
#include "CReplayInterface.h"

// Pools
#include "CEntity.h"
#include "CPedestrian.h"
#include "CVehicle.h"
#include "CLocalPlayer.h"

// Net
#include "CNetworkPlayer.h"
#include "CNetworkVehicle.h"
#include "CNetworkConnection.h"
#include "Functions.h"
#include "CRPCPlugin.h"
