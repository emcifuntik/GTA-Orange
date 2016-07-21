#pragma once

class OnFootSyncData
{
public:
	//CControlState controlState;		// control state
	float fBlendRatio;
	CVector3 vecPos;					// player position
	CVector3 vecRot;					// player rotation
	float fHeading;						// player heading
	CVector3 vecMoveSpeed;				// player move speed
	CVector3 vecTurnSpeed;				// player turn speed
	bool bDuckState : 1;				// ducking
	bool bJumping : 1;					// jumping
	unsigned short int usHealth : 16;	// player health 
	unsigned short int usArmour : 16;	// player armor
	unsigned long ulWeapon;				// player weapon and ammo
	unsigned int uAmmo;					// player weapon and ammo

	std::string ToString()
	{
		std::stringstream ss;
		ss << "Position: X = " << vecPos.fX << ", Y = " << vecPos.fY << ", Z = " << vecPos.fZ << std::endl <<
			"Rotation: X = " << vecRot.fY << ", Y = " << vecRot.fY << ", Z = " << vecRot.fZ << std::endl <<
			"Heading: " << fHeading << std::endl <<
			"Velocity: X = " << vecMoveSpeed.fX << ", Y = " << vecMoveSpeed.fY << ", Z = " << vecMoveSpeed.fY << std::endl <<
			"Rotation velocity: X = " << vecTurnSpeed.fX << ", Y = " << vecTurnSpeed.fY << ", Z = " << vecTurnSpeed.fZ << std::endl <<
			"DuckState: " << (bDuckState ? "true" : "false") << std::endl <<
			"Health: " << usHealth << std::endl <<
			"Armour: " << usArmour << std::endl <<
			"Weapon: " << ulWeapon << std::endl <<
			"Ammo: " << uAmmo << std::endl <<
			"BlendRatio: " << fBlendRatio << std::endl <<
			"Jumping: " << bJumping << std::endl;
		return ss.str();
	}
};