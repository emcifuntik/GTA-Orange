#include "stdafx.h"
#include "Includes.h"
#include "VIngameConsole.h"
#include "thirdparty/DirectX/Include/d3d11.h"
#include "Memory\Memory.h"
#include <sstream>
#include <d3d11.h>
#include <dxgi1_2.h>

typedef HRESULT(__stdcall* D3D11Present_t) (IDXGISwapChain* pThis, UINT SyncInterval, UINT Flags);
D3D11Present_t pD3D11_Present = NULL;

HRESULT __stdcall D3D11_Present_Hook(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	D3DHook::Render();
	return pD3D11_Present(pSwapChain, SyncInterval, Flags);
}

bool D3DHook::HookD3D11()
{
	IDXGISwapChain1* swapchain = *(IDXGISwapChain1**)CMemory::Find("48 8B 0D ? ? ? ? 48 8B 01 44 8D 43 01 33 D2").getOffset();
	CGlobals::Get().d3dSwapChain = swapchain;
	ID3D11Device* device;
	swapchain->GetDevice(__uuidof(ID3D11Device), (void**)&device);
	ID3D11DeviceContext* device_context;
	device->GetImmediateContext(&device_context);
	CGlobals::Get().d3dDevice = device;
	CGlobals::Get().d3dDeviceContext = device_context;
	auto gui_result = ImGui_ImplDX11_Init(CGlobals::Get().gtaHwnd, device, device_context);
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontDefault();
	CreateRenderTarget();
	DWORD64* pD3D11_SwapChainVTable = (DWORD64*)swapchain;
	pD3D11_SwapChainVTable = (DWORD64*)pD3D11_SwapChainVTable[0];

	Memory::Init();
	Memory::HookFunction((DWORD64)pD3D11_SwapChainVTable[8], &D3D11_Present_Hook, (void**)&pD3D11_Present);
	return true;
}
