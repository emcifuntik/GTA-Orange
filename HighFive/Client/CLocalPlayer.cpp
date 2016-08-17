#include "stdafx.h"

CLocalPlayer* CLocalPlayer::Instance = nullptr;

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

	aimPosition = &CWorld::Get()->CPedPtr->CPlayerInfoPtr->AimPosition;

	// Disabling weapon wheel slow motion
	auto addr = CMemory::Find("32 C0 F3 0F 11 09");
	addr->nop(6);

	//auto addr = Memory::Find("74 25 B9 40 ? ? ? E8 ? ? C4 FF");
	//addr->nop(20);
	//GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST("XMAS");
	//GRAPHICS::_SET_FORCE_PED_FOOTSTEPS_TRACKS(true);
	//GRAPHICS::_SET_FORCE_VEHICLE_TRAILS(true);

	std::stringstream ss;
	ss << "Connecting to ~b~" << CConfig::Get()->sIP.c_str() << ":" << CConfig::Get()->uiPort;
	CChat::Get()->AddChatMessage(ss.str());
	if (!CNetworkConnection::Get()->Connect(CConfig::Get()->sIP.c_str(), CConfig::Get()->uiPort))
		CChat::Get()->AddChatMessage("Can't connect to the server", { 255, 0, 0, 255 });
	else
		CChat::Get()->AddChatMessage("Connection successfull");
}


CLocalPlayer::~CLocalPlayer()
{
}

void CLocalPlayer::GetOnFootSync(OnFootSyncData& onfoot)
{
	onfoot.hModel = GetModel();
	onfoot.bJumping = IsJumping();
	onfoot.fMoveSpeed = CWorld::Get()->CPedPtr->MoveSpeed;
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
	onfoot.vecAim = *aimPosition;
	onfoot.bAiming = (CWorld::Get()->CPedPtr->CPlayerInfoPtr->AimState == 2);
	onfoot.bShooting = PED::IS_PED_SHOOTING(Handle) ? true : false;
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

void CLocalPlayer::SendTasks()
{
	
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
