#include "stdafx.h"

CUI::CUI()
{
}


CUI::~CUI()
{
}

void CUI::PrintText(std::string text, float posx, float posy, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, float size, bool center)
{
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_0x5F68520888E69014((char*)(text.c_str()));
	UI::SET_TEXT_FONT(0);
	UI::SET_TEXT_SCALE(size, size);
	UI::SET_TEXT_COLOUR(red, green, blue, alpha);
	UI::SET_TEXT_WRAP(0.0, 1.0);
	UI::SET_TEXT_CENTRE(center);
	UI::SET_TEXT_DROPSHADOW(1, 0, 0, 0, 100);
	UI::SET_TEXT_EDGE(0, 0, 0, 0, 100);
	UI::SET_TEXT_LEADING(1);
	UI::_DRAW_TEXT(posx, posy);
}
