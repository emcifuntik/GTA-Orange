#pragma once
class CUI
{
public:
	CUI();
	~CUI();
	static void PrintText(std::string text, float posx, float posy, unsigned char red = 255, unsigned char green = 255, unsigned char blue = 255, unsigned char alpha = 255, float size = .4f, bool center = false);
};

