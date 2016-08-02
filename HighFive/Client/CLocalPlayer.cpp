#include "stdafx.h"

CLocalPlayer* CLocalPlayer::Instance = nullptr;
float CLocalPlayer::offsetX = 0.f;
float CLocalPlayer::offsetY = 0.f;
float CLocalPlayer::alpha = 0.001f;

CLocalPlayer::CLocalPlayer():CPedestrian(PLAYER::PLAYER_PED_ID())
{
	DisableScripts();
	SCRIPT::SHUTDOWN_LOADING_SCREEN();
	CAM::DO_SCREEN_FADE_IN(500);
	UI::DISPLAY_RADAR(true);
	UI::DISPLAY_HUD(true);

	for (int i = 0; i < 5; i++) {
		GAMEPLAY::DISABLE_HOSPITAL_RESTART(i, true);
	}

	for (int i = 0; i < 50; i++) {
		GAMEPLAY::DISABLE_STUNT_JUMP_SET(i);
		GAMEPLAY::DELETE_STUNT_JUMP(i);
	}
	GAMEPLAY::SET_MISSION_FLAG(true);
	auto addr = Memory::Find("74 25 B9 40 ? ? ? E8 ? ? C4 FF");
	addr->nop(20);
	//AUDIO::REQUEST_SCRIPT_AUDIO_BANK("SNOW_FOOTSTEPS", true);
	GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("XMAS");
	GRAPHICS::_SET_FORCE_PED_FOOTSTEPS_TRACKS(true);
	GRAPHICS::_SET_FORCE_VEHICLE_TRAILS(true);
}


CLocalPlayer::~CLocalPlayer()
{
}

void CLocalPlayer::GetOnFootSync(OnFootSyncData& onfoot)
{
	onfoot.hModel = GetModel();
	onfoot.bJumping = IsJumping();
	onfoot.fMoveSpeed = GetBlendRation();
	onfoot.vecPos = GetPosition();
	onfoot.vecRot = GetRotation();
	onfoot.fHeading = GetHeading();
	GetMoveSpeed(onfoot.vecMoveSpeed);
	onfoot.vecTurnSpeed = GetRotationVelocity();
	onfoot.bDuckState = IsDucking();
	onfoot.usHealth = GetHealth();
	onfoot.usArmour = GetArmour();
	onfoot.ulWeapon = GetCurrentWeapon();
	onfoot.uAmmo = GetCurrentWeaponAmmo();
	GetAimPosition(onfoot.vecAim);
	onfoot.bAiming = CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, 25);
	onfoot.bShooting = PED::IS_PED_SHOOTING(Handle);
	bool inveh = false;
	if (PED::IS_PED_IN_ANY_VEHICLE(Handle, false)) inveh = true;
	if (PED::IS_PED_IN_ANY_VEHICLE(Handle, true)) inveh = true;
	onfoot.isInVehicle = inveh;
	onfoot.seat = 1;
	for each(CNetworkVehicle *temp in CNetworkVehicle::All())
	{
		if (GetPlayerVehicle() == temp->GetVehicle())
		{
			onfoot.vehGuid = temp->m_GUID.ToUint32(temp->m_GUID);
			std::ofstream stream;
			stream.open("example.txt");
			stream << "isInVehicle[1]:" << onfoot.isInVehicle << std::endl << "Seat[1]:" << onfoot.seat << std::endl << "VehGUID[2]:" << onfoot.vehGuid << std::endl;
			stream.close();
			break;
		}
	}
}

CLocalPlayer * CLocalPlayer::Get()
{
	if (!Instance)
		Instance = new CLocalPlayer();
	return Instance;
}

void CLocalPlayer::Tick()
{
	if (newModel != 0)
	{
		ChangeModel(newModel);
		newModel = 0;
	}
	VEHICLE::SET_GARBAGE_TRUCKS(false);
	VEHICLE::SET_RANDOM_BOATS(false);
	VEHICLE::SET_RANDOM_TRAINS(false);
	VEHICLE::SET_FAR_DRAW_VEHICLES(false);
	VEHICLE::DELETE_ALL_TRAINS();
	VEHICLE::SET_NUMBER_OF_PARKED_VEHICLES(-1);
	VEHICLE::SET_ALL_LOW_PRIORITY_VEHICLE_GENERATORS_ACTIVE(false);
	VEHICLE::SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(.0f);
	VEHICLE::SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(.0f);
	VEHICLE::SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(.0f);
	VEHICLE::REMOVE_VEHICLES_FROM_GENERATORS_IN_AREA(-9999.f, -9999.f, -9999.f, 9999.f, 9999.f, 9999.f, false);

	PED::SET_CREATE_RANDOM_COPS_NOT_ON_SCENARIOS(false);
	PED::SET_CREATE_RANDOM_COPS(false);
	PED::SET_CREATE_RANDOM_COPS_ON_SCENARIOS(false);
	PED::SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(.0f);
	PED::SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME(.0f, .0f);

	PLAYER::SET_MAX_WANTED_LEVEL(0);

	MOBILE::DESTROY_MOBILE_PHONE();

	STREAMING::SET_VEHICLE_POPULATION_BUDGET(0);
	STREAMING::SET_PED_POPULATION_BUDGET(0);

	CONTROLS::DISABLE_CONTROL_ACTION(2, 19, true);

	UI::_0x170F541E1CADD1DE(true);
	UI::SHOW_HUD_COMPONENT_THIS_FRAME(3);
	UI::DISPLAY_CASH(true);
	PLAYER::SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER(PLAYER::PLAYER_ID(), 0.f);
	PLAYER::SET_AUTO_GIVE_PARACHUTE_WHEN_ENTER_PLANE(PLAYER::PLAYER_ID(), false);
	PLAYER::ENABLE_SPECIAL_ABILITY(PLAYER::PLAYER_ID(), false);
}

void CLocalPlayer::ChangeModel(Hash model)
{
	if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_VALID(model))
		STREAMING::REQUEST_MODEL(model);
	while (!STREAMING::HAS_MODEL_LOADED(model))
		WAIT(0);
	PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), model);
	STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
	Handle = PLAYER::PLAYER_PED_ID();
}

void CLocalPlayer::Connect()
{
	RakNet::BitStream requestid;
	RakString playerName(CConfig::Get()->sNickName.c_str());
	requestid.Write((MessageID)ID_CONNECT_TO_SERVER);
	requestid.Write(playerName);
	CNetworkConnection::Get()->client->Send(&requestid, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);

	CChat::Get()->AddChatMessage("Connected to server", { 100, 255, 100, 200 });
}

void CLocalPlayer::SendOnFootData()
{
	RakNet::BitStream bsOut;
	bsOut.Write((MessageID)ID_SEND_PLAYER_DATA);
	OnFootSyncData data;
	GetOnFootSync(data);
	bsOut.Write(data);

	CNetworkConnection::Get()->client->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

void CLocalPlayer::SetMoney(int money)
{
	for (int i = 0; i < 3; i++)
	{
		char statNameFull[32];
		sprintf_s(statNameFull, "SP%d_TOTAL_CASH", i);
		Hash hash = GAMEPLAY::GET_HASH_KEY(statNameFull);
		STATS::STAT_SET_INT(hash, money, 1);
	}
}

bool CLocalPlayer::GetAimPosition(CVector3& aimPos)
{
	bool aiming = CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, 25);
	bool shooting = PED::IS_PED_SHOOTING(Handle);
	if (!aiming && !shooting)
		return false;

	Vector3 _camPos = CAM::GET_GAMEPLAY_CAM_COORD();
	CVector3 camPos = CVector3(_camPos.x, _camPos.y, _camPos.z);
	Vector3 _camRot = CAM::GET_GAMEPLAY_CAM_ROT(2);
	CVector3 camRot = CVector3(_camRot.x, _camRot.y, _camRot.z);
	CVector3 camDirection = Utils::RotationToDirection(camRot);

	CVector3 target = camPos + camDirection * 1000.f;
	int iRayCast = WORLDPROBE::_CAST_RAY_POINT_TO_POINT(camPos.fX, camPos.fY, camPos.fZ, target.fX, target.fY, target.fZ, 1 | 4 | 10, 0, 7);
	BOOL hit;
	Vector3 hitCoords, surfaceCoords;
	Entity hitEntity;
	WORLDPROBE::_GET_RAYCAST_RESULT(iRayCast, &hit, &hitCoords, &surfaceCoords, &hitEntity);
	
	aimPos = CVector3(hitCoords.x, hitCoords.y, hitCoords.z);
	return true;
}
