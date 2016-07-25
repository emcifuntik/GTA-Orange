#pragma once

class OnFootSyncData
{
public:
	//CControlState controlState;		// control state
	Hash hModel;						// player model
	float fMoveSpeed;
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
	bool bAiming : 1;
	bool bShooting : 1;
	bool bReloading : 1;
	CVector3 vecAim;

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
			"BlendRatio: " << fMoveSpeed << std::endl <<
			"Jumping: " << (bJumping ? "true" : "false") << std::endl <<
			"Aiming: " << (bAiming ? "true" : "false") << std::endl <<
			"Shooting: " << (bShooting ? "true" : "false") << std::endl <<
			"Aim pos: X = " << vecAim.fX << ", Y = " << vecAim.fY << ", Z = " << vecAim.fZ << std::endl <<
			"Player model: " << hModel << std::endl;
		return ss.str();
	}
};

class VehicleData
{
public:
	RakNet::RakNetGUID GUID;
	RakNet::RakNetGUID driver;			// vehicle driver
	Hash hashModel;						// vehicle model
	CVector3 vecPos;					// vehicle position
	CVector3 vecRot;					// vehicle rotation
	CVector3 vecMoveSpeed;				// vehicle move speed
	unsigned short int usHealth : 16;	// vehicle health 
	bool bTaxiLights : 1;				// vehicle taxi lights
	bool bSirenState : 1;				// vehicle siren state
	float iDirtLevel;					// vehicle dirt level

	std::string ToString()
	{
		std::stringstream ss;
		ss << "Position: X = " << vecPos.fX << ", Y = " << vecPos.fY << ", Z = " << vecPos.fZ << std::endl <<
			"Rotation: X = " << vecRot.fY << ", Y = " << vecRot.fY << ", Z = " << vecRot.fZ << std::endl <<
			"Velocity: X = " << vecMoveSpeed.fX << ", Y = " << vecMoveSpeed.fY << ", Z = " << vecMoveSpeed.fY << std::endl <<
			"Health: " << usHealth << std::endl <<
			"Model: 0x" << std::hex << hashModel << std::endl <<
			"Driver: " << driver.ToString() << std::endl <<
			"Taxi lights: " << (bTaxiLights ? "true" : "false") << std::endl <<
			"Siren state: " << (bSirenState ? "true" : "false") << std::endl <<
			"Dirt level: " << iDirtLevel << std::endl;
		return ss.str();
	}
};