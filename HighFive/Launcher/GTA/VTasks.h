#pragma once

#define HOOK_CTOR(x, y) (x *(*)(x*))((intptr_t)GetModuleHandle(NULL) + y);

namespace GTA
{
	enum
	{
		CTaskNMSit = 414,
		CTaskMotionInAutomobile = 170,
		CTaskMotionInVehicle = 173,
		CTaskInVehicleSeatShuffle = 165,
		CTaskQuadLocomotion = 279,
		CTaskMotionStrafing = 270,
		CTaskMotionAimingTransition = 285,
		CTaskNMShot = 394,
		CTaskMotionInCover = 288,
		CTaskThreatResponse = 351,
		CTaskMoveFollowNavMesh = 238,
		CTaskNMExplosion = 399,
		CTaskNMHighFall = 395,
		CTaskRageRagdoll = 417,
		CTaskNMControl = 407,
		CTaskMotionAiming = 272,
		CTaskPlayerWeapon = 9,
		CTaskSwapWeapon = 56,
		CTaskMeleeActionResult = 130,
		CTaskVehicleGun = 200,
		CTaskInVehicleBasic = 150,
		CTaskPlayerIdles = 10,
		CTaskJump = 421,
		CTaskJumpVault = 420,
		CTaskMotionSwimming = 281,
		CTaskWitness = 76,
		CTaskVehicleTransformToSubmarine = 527,
		CTaskVault = 50,
		CTaskWeapon = 8,
		CTasksArraymartFlee = 218,
		CTasksArrayetPedOutOfVehicle = 198,
		CTasksArrayetPedInVehicle = 197,
		CTaskReloadGun = 298,
		CTaskPlayerOnFoot = 6,
		CTaskPlayerDrive = 159,
		CTaskParachute = 334,
		CTaskOpenVehicleDoorFromOutside = 162,
		CTaskOpenDoor = 54,
		CTaskMoveWithinDefensiveArea = 367,
		CTaskMoveWithinAttackWindow = 366,
		CTaskMoveStandStill = 34,
		CTaskMoveSlideToCoord = 252,
		CTaskMovePlayer = 5,
		CTaskMoveMeleeMovement = 129,
		CTaskMoveInAir = 39,
		CTaskMoveGoToVehicleDoor = 196,
		CTaskMoveGoToPoint = 205,
		CTaskMoveAchieveHeading = 206,
		CTaskMelee = 128,
		CTaskLeaveAnyCar = 152,
		CTaskInCover = 309,
		CTaskHumanLocomotion = 268,
		CTaskHandsUp = 0,
		CTaskGun = 290,
		CTaskGoToPointAnyMeans = 224,
		CTaskGoToPointAiming = 230,
		CTaskGoToCarDoorAndStandStill = 195,
		CTaskGoToAndClimbLadder = 47,
		CTaskGetUpAndStandStill = 17,
		CTaskGetUp = 16,
		CTaskGetOutOfWater = 256,
		CTaskGetOnTrain = 178,
		CTaskGetOffTrain = 179,
		CTaskGeneralSweep = 57,
		CTaskForceMotionState = 45,
		CTaskFollowWaypointRecording = 261,
		CTaskFollowLeaderInFormation = 223,
		CTaskFollowLeaderAnyMeans = 226,
		CTaskFlyingWander = 229,
		CTaskFlyToPoint = 228,
		CTaskFlyAway = 219,
		CTaskFlightlessBirdLocomotion = 274,
		CTaskFishLocomotion = 278,
		CTaskFirePatrol = 65,
		CTaskFallOver = 18,
		CTaskFallAndGetUp = 19,
		CTaskFall = 422,
		CTaskFSMClone = 12,
		CTaskExitVehicleSeat = 167,
		CTaskExitVehicle = 44,
		CTaskExitCover = 301,
		CTaskExhaustedFlee = 215,
		CTaskEscapeBlast = 240,
		CTaskEnterVehicleSeat = 163,
		CTaskEnterVehicleAlign = 161,
		CTaskEnterVehicle = 160,
		CTaskEnterCover = 300,
		CTaskDyingDead = 97,
		CTaskDuckAndCover = 146,
		CTaskDropDown = 51,
		CTaskDraggingToSafety = 363,
		CTaskDraggedToSafety = 364,
		CTaskDoNothing = 15,
		CTaskDiveToGround = 443,
		CTaskDetonator = 432,
		CTaskDeadBodyScenario = 107,
		CTaskDamageElectric = 26,
		CTaskCutScene = 440,
		CTaskCrouchToggle = 327,
		CTaskCrouch = 127,
		CTaskCrawl = 20,
		CTaskCowerScenario = 106,
		CTaskCower = 126,
		CTaskCover = 287,
		CTaskCoupleScenario = 117,
		CTaskControlVehicle = 169,
		CTaskConfront = 322,
		CTaskComplexStuckInAir = 140,
		CTaskComplexOnFire = 25,
		CTaskComplexGoToPointAndStandStillTimed = 208,
		CTaskComplexGetOffBoat = 153,
		CTaskComplexEvasiveStep = 137,
		CTaskComplexControlMovement = 35,
		CTaskComplex = 12,
		CTaskCombatSeekCover = 339,
		CTaskCombatRoll = 3,
		CTaskCombatMounted = 343,
		CTaskCombatFlank = 341,
		CTaskCombatClosestTargetInArea = 307,
		CTaskCombatAdditionalTask = 308,
		CTaskCombat = 342,
		CTaskCloseVehicleDoorFromOutside = 168,
		CTaskCloseVehicleDoorFromInside = 164,
		CTaskClimbLadderFully = 48,
		CTaskClimbLadder = 1,
		CTaskClearLookAt = 29,
		CTaskChatScenario = 104,
		CTaskChat = 425,
		CTaskCharge = 384,
		CTaskCarSetTempAction = 155,
		CTaskCarReactToVehicleCollisionGetOut = 95,
		CTaskCarReactToVehicleCollision = 93,
		CTaskCarDriveWander = 151,
		CTaskCarDrive = 157,
		CTaskCallPolice = 446,
		CTaskBusted = 64,
		CTaskBringVehicleToHalt = 156,
		CTaskBomb = 431,
		CTaskBoatStrafe = 372,
		CTaskBoatCombat = 371,
		CTaskBoatChase = 370,
		CTaskBlendFromNM = 406,
		CTaskBirdLocomotion = 273,
		CTaskArrestPed = 62,
		CTaskArrestPed2 = 63,
		CTaskArmy = 78,
		CTaskAnimatedHitByExplosion = 387,
		CTaskAnimatedFallback = 528,
		CTaskAnimatedAttach = 434,
		CTaskAmbulancePatrol = 68,
		CTaskAmbientLookAtEvent = 53,
		CTaskAmbientClips = 38,
		CTaskAimSweep = 313,
		CTaskAimGunVehicleDriveBy = 295,
		CTaskAimGunScripted = 296,
		CTaskAimGunOnFoot = 4,
		CTaskAimGunFromCoverOutro = 303,
		CTaskAimGunFromCoverIntro = 302,
		CTaskAimGunBlindFire = 304,
		CTaskAimGun = 12,
		CTaskAimFromGround = 291,
		CTaskAimAndThrowProjectile = 289,
		CTaskAgitatedAction = 321,
		CTaskAgitated = 320,
		CTaskAggressiveRubberneck = 147,
		CTaskAffectSecondaryBehaviour = 52,
		CTaskAdvance = 383,
		CTaskMotionPed = 264
	};
	enum
	{
		TASK_PRIORITY_LOWEST = 0,
		TASK_PRIORITY_LOW,
		TASK_PRIORITY_NORMAL,
		TASK_PRIORITY_HIGH,
		TASK_PRIORITY_HIGHEST,
		TASK_PRIORITY_REAL_TIME
	};
};

typedef void CTaskJumpVault;
typedef void CTaskPlayerOnFoot;
typedef void CTaskPlayerDrive;

class VTasks
{
	std::string* TasksArray[500] = { nullptr };
	VTasks();
	static VTasks *singleInstance;
public:
	static VTasks* Get()
	{
		if (!singleInstance)
			singleInstance = new VTasks();
		return singleInstance;
	}

	std::string GetTaskName(int64_t id);
	~VTasks();
	void *GetTaskFromID(unsigned int taskID) { 
		typedef void*(*__func)(unsigned int);
		((__func)(CMemory::Find("48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 41 54 41 55 41 56 41 57 48 83 EC 20 33 F6 B8 DB 00 00 00")()))(taskID);
	}
};



