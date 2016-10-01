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

char serverIP[32] = "";
char nickName[32] = "";

void D3DHook::Render()
{
	ImGui_ImplDX11_NewFrame();
	if(CGlobals::Get().showChat)
		CChat::Get()->Render();

	if (CGlobals::Get().displayServerBrowser)
	{
		ShowCursor(TRUE);
		ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiSetCond_Always);
		ImGui::SetNextWindowPosCenter(ImGuiSetCond_Always);
		ImGui::Begin("Server browser", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
		ImGui::Text("Configuration");
		ImGui::InputText("Nickname", nickName, 32);
		ImGui::Text("Direct connect");
		ImGui::InputText(":", serverIP, 32);
		ImGui::SameLine();
		int port = 7788;
		ImGui::InputInt("", &port, 1, 100);
		if (ImGui::Button("Connect"))
		{
			std::stringstream ss;
			ss << "Connecting to " << serverIP << ":" << port;
			CChat::Get()->AddChatMessage(ss.str());
			if (!CNetworkConnection::Get()->Connect(serverIP, port))
				CChat::Get()->AddChatMessage("Can't connect to the server", { 255, 0, 0, 255 });
			CGlobals::Get().displayServerBrowser ^= 1;
			CGlobals::Get().showChat = true;
			CConfig::Get()->sNickName = std::string(nickName);
			ShowCursor(FALSE);
		}
		ImGui::End();
	}

	ImGui::Render();

	//CNetworkPlayer::Render();
}