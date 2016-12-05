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
#include <io.h>
#include <thread>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <fstream>
#include <mutex>
#include <iostream>
#include <locale>
#include <codecvt>
#include <TimeAPI.h>
#include <shlobj.h>
#include <functional>
#include <queue>
#include "resource.h"
#include "tinyxml2.h"
#include "CVector3.h"
#include "Utils.h"
#include "Console\CConsole.h"
#include "Console\CLog.h"
#include <cfloat>
#include <cstdarg> 
#include <cstddef>
#include <cstring>
#include "FakeSteam.h"
#include "UserLibrary.h"
#include <Winternl.h>
#include "jitasm.h"
#pragma endregion

#pragma region D3D Stuff
#include "D3D11\Include\d3d11.h"
#include "D3D11\Include\d3dcompiler.h"
#include "D3D11\Include\dxgi1_2.h"
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
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
#include "Natives.h"
#pragma endregion

#pragma region RakNet
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
#pragma endregion

#pragma region tinyxml2
#include <tinyxml2.h>
#pragma endregion

#pragma region Shared
#include "CMath.h"
#include "Memory.h"
#include "NetworkTypes.h"
#include "Models.h"
#include "Network\CConfig.h"
#pragma endregion

#pragma region RAGE Stuff
#include "GTA\sysAllocator.h"
#include "GTA\VTasks.h"
#include "GTA\CRage.h"
#include "GTA\CReplayInterface.h"
#include "GTA\CGraphics.h"
#pragma endregion

#pragma region Network
#include "Network\CEntity.h"
#include "Network\CPedestrian.h"
#include "Network\CVehicle.h"
#include "Network\CLocalPlayer.h"
#include "Network\CNetworkBlip.h"
#include "Network\CNetworkPlayer.h"
#include "Network\CNetworkVehicle.h"
#include "Network\CNetworkConnection.h"
#include "Network\CNetworkUI.h"
#include "Network\Functions.h"
#include "Network\CRPCPlugin.h"
#pragma endregion

/*#pragma region CEF
#include <include/cef_browser.h>
#include <include/cef_command_line.h>
#include <include/views/cef_browser_view.h>
#include <include/views/cef_window.h>
#include <include/wrapper/cef_helpers.h>
#include <include/cef_parser.h>
#include <include/cef_task.h>
#include <include/cef_app.h>
#include <include/cef_client.h>
#include <include/cef_render_handler.h>
#include <include/cef_life_span_handler.h>
#include <include/internal/cef_types_wrappers.h>
#include <include/internal/cef_win.h>
#include <include/internal/cef_types.h>
#include <include/cef_origin_whitelist.h>
#include "Window.h"
#pragma endregion*/

#include "Registry.h"
#include "Common.h"
#include "PELoader.h"
#include "Game.h"
#include "Chat.h"
#include "Commands.h"

#pragma region IMGUI
#include "D3D11\VIngameConsole.h"
#include "D3D11\imgui.h"
#include "D3D11\imgui_impl_dx11.h"
#pragma endregion

#include "Globals.h"
#include "ScriptInvoker.h"


#define WINDOWTITLE L"Grand Theft Auto: Orange"
#define STEAMTITLE  "Grand Theft Auto V: Orange"


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

IMGUI_API LRESULT ImGui_ImplDX11_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void CreateRenderTarget();

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

#define TRACE() log_debug << __FILE__ << " -> Line " << __LINE__ << std::endl

void UpdateSplash(std::string text, float progress);
