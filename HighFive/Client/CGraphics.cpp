#include "stdafx.h"

CGraphics * CGraphics::singleInstance = nullptr;

CGraphics * CGraphics::Get()
{
	if (!singleInstance)
		singleInstance = new CGraphics();
	return singleInstance;
}


bool CGraphics::WorldToScreen(float worldX, float worldY, float worldZ, float & screenX, float & screenY)
{
	return (GRAPHICS::_WORLD3D_TO_SCREEN2D(worldX, worldY, worldZ, &screenX, &screenY) ? true : false);
}

void CGraphics::Draw3DText(std::string text, float size, float x, float y, float z, color_t color)
{
	float screenX, screenY;
	WorldToScreen(x, y, z, screenX, screenY);
	CUI::PrintText(text, screenX, screenY, color.red, color.green, color.blue, color.alpha, size, true);
}

void CGraphics::Draw3DProgressBar(color_t bgColor, color_t frontColor, float width, float height, float x, float y, float z, float value)
{
	if (value > 1.f)
		value = 1.f;
	float screenX, screenY;
	WorldToScreen(x, y, z, screenX, screenY);
	screenY += 0.045f;
	GRAPHICS::DRAW_RECT(screenX, screenY, width, height, bgColor.red, bgColor.green, bgColor.blue, bgColor.alpha);
	float frontWidth = width * 0.98f;
	float frontHeight = height * 0.8f;
	float frontX = screenX + ((width - frontWidth) / 8.f) - ((frontWidth*(1.f - value))/2.f);
	float frontY = screenY + ((height - frontHeight) / 8.f);
	GRAPHICS::DRAW_RECT(frontX, frontY, frontWidth * value, frontHeight, frontColor.red, frontColor.green, frontColor.blue, frontColor.alpha);
}

CGraphics::~CGraphics()
{
}
