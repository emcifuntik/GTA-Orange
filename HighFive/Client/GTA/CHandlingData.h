#pragma once

namespace GTA
{
	class CAICurvePointWrapper;
	class CAICurvePoint;
	class CAIHandlingInfo;
	class CAICurvePointList;
	class CHandlingData;
	class CVehiclePassengers;
	class CCarLooks;
	class CCarInfo;


	class CAICurvePointWrapper
	{
	public:
		CAICurvePoint* ptrAICurvePoint; //0x0000 

	};//Size=0x0008


	class CAICurvePoint
	{
	public:
		char _0x0000[8];
		float fAngle; //0x0008 
		float fSpeed; //0x000C 

	};//Size=0x0010


	class CAIHandlingInfo
	{
	public:
		char _0x0000[8];
		DWORD dwAIHandlingHash; //0x0008 verified
		float fMinBrakeDistance; //0x000C 
		float fMaxBrakeDistance; //0x0010 
		float fMaxSpeedAtBrakeDistnace; //0x0014 
		float fMinVelocity; //0x0018 
		char _0x001C[4];
		CAICurvePointList* ptrAICurvePoints; //0x0020 
		__int16 iCurvePointCount1; //0x0028 
		__int16 iCurvePointCount2; //0x002A 
		char _0x002C[4];

	};//Size=0x0030


	class CAICurvePointList
	{
	public:
		CAICurvePointWrapper aAICurvePointWrappers[8]; //0x0000 
		char _0x0040[8];

	};//Size=0x0048


	class CHandlingData
	{
	public:
		char _0x0000[8];
		DWORD dwHandlingNameHash; //0x0008 
		float fMass; //0x000C  verified (mass in Kg)
		char _0x0010[16];
		CVector3 vecCentreOfMassOffset; //0x0020   verified (between -10 and 10)
		char _0x002C[4];
		CVector3 vecInertiaMultiplier; //0x0030  verified (between -10 and 10)
		float N0000228C; //0x003C maybe vec3x again?
		float fPercentSubmerged; //0x0040  verified (10 to 120, drag coeff proportional to velocity squared)
		float N0000227D; //0x0044 
		float N000021CC; //0x0048 
		float nDriveBias; //0x004C  (1.0 = fwd, 0.0 = rwd, 0.5 = 4x4)
		BYTE nInitialDiveGears; //0x0050  verified (number of gears, excluding reverse)
		char _0x0051[3];
		float fDriveInertia; //0x0054  (between 0 and 1, lower=slower accel)
		float fClutchChangeRateScaleUpShift; //0x0058 (speed multiplier on up shifts)
		float fClutchChangeRateScaleDownShift; //0x005C (speed multiplier on down shifts)
		float fInitialDriveForce; //0x0060 
		float fInitialDriveMaxFlatVel; //0x0064 
		float fSteeringLock; //0x0068  GUESSING (max wheel angle of outer wheel at low speed)
		float fBrakeForce; //0x006C verified (higher=faster stop)
		DWORD dwUnknown1; //0x0070 
		float N0000229A; //0x0074 fSuspensionCompDamp?
		float N000021D2; //0x0078 
		float fHandBrakeForce; //0x007C 
		float fSteeringLock2; //0x0080  (angle to restrict turning, between 0 and 1 suggested)
		float N0000229E; //0x0084 
		float fTractionCurveMax; //0x0088  (formally fTractionMult)
		float m_fAcceleration; //0x008C 
		float fTractionCurveMin; //0x0090  (formally fTractionLoss)
		float fInitialDragCoeff; //0x0094 
		float N000021D6; //0x0098 
		float m_fGrip; //0x009C 
		float fTractionSpringDeltaMax; //0x00A0 
		float N000022A6; //0x00A4 
		float fLowSpeedTractionLostMult; //0x00A8 
		float fCamberStiffness; //0x00AC GUESSING
		float N000021D9; //0x00B0 
		float N000022AA; //0x00B4 
		float fTractionLossMult; //0x00B8 verified
		float fSuspensionForce; //0x00BC  verified (1/(Force*NumWheels)) = Lower limit for zero force at full extension)
		float funknown; //0x00C0  fSuspensionCompDamp? *10?
		float fSuspensionReboundDamp; //0x00C4  unlikely unless *10
		float fSuspensionUpperLimit; //0x00C8  verified (visual limit of how far wheels can move up from orig pos)
		float fSuspensionLowerLimit; //0x00CC  verified (visual limit of how far wheels can move down from orig pos)
		float N000021DD; //0x00D0 fSuspensionRaise?
		float N000022B2; //0x00D4 
		float N000021DE; //0x00D8 
		float fAntiRollBarForce; //0x00DC ?
		float fUnknown3; //0x00E0 ?
		float fUnknown2; //0x00E4 ?
		float fRollCentreHeightFront; //0x00E8 verified
		float fRollCentreHeightRear; //0x00EC verified
		float fCollisionDamageMult; //0x00F0 verified
		float fWeaponDamageMult; //0x00F4 verified
		float fDeformationDamageMult; //0x00F8 verified
		float fEngineDamageMult; //0x00FC verified
		float fPetrolTankVolume; //0x0100  verified (for damage)
		float fOilVolume; //0x0104  verified (for damage)
		float N000021E4; //0x0108 
		float fSeatOffsetDistX; //0x010C 
		float fSeatOffsetDistY; //0x0110 verified
		float fSeatOffsetDistZ; //0x0114 
		DWORD dwMonetaryValue; //0x0118 verified
		DWORD dwStrModelFlags; //0x011C verified
		DWORD dwStrHandlingFlags; //0x0120 probable
		DWORD dwStrDamageFlags; //0x0124 probable
		DWORD N0000256D; //0x0128 
		DWORD N00002575; //0x012C 
		DWORD N000021E9; //0x0130 
		DWORD dwAIHandlingHash; //0x0134 verified
		float N000021EA; //0x0138 
		float N000025C4; //0x013C 
		char _0x0140[8];
		CAIHandlingInfo* ptrAIHandling; //0x0148 
		char _0x0150[16];
		float N000021EF; //0x0160 
		char _0x0164[12];
		void* ptrUnknown; //0x0170 
		float fBackEndPopUpCarImpulseMult; //0x0178 
		float fBackEndPopUpBuildingImpulseMult; //0x017C 
		float fBackEndPopUpMaxDeltaSpeed; //0x0180 
		char _0x0184[700];

	};//Size=0x0440


	class CVehiclePassengers
	{
	public:
		//CPed aVehiclePassengers[15]; //0x0000 
	};//Size=0x11850


	//class CAutomobile : public CEntity
	//{
	//public:
	//	char _0x00A0[608];
	//	CVector4 N00001347; //0x0300 
	//	char _0x0310[96];
	//	CVector4 N00001355; //0x0370 
	//	char _0x0380[136];
	//	__int32 N00001368; //0x0408 
	//	char _0x040C[24];
	//	__int32 N0000266A; //0x0424 
	//	__int32 N0000136C; //0x0428 
	//	char _0x042C[4];
	//	float N0000136D; //0x0430 
	//	float N00002678; //0x0434 
	//	char _0x0438[8];
	//	float N0000136F; //0x0440 
	//	char _0x0444[4];
	//	float N00001370; //0x0448 
	//	char _0x044C[4];
	//	float N00001371; //0x0450 
	//	char _0x0454[4];
	//	float N00001372; //0x0458 
	//	char _0x045C[4];
	//	float N00001373; //0x0460 
	//	char _0x0464[12];
	//	float N00001375; //0x0470 
	//	char _0x0474[12];
	//	float N00001377; //0x0480 
	//	char _0x0484[4];
	//	float N00001378; //0x0488 
	//	char _0x048C[4];
	//	float N00001379; //0x0490 
	//	char _0x0494[44];
	//	float N0000139B; //0x04C0 
	//	char _0x04C4[4];
	//	float N0000139C; //0x04C8 
	//	char _0x04CC[4];
	//	float N0000139D; //0x04D0 
	//	char _0x04D4[4];
	//	float N0000139E; //0x04D8 
	//	char _0x04DC[4];
	//	float N0000139F; //0x04E0 
	//	char _0x04E4[4];
	//	float N000013A0; //0x04E8 
	//	char _0x04EC[4];
	//	float N000013A1; //0x04F0 
	//	char _0x04F4[4];
	//	float N000013A2; //0x04F8 
	//	char _0x04FC[28];
	//	float N000013A6; //0x0518 
	//	float N000026A8; //0x051C 
	//	char _0x0520[40];
	//	float N000013AC; //0x0548 
	//	float N000026B7; //0x054C 
	//	float N000013AD; //0x0550 
	//	float N000026B5; //0x0554 
	//	float N000013AE; //0x0558 
	//	float N000026B3; //0x055C 
	//	char _0x0560[8];
	//	float N000013B0; //0x0568 
	//	float N000026B1; //0x056C 
	//	float N000013B1; //0x0570 
	//	float N000026AF; //0x0574 
	//	float N000013B2; //0x0578 
	//	char _0x057C[4];
	//	float N000013B3; //0x0580 
	//	float N000026AB; //0x0584 
	//	char _0x0588[8];
	//	DWORD N000013B5; //0x0590 
	//	char _0x0594[20];
	//	__int32 N000013B8; //0x05A8 
	//	float N000026C4; //0x05AC 
	//	char _0x05B0[16];
	//	float N000013BB; //0x05C0 
	//	float N000026BF; //0x05C4 
	//	float N000013BC; //0x05C8 
	//	char _0x05CC[4];
	//	CHandlingData* ptrHandlingData2; //0x05D0 
	//	char _0x05D8[88];
	//	void *ptrSelf; //0x0630 
	//	char _0x0638[116];
	//	float N0000270B; //0x06AC 
	//	char _0x06B0[32];
	//	float N000013DD; //0x06D0 
	//	char _0x06D4[132];
	//	void *ptrSelf2; //0x0758 
	//	float N000013EF; //0x0760 
	//	float N00002719; //0x0764 
	//	float fCarHealth1; //0x0768 
	//	float N0000209E; //0x076C 
	//	char _0x0770[40];
	//	float N000013F6; //0x0798 
	//	float N00002723; //0x079C 
	//	float N000013F7; //0x07A0 
	//	float N0000271F; //0x07A4 
	//	float N000013F8; //0x07A8 
	//	float N00002721; //0x07AC 
	//	char _0x07B0[8];
	//	float N000013FA; //0x07B8 
	//	float N0000272A; //0x07BC 
	//	float N000013FB; //0x07C0 
	//	float N00002728; //0x07C4 
	//	float N000013FC; //0x07C8 
	//	char _0x07CC[4];
	//	float N000013FD; //0x07D0 
	//	char _0x07D4[40];
	//	float fCarHealth2; //0x07FC 
	//	char _0x0800[16];
	//	float N00001405; //0x0810 
	//	float N0000272E; //0x0814 
	//	float N00001406; //0x0818 
	//	char _0x081C[4];
	//	CHandlingData* ptrHandlingData; //0x0820 
	//	char _0x0828[3];
	//	BYTE bBulletProofTires; //0x082B 0x2C - On; 0x0C - Off
	//	char _0x082C[348];
	//	WORD wVehicleAlarmDuration; //0x0988 
	//	char _0x098A[38];
	//	CVector4 vec4Rotation; //0x09B0 GUESSING
	//	char _0x09C0[64];
	//	CVector3 vec3Acceleration; //0x0A00 
	//	char _0x0A0C[228];
	//	BYTE bMaxNumberOfPassengers; //0x0AF0 
	//	char _0x0AF1[7];
	//	CVehiclePassengers* ptrPassengersLink; //0x0AF8 

	//}; //Size=0x0B00

	// This was MOSTLY taken from someone else, but I added a few to it and I don't feel like picking it apart right now.

	class CCarLooks
	{
	public:
		char _0x0000[120];
		BYTE N000020BD; //0x0078 
		BYTE N00002137; //0x0079 
		BYTE N0000213B; //0x007A 
		BYTE N0000213E; //0x007B 
		BYTE N0000213C; //0x007C 
		BYTE N00002138; //0x007D 
		BYTE N00002141; //0x007E 
		BYTE N00002139; //0x007F 
		BYTE N000020BE; //0x0080 
		BYTE N00002149; //0x0081 
		char _0x0082[6];
		BYTE N000020BF; //0x0088 
		char _0x0089[19];
		BYTE N0000215C; //0x009C 
		BYTE N0000215F; //0x009D 
		BYTE N0000215A; //0x009E 
		BYTE N00002162; //0x009F 
		BYTE bPaintB; //0x00A0 
		BYTE bPaintG; //0x00A1 
		BYTE bPaintR; //0x00A2 
		BYTE N0000216A; //0x00A3 
		BYTE bSecondaryPaintB; //0x00A4 
		BYTE bSecondaryPaintG; //0x00A5 
		BYTE bSecondaryPaintR; //0x00A6 
		BYTE N00002174; //0x00A7 
		BYTE bChrome1; //0x00A8 
		BYTE bChrome2; //0x00A9 
		BYTE bChrome3; //0x00AA 
		BYTE N0000217D; //0x00AB 
		BYTE bWindowTintB; //0x00AC 
		BYTE bWindowTintG; //0x00AD 
		BYTE bWindowTintR; //0x00AE 
		BYTE N00002178; //0x00AF 
		BYTE N000020C4; //0x00B0 
		BYTE N00002186; //0x00B1 
		BYTE N0000218E; //0x00B2 
		BYTE N00002194; //0x00B3 
		BYTE N0000218F; //0x00B4 
		BYTE N00002187; //0x00B5 
		BYTE N00002191; //0x00B6 
		BYTE N00002188; //0x00B7 
		BYTE N000020C5; //0x00B8 
		BYTE N0000218A; //0x00B9 
		BYTE N0000219A; //0x00BA 
		BYTE bWindowTint3; //0x00BB 
		BYTE N0000219B; //0x00BC 
		BYTE N0000218B; //0x00BD 
		BYTE N000021A1; //0x00BE 
		BYTE N0000218C; //0x00BF 
		BYTE bChromeTypePrimary; //0x00C0 7=super chrome
		BYTE bChromeTypeSecondary; //0x00C1 
		BYTE N000021A8; //0x00C2 
		BYTE N000021B7; //0x00C3 
		BYTE N000021A9; //0x00C4 
		BYTE N000021A5; //0x00C5 
		BYTE N000021AB; //0x00C6 
		BYTE N000021A6; //0x00C7 
		BYTE N000020C7; //0x00C8 
		BYTE N000021AE; //0x00C9 
		BYTE N000021B2; //0x00CA 

	};//Size=0x00CB  

	class CCarInfo
	{
	public:
		char _0x0000[32];
		CCarLooks* ptrCarLooks; //0x0020 
		char _0x0028[24];

	};//Size=0x0040
};