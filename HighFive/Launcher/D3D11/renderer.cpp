// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "VIngameConsole.h"
#include "../Chat.h"
#include "../Globals.h"
#include "stdafx.h"

void CreateRenderTarget()
{
	DXGI_SWAP_CHAIN_DESC sd;
	CGlobals::Get().d3dSwapChain->GetDesc(&sd);
	log_debug << "SwapChain: 0x" << std::hex << CGlobals::Get().d3dSwapChain << std::endl;
	log_debug << "sd.BufferDesc.Format: " << std::dec << sd.BufferDesc.Format << std::endl;

	// Create the render target
	
	ID3D11Texture2D* pBackBuffer;
	D3D11_RENDER_TARGET_VIEW_DESC render_target_view_desc;
	memset(&render_target_view_desc, 0, sizeof(render_target_view_desc));
	render_target_view_desc.Format = sd.BufferDesc.Format;
	render_target_view_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	CGlobals::Get().d3dSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	CGlobals::Get().d3dDevice->CreateRenderTargetView(pBackBuffer, &render_target_view_desc, &CGlobals::Get().d3dRenderTargetView);
	CGlobals::Get().d3dDeviceContext->OMSetRenderTargets(1, &CGlobals::Get().d3dRenderTargetView, NULL);
	pBackBuffer->Release();
}

void D3DHook::Render()
{
	//CChat::Get()->Render();
	bool show_chat_window = true;
	ImVec4 clear_col = ImColor(114, 144, 154);
	ImGui_ImplDX11_NewFrame();
	{
		/*static float f = 0.0f;
		ImGui::Text("Hello, world!");
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		ImGui::ColorEdit3("clear color", (float*)&clear_col);
		if (ImGui::Button("Test Window")) show_test_window ^= 1;
		if (ImGui::Button("Another Window")) show_another_window ^= 1;
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);*/
	}
	//Chat
	//if(*CGlobals::Get().hudDisabled)
	CChat::Get()->Render();

	ImGui::Render();
}