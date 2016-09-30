#include "stdafx.h"
#include "Natives.h"

CChat *CChat::singleInstance = nullptr;

void CChat::AddLine(ChatLine line)
{
	if (vChatLines.size() >= cuChatHistorySize)
		vChatLines.erase(vChatLines.begin());
	vChatLines.push_back(line);
}

CChat::CChat() :uiCarretPos(0)
{

}

CChat* CChat::Get()
{
	if (!singleInstance)
		singleInstance = new CChat();
	return singleInstance;
}


void CChat::RegisterCommandProcessor(int(*callback)(std::string))
{
	_commandProcess = callback;
}

void CChat::Scroll(ScrollRoute route)
{
	if (route == SCROLL_UP)
	{
		iOffset += cuLinesOnScreen;
		if (iOffset > vChatLines.size())
			iOffset = (int)vChatLines.size();
	}
	else if (route == SCROLL_DOWN)
	{
		iOffset -= cuLinesOnScreen;
		if (iOffset < 0)
			iOffset = 0;
	}
}

CChat::~CChat()
{

}

void CChat::Render()
{
	if (!bEnabled)
		return;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f);
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1));

	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_Always);
	ImGui::Begin("Chat", &bEnabled, ImVec2(400, 190), .2f, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

	int uiFirstLine = (int)(vChatLines.size() - cuLinesOnScreen - iOffset);
	if (uiFirstLine < 0)
		uiFirstLine = 0;
	UINT uiLastLine = (UINT)min(uiFirstLine + cuLinesOnScreen, vChatLines.size());

	ImGui::PushFont(CGlobals::Get().chatFont);
	auto lines = uiLastLine - uiFirstLine;
	for (unsigned int i = uiFirstLine; i < uiLastLine; i++) {
		ImGui::TextColored(ImVec4(vChatLines[i].structColor.red, vChatLines[i].structColor.green, vChatLines[i].structColor.blue, vChatLines[i].structColor.alpha), (char*)vChatLines[i].sLineText.c_str());
		//CGlobals::Get().renderer->_RenderText(int(0.01f * 800), int(heightupdate * 600), vChatLines[i].structColor.red, vChatLines[i].structColor.green, vChatLines[i].structColor.blue, vChatLines[i].structColor.alpha, 14.f, FW1_RESTORESTATE, (char*)vChatLines[i].sLineText.c_str());
	}
	
	ImGui::End();
	ImGui::PopStyleVar(2);

	if (bOpened)
	{
		//using convert_type = std::codecvt_utf8<wchar_t>;
		//std::wstring_convert<convert_type, wchar_t> converter;
		//std::wstring msgCopy(wsCurrentMessage);
		//msgCopy.insert(msgCopy.begin() + uiCarretPos, L'_');
		//std::string converted_str = std::string("> ") + converter.to_bytes(msgCopy);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
		ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 0.f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		if (CChat::Get()->Opened())
			ShowCursor(TRUE);

		ImGui::SetNextWindowPos(ImVec2(0, 190), ImGuiSetCond_Always);
		ImGui::Begin("ChatInput", &bOpened, ImVec2(450, 50), .0f, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

		char buffer[256] = "";
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5.f, 2.f));
		ImGui::PushItemWidth(400);
		if (ImGui::InputText("", buffer, 256, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CharsNoBlank/* | ImGuiInputTextFlags_CallbackHistory*/))
		{
			if (buffer[0] == '/')
			{
				if (_commandProcess != nullptr)
				{
					if (_commandProcess(buffer) != 1)
					{
						/*RakNet::BitStream sendmessage;
						RakNet::RakString outStr(converted_str.c_str());

						sendmessage.Write((MessageID)ID_COMMAND_MESSAGE);
						sendmessage.Write(outStr);
						CNetworkConnection::Get()->client->Send(&sendmessage,HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);*/
					}
				}
			}
			strcpy_s(buffer, 256, "");
			ShowCursor(FALSE);
			Close();
		}
		if (bJustOpened)
		{
			bJustOpened = false;
			ShowCursor(TRUE);
			ImGui::SetKeyboardFocusHere(0);
		}
		ImGui::PopItemWidth();
		ImGui::PopStyleVar(6);
		ImGui::End();
	}
	ImGui::PopFont();
}

void CChat::Input()
{
	if (bOpened)
		UI::SET_PAUSE_MENU_ACTIVE(false);
}

void CChat::AddChatMessage(std::string text, unsigned int rgba)
{
	ChatLine tempLine;
	tempLine.structColor = {
		((rgba >> 24) & 0xFF),
		((rgba >> 16) & 0xFF),
		((rgba >> 8) & 0xFF) ,
		((rgba) & 0xFF)
	};
	tempLine.sLineText = text;
	AddLine(tempLine);
}


void CChat::AddChatMessage(std::string text, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	ChatLine tempLine;
	tempLine.structColor = {
		red, green, blue, alpha
	};
	tempLine.sLineText = text;
	AddLine(tempLine);
}


void CChat::AddChatMessage(std::string text, color_t color)
{
	ChatLine tempLine;
	tempLine.structColor = color;
	tempLine.sLineText = text;
	AddLine(tempLine);
}

void CChat::Clear()
{
	vChatLines.clear();
	iOffset = 0;
}


void CChat::Toggle()
{
	if (bOpened)
		Close();
	else
		Open();
}


void CChat::Open()
{
	PLAYER::SET_PLAYER_CONTROL(PLAYER::PLAYER_ID(), false, 0);
	(*CGlobals::Get().canLangChange) = true;
	bOpened = true;
	bJustOpened = true;
}


void CChat::Close()
{
	PLAYER::SET_PLAYER_CONTROL(PLAYER::PLAYER_ID(), true, 0);
	(*CGlobals::Get().canLangChange) = false;
	bOpened = false;
}

void CChat::ScriptKeyboardMessage(DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow)
{
	CChat *Chat = CChat::Get();

	/*if (Chat->bOpened && (isUpNow || wasDownBefore) && (key != VK_RETURN && key != VK_BACK && key != VK_DELETE && key != VK_ESCAPE))
	{
		LPWSTR outChars = new WCHAR[4];
		BYTE keyState[256] = { 0 };
		if (!GetKeyboardState(keyState))
			return;
		int charsTranslated = ToUnicodeEx(key, scanCode, keyState, outChars, 4, 0, GetKeyboardLayout(NULL));
		if (charsTranslated > 0)
		{
			for (int i = 0; i < charsTranslated; ++i)
				Chat->wsCurrentMessage.insert(Chat->wsCurrentMessage.begin() + Chat->uiCarretPos, outChars[i]);
			Chat->uiCarretPos += charsTranslated;
		}
	}*/

	if (isUpNow || wasDownBefore)
	{
		switch (key)
		{
		case VK_ESCAPE:
			if (Chat->bOpened)
				Chat->Close();
			break;
		case VK_F6:
			Chat->Toggle();
			break;
		case VK_F7:
			Chat->bEnabled = !Chat->bEnabled;
			break;
		//case VK_RETURN:
		//	if (Chat->bOpened)
		//	{
		//		if (Chat->wsCurrentMessage.empty())
		//		{
		//			Chat->Close();
		//			break;
		//		}
		//		if (Chat->wsCurrentMessage[0] == L'/')
		//		{
		//			using convert_type = std::codecvt_utf8<wchar_t>;
		//			std::wstring_convert<convert_type, wchar_t> converter;
		//			std::string converted_str = converter.to_bytes(Chat->wsCurrentMessage);
		//			if (Chat->_commandProcess != nullptr)
		//			{
		//				if (Chat->_commandProcess(converted_str) == 1)
		//				{
		//					Chat->wsCurrentMessage.clear();
		//					Chat->Close();
		//					Chat->uiCarretPos = 0;
		//					break;
		//				}
		//				else
		//				{
		//					/*RakNet::BitStream sendmessage;
		//					RakNet::RakString outStr(converted_str.c_str());

		//					sendmessage.Write((MessageID)ID_COMMAND_MESSAGE);
		//					sendmessage.Write(outStr);
		//					CNetworkConnection::Get()->client->Send(&sendmessage,HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);*/

		//					Chat->wsCurrentMessage.clear();
		//					Chat->Close();
		//					Chat->uiCarretPos = 0;
		//					break;
		//				}
		//			}
		//		}
		//		using convert_type = std::codecvt_utf8<wchar_t>;
		//		std::wstring_convert<convert_type, wchar_t> converter;
		//		std::string converted_str = converter.to_bytes(Chat->wsCurrentMessage);

		//		/*RakNet::BitStream sendmessage;
		//		RakNet::RakString outStr(converted_str.c_str());

		//		sendmessage.Write((MessageID)ID_CHAT_MESSAGE);
		//		sendmessage.Write(outStr);
		//		CNetworkConnection::Get()->client->Send(&sendmessage, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);*/

		//		Chat->wsCurrentMessage.clear();
		//		Chat->Close();
		//		Chat->uiCarretPos = 0;
		//	}
		//	break;
		/*case VK_LEFT:
			if (!Chat->bOpened)
				break;
			if (Chat->uiCarretPos > 0)
				Chat->uiCarretPos--;
			break;
		case VK_RIGHT:
			if (!Chat->bOpened)
				break;
			if (Chat->uiCarretPos < Chat->wsCurrentMessage.length())
				Chat->uiCarretPos++;
			break;
		case VK_BACK:
			if (!Chat->bOpened)
				break;
			if (Chat->uiCarretPos > 0)
			{
				Chat->wsCurrentMessage.erase(Chat->wsCurrentMessage.begin() + (Chat->uiCarretPos - 1), Chat->wsCurrentMessage.begin() + Chat->uiCarretPos);
				Chat->uiCarretPos--;
			}
			break;
		case VK_DELETE:
			if (!Chat->bOpened)
				break;
			if (Chat->uiCarretPos < Chat->wsCurrentMessage.length())
			{
				Chat->wsCurrentMessage.erase(Chat->wsCurrentMessage.begin() + Chat->uiCarretPos, Chat->wsCurrentMessage.begin() + Chat->uiCarretPos + 1);
			}
			break;
		case VK_PRIOR:
			if (!Chat->bOpened)
				break;
			Chat->Scroll(SCROLL_UP);
			break;
		case VK_NEXT:
			if (!Chat->bOpened)
				break;
			Chat->Scroll(SCROLL_DOWN);
			break;*/
		}
	}
}