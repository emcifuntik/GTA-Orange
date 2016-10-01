#include "stdafx.h"

//bool Utils::WorldToScreenRel(CVector3 worldCoords, CVector2& screenCoords)
//{
//	float num1, num2;
//
//	if (GRAPHICS::_WORLD3D_TO_SCREEN2D, worldCoords.fX, worldCoords.fY, worldCoords.fZ, &num1, &num2)
//	{
//		screenCoords = CVector2();
//		return false;
//	}
//	screenCoords = CVector2((num1 - 0.5f) * 2, (num2 - 0.5f) * 2);
//	return true;
//}
//
//CVector3 Utils::ScreenRelToWorld(CVector3 camPos, CVector3 camRot, CVector2 coord)
//{
//	auto camForward = RotationToDirection(camRot);
//	auto rotUp = camRot + CVector3(10.f, 0, 0);
//	auto rotDown = camRot + CVector3(-10.f, 0, 0);
//	auto rotLeft = camRot + CVector3(0, 0, -10.f);
//	auto rotRight = camRot + CVector3(0, 0, 10.f);
//
//	auto camRight = RotationToDirection(rotRight) - RotationToDirection(rotLeft);
//	auto camUp = RotationToDirection(rotUp) - RotationToDirection(rotDown);
//
//	auto rollRad = -DegToRad(camRot.fY);
//
//	auto camRightRoll = camRight * (float)std::cos(rollRad) - camUp * (float)std::sin(rollRad);
//	auto camUpRoll = camRight * (float)std::sin(rollRad) + camUp * (float)std::cos(rollRad);
//
//	auto point3D = camPos + camForward * 100.f + camRightRoll + camUpRoll;
//	CVector2 point2D;
//	if (!WorldToScreenRel(point3D, point2D)) return camPos + camForward * 100.f;
//	auto point3DZero = camPos + camForward * 100.0f;
//	CVector2 point2DZero;
//	if (!WorldToScreenRel(point3DZero, point2DZero)) return camPos + camForward * 100.f;
//
//	const double eps = 0.0000001;
//	if (std::abs(point2D.fX - point2DZero.fX) < eps || std::abs(point2D.fY - point2DZero.fY) < eps) return camPos + camForward * 100.f;
//	auto scaleX = (coord.fX - point2DZero.fX) / (point2D.fX - point2DZero.fX);
//	auto scaleY = (coord.fY - point2DZero.fY) / (point2D.fY - point2DZero.fY);
//	auto point3Dret = camPos + camForward * 100.f + camRightRoll * scaleX + camUpRoll * scaleY;
//	return point3Dret;
//}
//
//CVector3 Utils::RotationToDirection(CVector3 rotation)
//{
//	auto z = DegToRad(rotation.fZ);
//	auto x = DegToRad(rotation.fX);
//	auto num = std::abs(std::cos(x));
//	return CVector3((float)(-std::sin(z) * num), (float)(std::cos(z) * num), (float)std::sin(x));
//}
//
//CVector3 Utils::DirectionToRotation(CVector3 direction)
//{
//	direction.Normalize();
//
//	auto x = std::atan2(direction.fZ, direction.fY);
//	auto y = 0;
//	auto z = -std::atan2(direction.fX, direction.fY);
//
//	return CVector3((float)RadToDeg(x), (float)RadToDeg(y), (float)RadToDeg(z));
//}
//
//double Utils::DegToRad(double deg)
//{
//	return deg * PI / 180.0;
//}
//
//double Utils::RadToDeg(double deg)
//{
//	return deg * 180.0 / PI;
//}
//
//double Utils::BoundRotationDeg(double angleDeg)
//{
//	auto twoPi = (int)(angleDeg / 360);
//	auto res = angleDeg - twoPi * 360;
//	if (res < 0) res += 360;
//	return res;
//}

unsigned int Utils::Hash(const char* inpStr)
{
	unsigned int value = 0, temp = 0;
	for (size_t i = 0; i<strlen(inpStr); i++)
	{
		temp = tolower(inpStr[i]) + value;
		value = temp << 10;
		temp += value;
		value = temp >> 6;
		value ^= temp;
	}
	temp = value << 3;
	temp += value;
	unsigned int temp2 = temp >> 11;
	temp = temp2 ^ temp;
	temp2 = temp << 15;
	value = temp2 + temp;
	if (value < 2) value += 2;
	return value;
}
//
//bool Utils::IsValidPtr(PVOID Ptr)
//{
//	if (!Ptr)
//		return 0;
//	MEMORY_BASIC_INFORMATION info = { 0 };
//
//	VirtualQuery(Ptr, &info, 1);
//
//	if (info.Protect | PAGE_READONLY)
//		return 1;
//
//	return 0;
//}
//
//bool Utils::IsSteam()
//{
//	return !(getGameVersion() % 2);
//}

int Utils::RoundToBytes(int bits)
{
	return (bits % 8) ? (bits / 8 + 1) : (bits / 8);
}

DWORD Utils::RGBAToHex(BYTE r, BYTE g, BYTE b, BYTE a)
{
	return ((r & 0xff) << 24) + ((g & 0xff) << 16) + ((g & 0xff) << 8) + (a & 0xff);
}
