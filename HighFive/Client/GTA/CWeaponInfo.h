#pragma once

namespace GTA
{
	class CWeaponManager;
	class CAmmoInfo;
	class CAmmoProjectileInfo;
	class CAimingInfo;
	class CBoneForces;
	class CBoneForce;
	class CWeaponAttachPoints;
	class CWeaponAttachBoneComponent;
	class CWeaponInfo;

	class CWeaponManager
	{
	public:
		char _0x0000[24];
		DWORD dwCurWeaponNameHash; //0x0018
		char _0x001C[4];
		CWeaponInfo* ptrCurrentWeapon; //0x0020
		char _0x0028[64];

	};//Size=0x0068

	class CAmmoProjectileInfo
	{
	public:
		float fDamage; //0x0000
		float fLifeTime; //0x0004
		float fFromVehicleLifeTime; //0x0008
		float fLifeTimeAfterImpact; //0x000C
		float fLifeTimeAfterExplosion; //0x0010
		float fExplosionTime; //0x0014
		float fLaunchSpeed; //0x0018
		float fSeparationTime; //0x001C
		float fTimeToReachTarget; //0x0020
		float fDamping; //0x0024
		float fGravityFactor; //0x0028
		float fRicochetTolerance; //0x002C
		float fPedRicochetTolerance; //0x0030
		float fVehicleRicochetTolerance; //0x0034
		float fFrictionMultiplier; //0x0038
		DWORD dwExplosionDefault; //0x003C
		DWORD dwExplosionHitCar; //0x0040
		DWORD dwExplosionHitTruck; //0x0044
		DWORD dwExplosionHitBike; //0x0048
		DWORD dwExplosionHitBoat; //0x004C
		DWORD dwExplosionHitPlane; //0x0050
		DWORD dwFuseFxHash; //0x0054
		DWORD dwTrailFxHash; //0x0058
		DWORD dwTrailFxUnderWaterHash; //0x005C
		float fTrailFxFadeInTime; //0x0060
		float fTrailFxFadeOutTime; //0x0064
		DWORD dwPrimedFxHash; //0x0068
		DWORD dwDisturbFxDefaultHash; //0x006C
		DWORD dwDisturbFxSandHash; //0x0070
		DWORD dwDisturbFxWaterHash; //0x0074
		DWORD dwDisturbFxDirtHash; //0x0078
		DWORD dwDisturbFxFoliageHash; //0x007C
		float fDisturbFxProbeDist; //0x0080
		float fDisturbFxScale; //0x0084
		char _0x0088[24];
		CVector3 vec3LightColour; //0x00A0
		char _0x00AC[4];
		float fLightIntensity; //0x00B0
		float fLightRange; //0x00B4
		float fLightFalloffExp; //0x00B8
		float fLightFrequency; //0x00BC
		float fLightPower; //0x00C0
		float fCoronaSize; //0x00C4
		float fCoronaIntensity; //0x00C8
		float fCoronaZBias; //0x00CC
		char _0x00D0[16];
		DWORD dwProjectileFlags; //0x00E0 (Seems to be wrong)
		char _0x00E4[12];
		float fForwardDragCoeff; //0x00F0
		float fSideDragCoeff; //0x00F4
		float fTimeBeforeHoming; //0x00F8
		float fTimeBeforeSwitchTargetMin; //0x00FC
		float fTimeBeforeSwitchTargetMax; //0x0100
		float fProximityRadius; //0x0104
		float fPitchChangeRate; //0x0108
		float fYawChangeRate; //0x010C
		float fRollChangeRate; //0x0110
		float fMaxRollAngleSin; //0x0114

	};//Size=0x0118

	class CAmmoInfo
	{
	public:
		char _0x0000[16];
		DWORD dwAmmoNameHash; //0x0010
		DWORD dwAmmoModelHash; //0x0014
		DWORD dwAmmoAudio; //0x0018
		DWORD dwAmmoSlot; //0x001C
		__int32 iAmmoMax; //0x0020
		__int32 iAmmoMax50; //0x0024
		__int32 iAmmoMax100; //0x0028
		__int32 iAmmoMaxMP; //0x002C
		__int32 iAmmoMax50MP; //0x0030
		__int32 iAmmoMax100MP; //0x0034
		BYTE bAmmoFlags; //0x0038
		char _0x0039[7];
		CAmmoProjectileInfo projectileInfo; //0x0040

	};//Size=0x0158

	class CAimingInfo
	{
	public:
		DWORD dwNameHash; //0x0000
		float fHeadingLimit; //0x0004
		float fSweepPitchMin; //0x0008
		float fSweepPitchMax; //0x000C

	};//Size=0x0010

	class CBoneForce
	{
	public:
		DWORD dwBoneTag; //0x0000
		float fForceFront; //0x0004
		float fForceBack; //0x0008

	};//Size=0x000C

	class CBoneForces
	{
	public:
		CBoneForce arrBones[6]; //0x0000
	};//Size=0x0048

	class CWeaponAttachBoneComponent
	{
	public:
		DWORD N22127501; //0x0000
		__int32 N2212E47E; //0x0004

	};//Size=0x0008

	class CWeaponAttachPoints
	{
	public:
		DWORD dwAttachBoneHash; //0x0000
		char _0x0004[4];
		CWeaponAttachBoneComponent N21B9B834[6]; //0x0008 
		__int32 iComponentCount; //0x0038

	};//Size=0x003C

	class CWeaponInfo
	{
	public:
		char _0x0000[16];
		DWORD dwNameHash; //0x0010
		DWORD dwModelHash; //0x0014
		DWORD dwAudioHash; //0x0018
		DWORD dwSlotHash; //0x001C
		__int32 bDamageType; //0x0020
		DWORD dwExplosionDefault; //0x0024
		DWORD dwExplosionHitCar; //0x0028
		DWORD dwExplosionHitTruck; //0x002C
		DWORD dwExplosionHitBike; //0x0030
		DWORD dwExplosionHitBoat; //0x0034
		DWORD dwExplosionHitPlane; //0x0038
		__int32 iWeaponFireType; //0x003C
		__int32 iWeaponWheelSlot; //0x0040
		DWORD dwGroupHash; //0x0044
		CAmmoInfo* ptrAmmoInfo; //0x0048
		CAimingInfo* ptrWeaponAimingInfo; //0x0050
		__int32 iClipSize; //0x0058
		float fAccuracySpread; //0x005C
		float fAccurateModeAccuracyModifier; //0x0060
		float fRunAndGunAccuracyModifier; //0x0064
		float fRunAndGunAccuracyMaxModifier; //0x0068
		float fRecoilAccuracyMax; //0x006C
		float fRecoilErrorTime; //0x0070
		float fRecoilRecoveryRate; //0x0074
		float fRecoilAccuracyToAllowHeadShotAI; //0x0078
		float fMinHeadShotDistanceAI; //0x007C
		float fMaxHeadShotDistanceAI; //0x0080
		float fHeadShotDamageModifierAI;
		float fRecoilAccuracyToAllowHeadShotPlayer; //0x0088
		float fMinHeadShotDistancePlayer; //0x008C
		float fMaxHeadShotDistancePlayer; //0x0090
		float fHeadShotDamageModifierPlayer; //0x0094
		float fDamage; //0x0098
		float fDamageTime; //0x009C
		float fDamageTimeInVehicle; //0x00A0
		float fDamageTimeInVehicleHeadShot; //0x00A4
		float fHitLimbsDamageModifier; //0x00A8
		float fNetworkHitLimbsDamageModifier; //0x00AC
		float fLightlyArmouredDamageModifier; //0x00B0
		float fForce; //0x00B4
		float fForce2; //0x00B8
		float fForceHitPed; //0x00BC
		float fForceHitVehicle; //0x00C0
		float fForceHitFlyingHeli; //0x00C4
		CBoneForces* ptrOverrideForces; //0x00C8
		__int16 iBoneForceFrontCount; //0x00D0
		__int16 iBoneForceBackCount; //0x00D2
		char _0x00D4[4];
		float fForceMaxStrengthMult; //0x00D8
		float fForceFalloffRangeStart; //0x00DC
		float fForceFalloffRangeEnd; //0x00E0
		float fForceFalloffMin; //0x00E4
		float fProjectileForce; //0x00E8
		float fFragImpulse; //0x00EC
		float fPenetration; //0x00F0
		float fVerticalLaunchAdjustment; //0x00F4
		float fDropForwardVelocity; //0x00F8
		float fSpeed; //0x00FC 
		__int32 iBulletsInBatch; //0x0100
		float fBatchSpread; //0x0104
		float fReloadTimeMP; //0x0108
		float fReloadTimeSP; //0x010C
		float fVehicleReloadTime; //0x0110
		float fAnimReloadRate; //0x0114
		__int32 iBulletsPerAnimLoop; //0x0118
		float fTimeBetweenShots; //0x011C
		float fTimeLeftBetweenShotsWhereShouldFireIsCached; //0x0120
		float fSpinUpTime; //0x0124
		float fSpinTime; //0x0128
		float fSpinDownTime; //0x012C
		float fAlternateWaitTime; //0x0130
		float fBulletBendingNearRadius; //0x0134
		float fBulletBendingFarRadius; //0x0138
		float fBulletBendingZoomedRadius; //0x013C
		float fFirstPersonBulletBendingNearRadius; //0x0140
		float fFirstPersonBulletBendingFarRadius; //0x0144
		float fFirstPersonBulletBendingZoomedRadius; //0x0148
		char _0x014C[4];
		__int32 fFxEffectGroup; //0x0150 (GUESSING - Need to map groups out)
		DWORD dwFxFlashFxHash; //0x0154
		DWORD dwFxFlashFxAltHash; //0x0158
		DWORD dwFxFlashFxFPHash; //0x015C
		DWORD dwFxFlashFxAltFPHash; //0x0160
		DWORD dwMuzzleSmokeFxHash; //0x0164
		DWORD dwMuzzleSmokeFxFPHash; //0x0168
		float fFxMuzzleSmokeFxMinLevel; //0x016C
		float fFxMuzzleSmokeFxIncPerShot; //0x0170
		float fFxMuzzleSmokeFxDecPerSec; //0x0174
		DWORD dwFxShellFxHash; //0x0178
		DWORD dwFxShellFxFP; //0x017C
		DWORD dwFxTracerFxHash; //0x0180
		DWORD dwFxPedDamageHash; //0x0184
		float fFxTracerFxChanceSP; //0x0188
		float fFxTracerFxChanceMP; //0x018C
		float fFxFlashFxChanceSP; //0x0190
		float fFxFlashFxChanceMP; //0x0194
		float fFxFlashFxAltChance; //0x0198
		float fFxFlashFxScale; //0x019C
		BYTE boolFxFlashFxLightEnabled; //0x01A0
		BYTE boolFxFlashFxLightCastsShadows; //0x01A1
		float fFxFlashFxLightOffsetDist; //0x01A2
		char _0x01A6[10];
		CVector3 vec3FxFlashFxLightRGBAMin; //0x01B0
		char _0x01BC[4];
		CVector3 vec3FxFlashFxLightRGBAMax; //0x01C0
		char _0x01CC[4];
		CVector2 vec2FxFlashFxLightIntensityMinMax; //0x01D0
		CVector2 vec2FxFlashFxLightRangeMinMax; //0x01D8
		CVector2 vec2FxFlashFxLightFalloffMinMax; //0x01E0
		BYTE boolFxGroundDisturbFxEnabled; //0x01E8
		char _0x01E9[3];
		float fFxGroundDisturbFxDist; //0x01EC
		DWORD dwFxGroundDisturbFxNameDefaultHash; //0x01F0
		DWORD dwFxGroundDisturbFxNameSandHash; //0x01F4
		DWORD dwFxGroundDisturbFxNameDirtHash; //0x01F8
		DWORD dwFxGroundDisturbFxNameWaterHash; //0x01FC
		char _0x0200[16];
		__int32 iInitialRumbleDuration; //0x0210
		float fInitialRumbleIntensity; //0x0214
		float fInitialRumbleIntensityTrigger; //0x0218
		__int32 iRumbleDuration; //0x021C
		float fRumbleIntensity; //0x0220
		float fRumbleIntensityTrigger; //0x0224
		float fRumbleDamageIntensity; //0x0228
		__int32 iInitialRumbleDurationFps; //0x022C
		float fInitialRumbleIntensityFps; //0x0230
		__int32 iRumbleDurationFps; //0x0234
		float fRumbleIntensityFps; //0x0238
		float fNetworkPlayerDamageModifier; //0x023C
		float fNetworkPedDamageModifier; //0x0240
		float fNetworkHeadShotPlayerDamageModifier; //0x0244
		float fLockOnRange; //0x0248
		float fWeaponRange; //0x024C
		float fAiSoundRange; //0x0250
		float fAiPotentialBlastEventRange; //0x0254
		float fDamageFallOffRangeMin; //0x0258
		float fDamageFallOffRangeMax; //0x025C
		char _0x0260[4];
		float fDamageFallOffModifier; //0x0264
		DWORD dwVehicleWeaponHash; //0x0268
		DWORD dwDefaultCameraHash; //0x026C
		char _0x0270[8];
		DWORD dwCoverCameraHash; //0x0278
		DWORD dwCoverReadyToFireCameraHash; //0x027C
		DWORD dwRunAndGunCameraHash; //0x0280
		DWORD dwCinematicShootingCameraHash; //0x0284
		char _0x0288[12];
		DWORD dwRecoilShakeHash; //0x0294
		DWORD dwRecoilShakeHashFirstPerson; //0x0298
		char _0x029C[4];
		__int32 iMinTimeBetweenRecoilShakes; //0x02A0
		float fRecoilShakeAmplitude; //0x02A4
		float fExplosionShakeAmplitude; //0x02A8
		float fCameraFov; //0x02AC
		float fFirstPersonAimFovMin; //0x02B0
		float fFirstPersonAimFovMax; //0x02B4
		float fFirstPersonScopeFov; //0x02B8
		float fFirstPersonScopeAttachmentFov; //0x02BC
		CVector3 N2178CA75; //0x02C0
		char _0x02CC[4];
		CVector3 N2178E6EE; //0x02D0
		char _0x02DC[4];
		CVector3 N218A9DE9; //0x02E0
		char _0x02EC[4];
		CVector3 N218AEA5B; //0x02F0
		char _0x02FC[4];
		CVector3 vec3FirstPersonScopeOffset; //0x0300
		char _0x030C[4];
		CVector3 vec3FirstPersonScopeAttachmentOffset; //0x0310
		char _0x031C[4];
		CVector3 N218BA3F9; //0x0320
		char _0x032C[4];
		CVector3 N218BA3FD; //0x0330
		char _0x033C[4];
		CVector3 vec3FirstPersonAsThirdPersonIdleOffset; //0x0340
		char _0x034C[4];
		CVector3 vec3FirstPersonScopeRotationOffset; //0x0350
		char _0x035C[4];
		CVector3 N218BD2FC; //0x0360
		char _0x036C[4];
		CVector3 vec3FirstPersonAsThirdPersonScopeOffset; //0x0370
		char _0x037C[4];
		CVector3 N218BD304; //0x0380
		char _0x038C[4];
		float fFirstPersonDofSubjectMagnificationPowerFactorNear; //0x0390
		float fFirstPersonDofMaxNearInFocusDistance; //0x0394
		float fFirstPersonDofMaxNearInFocusDistanceBlendLevel; //0x0398
		float fZoomFactorForAccurateMode; //0x039C
		CVector3 vec3AimOffsetMin; //0x03A0
		char _0x03AC[4];
		CVector3 vec3AimOffsetMax; //0x03B0
		char _0x03BC[4];
		CVector2 vec2TorsoAimOffset; //0x03C0
		CVector2 vec2TorsoCrouchedAimOffset; //0x03C8
		float fAimProbeLengthMin; //0x03D0
		float fAimProbeLengthMax; //0x03D4
		char _0x03D8[8];
		CVector3 vec3AimOffsetMinFPSIdle; //0x03E0
		char _0x03EC[4];
		CVector3 vec3AimOffsetMedFPSIdle; //0x03F0
		char _0x03FC[4];
		CVector3 vec3AimOffsetMaxFPSIdle; //0x0400
		char _0x040C[4];
		CVector3 vec3AimOffsetMinFPSLT; //0x0410
		char _0x041C[4];
		CVector3 vec3AimOffsetMaxFPSLT; //0x0420
		char _0x042C[4];
		CVector3 vec3AimOffsetMinFPSRNG; //0x0430
		char _0x043C[4];
		CVector3 vec3AimOffsetMaxFPSRNG; //0x0440
		char _0x044C[4];
		CVector3 vec3AimOffsetMinFPSScope; //0x0450
		char _0x045C[4];
		CVector3 vec3AimOffsetMaxFPSScope; //0x0460
		char _0x046C[4];
		CVector3 vec3AimOffsetEndPosMinFPSIdle; //0x0470
		char _0x047C[4];
		CVector3 vec3AimOffsetEndPosMedFPSIdle; //0x0480
		char _0x048C[4];
		CVector3 vec3AimOffsetEndPosMaxFPSIdle; //0x0490
		char _0x049C[84];
		CVector3 vec3LeftHandIkOffset; //0x04F0 (GUESSING)
		char _0x04FC[4];
		float fIkRecoilDisplacement; //0x0500
		float fIkRecoilDisplacementScope; //0x0504
		float fIkRecoilDisplacementScaleBackward; //0x0508
		float fIkRecoilDisplacementScaleVertical; //0x050C
		CVector2 vec2ReticuleHudPosition; //0x0510
		float fReticuleMinSizeStanding; //0x0518 (GUESSING)
		float fReticuleMinSizeCrouched; //0x051C (GUESSING)
		float fReticuleScale; //0x0520 (GUESSING)
		DWORD dwReticuleStyleHash; //0x0524
		char _0x0528[4];
		DWORD dwPickupHash; //0x052C
		DWORD dwMPPickupHash; //0x0530
		DWORD dwHumanNameHash; //0x0534
		char _0x0538[4];
		DWORD dwMovementModeConditionalIdleHash; //0x053C
		__int8 iAmmoDiminishingRate; //0x0540
		__int8 iHudDamage; //0x0541
		__int8 iHudSpeed; //0x0542
		__int8 iHudCapacity; //0x0543
		__int8 iHudAccuracy; //0x0544
		__int8 iHudRange; //0x0545
		char _0x0546[2];
		float N221C635B; //0x0548 (TODO)
		float N221B5712; //0x054C (TODO)
		float N220AD14F; //0x0550 (TODO)
		float N221C8BC7; //0x0554 (TODO)
		float N220AD43E; //0x0558 (TODO)
		float N221C9C45; //0x055C (TODO)
		float N21A5C6CD; //0x0560 (TODO)
		float N221CCDB8; //0x0564 (TODO)
		DWORD N221CD3F4; //0x0568 (TODO)
		float N2130C586; //0x056C (TODO)
		__int32 iKnockdownCount; //0x0570 (GUESSING)
		float fKillshotImpulseScale; //0x0574
		DWORD dwNmShotTuningSetHash; //0x0578
		CWeaponAttachPoints dwAttachBoneHash[5]; //0x057C
		char _0x06A8[1648];
		char* pChrStatName; //0x0D18 
		char _0x0D20[576];

	};//Size=0x0F60  
};