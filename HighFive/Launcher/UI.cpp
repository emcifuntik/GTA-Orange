#include "stdafx.h"
#include "Natives.h"

CUI::CUI()
{
}


CUI::~CUI()
{
}

void CUI::SendNotification(std::string text)
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING3((char*)text.c_str());
	UI::_DRAW_NOTIFICATION(FALSE, TRUE);
}

void CUI::PrintText(std::string text, float posx, float posy, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, float size, bool center)
{
	auto viewPortGame = GTA::CViewportGame::Get();
	CGlobals::Get().DX11Renderer->RenderText(viewPortGame->Width * posx, viewPortGame->Height * posy, red, green, blue, alpha, true, text.c_str());
}
