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

bool quickmenu = false;

bool getKeyPressed(int key) {
	return (GetAsyncKeyState(key) & 0xFFFF) == 0x8001;
}

#include "Natives.h"

void D3DHook::Render()
{
	ImGui_ImplDX11_NewFrame();
	if(CGlobals::Get().currentGameState == GameStatePlaying)
		CChat::Get()->Render();

	//block escape key on first start
	if (CGlobals::Get().displayServerBrowser && CGlobals::Get().blockquickswitch)
	{
		ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiSetCond_Always);
		ImGui::SetNextWindowPosCenter(ImGuiSetCond_Always);
		ImGui::Begin("Server browser", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
		ImGui::Text("Direct connect");
#if _DEBUG
		char serverIP[32] = "127.0.0.1";
#else
		char serverIP[32] = "";
#endif
		ImGui::InputText(":", serverIP, 32);
		ImGui::SameLine();
		int port = 7788;
		ImGui::InputInt("", &port, 1, 100);
		if (ImGui::Button("Connect"))
		{
		//	if (strcmp(serverIP, "127.0.0.1") == 0)
		//	{
		//
		//	}
			//if he is a dev we can send user on localhost
			if (CGlobals::Get().isorangedev)
			{
				CGlobals::Get().displayServerBrowser = false;
				CGlobals::Get().blockquickswitch = false;
				//disable static cam
		//		CAM::SET_CAM_ACTIVE(CGlobals::Get().currentcam, false);
		//		CAM::DESTROY_CAM(CGlobals::Get().currentcam, true);
		//		CAM::DESTROY_ALL_CAMS(true);
		//		CAM::SET_FOLLOW_PED_CAM_VIEW_MODE(1);
				CAM::RENDER_SCRIPT_CAMS(false, false, 0, false, false);
			}
		}
		ImGui::End();
		ShowCursor(TRUE);
	}

	ImGui::Render();
}