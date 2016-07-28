#pragma once

namespace Utils
{
	bool WorldToScreenRel(CVector3 worldCoords, Vector2 & screenCoords);
	CVector3 ScreenRelToWorld(CVector3 camPos, CVector3 camRot, Vector2 coord);
	CVector3 RotationToDirection(CVector3 rotation);
	CVector3 DirectionToRotation(CVector3 direction);
	double DegToRad(double deg);
	double RadToDeg(double deg);
	double BoundRotationDeg(double angleDeg);
	unsigned int Hash(char * inpStr);
}

