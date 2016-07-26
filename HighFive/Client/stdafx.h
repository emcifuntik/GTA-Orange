#pragma once

#define WIN32_LEAN_AND_MEAN

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

// XML
#include <tinyxml2.h>

// ScriptHook
#include <natives.h>
#include <types.h>
#include <enums.h>
#include <sh_main.h>

// Client
#include "main.h"

// Game Functions
#include "GameScripts.h"
#include "CUI.h"
#include "CGraphics.h"

// Math
#include "../../Shared/CMath.h"
#include "../../Shared/CVector3.h"
#include "../../Shared/NetworkTypes.h"
#include "../../Shared/Models.h"
#include "CConfig.h"

// Utils
#include "Utils.h"

// Modification
#include "Commands.h"
#include "Memory.h"

// Pools
#include "CEntity.h"
#include "CPedestrian.h"
#include "CVehicle.h"
#include "CLocalPlayer.h"

// Net
#include "CNetworkPlayer.h"
//#include "CNetworkVehicle.h"
#include "CNetworkConnection.h"
#include "Functions.h"
#include "CRPCPlugin.h"

// Interface
#include "CChat.h"

#if 0
#define TRACE( format, ... )
#define TRACEN()
#else
#define TRACE( format, ... ) { char debug[256]; sprintf( debug,  "%s::%s(%d) " format "\n", __FILE__, __FUNCTION__,  __LINE__, __VA_ARGS__ ); MessageBoxA(NULL, debug, "DEBUG", MB_OK);}
#define TRACEN() { char debug[256]; sprintf( debug,  "%s::%s(%d)\n", __FILE__, __FUNCTION__,  __LINE__ ); MessageBoxA(NULL, debug, "DEBUG", MB_OK);}
#endif
