#include "stdafx.h"


std::vector<CNetworkPlayer *> CNetworkPlayer::PlayersPool;
Hash CNetworkPlayer::hFutureModel = 0;
int CNetworkPlayer::ignoreTasks = 0;


CNetworkPlayer::CNetworkPlayer() :CPedestrian(0)
{
	PlayersPool.push_back(this);
	m_Model = hFutureModel;
	Spawn({ 0.f, 0.f, 0.f });
}

CNetworkPlayer* CNetworkPlayer::GetByGUID(RakNet::RakNetGUID GUID)
{
	for each (CNetworkPlayer *_player in PlayersPool)
	{
		if (_player->m_GUID == GUID)
			return _player;
	}
	CNetworkPlayer *_newPlayer = new CNetworkPlayer();
	_newPlayer->m_GUID = GUID;
	return _newPlayer;
}

CNetworkPlayer* CNetworkPlayer::GetByHandler(Entity handler)
{
	for each (CNetworkPlayer *_player in PlayersPool)
	{
		if (_player->Handle == handler)
			return _player;
	}
	return nullptr;
}

void CNetworkPlayer::Tick()
{
	for each (CNetworkPlayer * player in PlayersPool)
	{
		if (player->IsSpawned())
		{
			player->Interpolate();
			player->DrawTag();
		}
	}
}

void CNetworkPlayer::UpdateLastTickTime()
{
	updateTick = (timeGetTime() - lastTick);
	lastTick = timeGetTime();
}

int CNetworkPlayer::GetTickTime()
{
	return updateTick;
}

CNetworkPlayer::~CNetworkPlayer()
{
	
}

std::vector<CNetworkPlayer*> CNetworkPlayer::All()
{
	return PlayersPool;
}

void CNetworkPlayer::DeleteNotExists(const std::vector<RakNet::RakNetGUID>& GUIDs)
{
	for (int i = 0; i < PlayersPool.size(); ++i)
	{
		if (std::find(GUIDs.begin(), GUIDs.end(), PlayersPool[i]->m_GUID) == GUIDs.end())
		{
			delete[] PlayersPool[i];
			PlayersPool.erase(PlayersPool.begin() + i);
			--i;
		}
	}
}

void CNetworkPlayer::Spawn(const CVector3& vecPosition)
{
	m_Spawned = true;
	if (STREAMING::IS_MODEL_IN_CDIMAGE(m_Model) && STREAMING::IS_MODEL_VALID(m_Model))
		STREAMING::REQUEST_MODEL(m_Model);
	while (!STREAMING::HAS_MODEL_LOADED(m_Model))
		WAIT(0);
	Handle = PED::CREATE_PED(1, m_Model, vecPosition.fX, vecPosition.fY, vecPosition.fZ, .0f, true, false);
	STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(m_Model);
	AI::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Handle, true);
	PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(Handle, false);
	PED::SET_PED_FLEE_ATTRIBUTES(Handle, 0, 0);
	PED::SET_PED_COMBAT_ATTRIBUTES(Handle, 17, 1);
	PED::SET_PED_CAN_RAGDOLL(Handle, false);
	PED::_SET_PED_RAGDOLL_FLAG(Handle, 1 | 2 | 4);
	ENTITY::SET_ENTITY_PROOFS(Handle, true, true, true, true, true, true, false, true);
}

void CNetworkPlayer::SetTargetPosition(const CVector3& vecPosition, unsigned long ulDelay)
{
	// Are we spawned?
	if (IsSpawned())
	{
		// Update our target position
		UpdateTargetPosition();

		// Get our position
		CVector3 vecCurrentPosition = GetPosition();

		// Set the target position
		m_interp.pos.vecTarget = vecPosition;

		// Calculate the relative error
		m_interp.pos.vecError = (vecPosition - vecCurrentPosition);

		// Get the interpolation interval
		unsigned long ulTime = timeGetTime();
		m_interp.pos.ulStartTime = ulTime;
		m_interp.pos.ulFinishTime = (ulTime + ulDelay);

		// Initialize the interpolation
		m_interp.pos.fLastAlpha = 0.0f;
	}
}

void CNetworkPlayer::SetTargetRotation(const CVector3& vecRotation, unsigned long ulDelay)
{
	// Are we spawned?
	if (IsSpawned())
	{
		// Update our target position
		UpdateTargetRotation();

		// Get our position
		CVector3 vecCurrentRotation = GetRotation();

		// Set the target position
		m_interp.rot.vecTarget = vecRotation;

		// Calculate the relative error
		m_interp.rot.vecError = (vecRotation - vecCurrentRotation);

		// Get the interpolation interval
		unsigned long ulTime = timeGetTime();
		m_interp.rot.ulStartTime = ulTime;
		m_interp.rot.ulFinishTime = (ulTime + ulDelay);

		// Initialize the interpolation
		m_interp.rot.fLastAlpha = 0.0f;
	}
}

void CNetworkPlayer::SetMoveToDirection(CVector3 vecPos, CVector3 vecMove, float iMoveSpeed)
{
	if (IsSpawned())
	{
		float tX = (vecPos.fX + (vecMove.fX * 10));
		float tY = (vecPos.fY + (vecMove.fY * 10));
		float tZ = (vecPos.fZ + (vecMove.fZ * 10));
		if (!is_active)
			TaskMove(CVector3(tX, tY, tZ), iMoveSpeed);
		else
		{
			//VEHICLE::SET_VEHICLE_FORWARD_SPEED(CNetworkVehicle::GetByGUID(vehGUID)->GetVehicle(), m_MoveSpeed);
			AI::TASK_VEHICLE_DRIVE_TO_COORD(Handle, CNetworkVehicle::GetByGUID(vehGUID)->GetVehicle(), tX, tY, tZ, 100, 0, CNetworkVehicle::GetByGUID(vehGUID)->GetModel(), 1074528293, 0.f, 0.f);
		}
	}
}

void CNetworkPlayer::SetMoveToDirectionAndAiming(CVector3 vecPos, CVector3 vecMove, CVector3 aimPos, float moveSpeed, bool shooting)
{
	if (IsSpawned())
	{
		float tX = (vecPos.fX + (vecMove.fX * 10));
		float tY = (vecPos.fY + (vecMove.fY * 10));
		float tZ = (vecPos.fZ + (vecMove.fZ * 10));
		AI::TASK_GO_TO_COORD_WHILE_AIMING_AT_COORD(Handle, tX, tY,
			tZ, aimPos.fX, aimPos.fY, aimPos.fZ, moveSpeed, (int)shooting, 0x3F000000, 0x40800000, 1, (shooting ?  0 : 512), 0, 3337513804U);
	}
}

void CNetworkPlayer::SetOnFootData(OnFootSyncData data, unsigned long ulDelay)
{
	SetHealth(data.usHealth);
	m_Health = data.usHealth;
	if (m_Health <= 100.f)
		return;
	else if(pedJustDead)
	{
		Spawn(data.vecPos);
		pedJustDead = false;
	}
	if (data.hModel != m_Model)
		SetModel(data.hModel);
	m_MoveSpeed = data.fMoveSpeed;
	m_vecMove = data.vecMoveSpeed;
	m_Jumping = data.bJumping;
	m_Aiming = data.bAiming;
	m_Shooting = data.bShooting;
	m_vecAim = data.vecAim;
	if (data.vehGuid > 0 && !isInVehicle)
	{
		isInVehicle = data.isInVehicle;
		seat = data.seat;
		vehGUID = RakNet::RakNetGUID(data.vehGuid);
		std::ofstream stream;
		stream.open("examples.txt");
		for each (CNetworkPlayer *var in CNetworkPlayer::All())
		{
			stream << "===========" << std::endl << "isInVehicle[1]:" << isInVehicle << std::endl << "Seat[1]:" << seat << std::endl << "VehGUID[2]:" << data.vehGuid << std::endl << "VehID[2]:" << vehGUID.ToString() << std::endl << "Enter:" << PED::IS_PED_IN_ANY_VEHICLE(var->Handle, false) << std::endl;
		}

		stream.close();
		PutInVehicle(CNetworkVehicle::GetByGUID(vehGUID)->GetVehicle(), seat);
	}
	if (!isInVehicle)
	{
		SetTargetPosition(data.vecPos, ulDelay);
		if (!m_Aiming && !m_Shooting)
			SetTargetRotation(data.vecRot, ulDelay);
		SetArmour(data.usArmour);
		if (GetCurrentWeapon() != data.ulWeapon)
			SetCurrentWeapon(data.ulWeapon, true);
		//SetAmmo(data.ulWeapon, 9999);
		SetDucking(data.bDuckState);
		m_Ducking = data.bDuckState;
		SetMovementVelocity(data.vecMoveSpeed);
	}
	else
	{
		m_interp.pos.vecTarget = data.vecPos;
		//VEHICLE::SET_VEHICLE_ENGINE_ON()
		if (!CNetworkVehicle::GetByGUID(vehGUID)->GetStartEngine())
		{
			CNetworkVehicle::GetByGUID(vehGUID)->StartEngine();
		}
		//CNetworkVehicle::GetByGUID(vehGUID)->TaskMove(m_interp.pos.vecTarget.fX, m_interp.pos.vecTarget.fY, m_interp.pos.vecTarget.fZ, 10.f);
		if (is_active)
		{
			CNetworkVehicle *veh = CNetworkVehicle::GetByGUID(vehGUID);
			SetTargetPosition(data.vecPos, ulDelay);
			veh->SetMovementVelocity(data.vecMoveSpeed);
			SetTargetRotation(data.vecRot, ulDelay);
			SetMoveToDirection(m_interp.pos.vecTarget, m_vecMove, m_MoveSpeed);
			
		}
	}


	
}

void CNetworkPlayer::UpdateTargetPosition()
{
	if (HasTargetPosition())
	{
		unsigned long ulCurrentTime = timeGetTime();
		float fAlpha = Math::UnlerpClamped(m_interp.pos.ulStartTime, ulCurrentTime, m_interp.pos.ulFinishTime);

		// Get the current error portion to compensate
		float fCurrentAlpha = (fAlpha - m_interp.pos.fLastAlpha);
		m_interp.pos.fLastAlpha = fAlpha;

		// Apply the error compensation
		CVector3 vecCompensation = Math::Lerp(CVector3(), fCurrentAlpha, m_interp.pos.vecError);

		// If we finished compensating the error, finish it for the next pulse
		if (fAlpha == 1.0f)
			m_interp.pos.ulFinishTime = 0;

		// Get our position
		CVector3 vecCurrentPosition = GetPosition();

		// Calculate the new position
		CVector3 vecNewPosition = (vecCurrentPosition + vecCompensation);

		// Check if the distance to interpolate is too far
		if ((vecCurrentPosition - m_interp.pos.vecTarget).Length() > 10)
		{
			// Abort all interpolation
			m_interp.pos.ulFinishTime = 0;
			vecNewPosition = m_interp.pos.vecTarget;
		}

		// Set our new position
		if(!is_active)
		SetPosition(vecNewPosition, false);
		else CNetworkVehicle::GetByGUID(vehGUID)->SetPosition(vecNewPosition);
	}
}

void CNetworkPlayer::UpdateTargetRotation()
{
	if (HasTargetRotation())
	{
		unsigned long ulCurrentTime = timeGetTime();
		float fAlpha = Math::UnlerpClamped(m_interp.rot.ulStartTime, ulCurrentTime, m_interp.rot.ulFinishTime);

		// Get the current error portion to compensate
		float fCurrentAlpha = (fAlpha - m_interp.rot.fLastAlpha);
		m_interp.rot.fLastAlpha = fAlpha;

		// Apply the error compensation
		CVector3 vecCompensation = Math::Lerp(CVector3(), fCurrentAlpha, m_interp.rot.vecError);

		// If we finished compensating the error, finish it for the next pulse
		if (fAlpha == 1.0f)
			m_interp.rot.ulFinishTime = 0;

		// Get our position
		CVector3 vecCurrentRotation = GetPosition();

		// Calculate the new position
		CVector3 vecNewRotation = (vecCurrentRotation + vecCompensation);

		// Check if the distance to interpolate is too far
		if ((vecCurrentRotation - m_interp.rot.vecTarget).Length() > 5)
		{
			// Abort all interpolation
			m_interp.rot.ulFinishTime = 0;
			vecNewRotation = m_interp.rot.vecTarget;
		}

		// Set our new position
		if(!is_active)
		SetRotation(vecNewRotation, false);
		else CNetworkVehicle::GetByGUID(vehGUID)->SetRotation(vecNewRotation);
	}
}

bool CNetworkPlayer::IsSpawned()
{
	return m_Spawned;
}

void CNetworkPlayer::SetPosition(const CVector3& vecPosition, bool bResetInterpolation)
{
	// Are we spawned?
	if (IsSpawned())
	{
		// Are we not in a vehicle and not entering a vehicle?
		//if (!InternalIsInVehicle() && !HasVehicleEnterExit())
		{
			// Set the position in the matrix
			CEntity::SetPosition(vecPosition);

			//m_pPlayerPed->GetPed()->UpdatePhysicsMatrix(true);

			//if (GetHealth() > 0 && IsDying())
			//	m_pPlayerPed->GetPedTaskManager()->RemoveTask(TASK_PRIORITY_EVENT_RESPONSE_NONTEMP);
		}
	}

	// Reset interpolation if requested
	if (bResetInterpolation)
		ResetInterpolation();
}

void CNetworkPlayer::SetRotation(const CVector3& vecRotation, bool bResetInterpolation)
{
	// Are we spawned?
	if (IsSpawned())
	{
		// Are we not in a vehicle and not entering a vehicle?
		//if (!InternalIsInVehicle() && !HasVehicleEnterExit())
		{
			// Set the position in the matrix
			CEntity::SetRotation(vecRotation);

			//m_pPlayerPed->GetPed()->UpdatePhysicsMatrix(true);

			//if (GetHealth() > 0 && IsDying())
			//	m_pPlayerPed->GetPedTaskManager()->RemoveTask(TASK_PRIORITY_EVENT_RESPONSE_NONTEMP);
		}
	}

	// Reset interpolation if requested
	if (bResetInterpolation)
		ResetInterpolation();
}

void CNetworkPlayer::Interpolate()
{
	if (!isInVehicle)
	{
		if (GetHealth() <= 100.f && !pedJustDead)
		{
			pedJustDead = true;
			ENTITY::DELETE_ENTITY(&Handle);
			return;
		}

		SetMovementVelocity(m_vecMove);
		if (!m_Shooting && !m_Aiming)
			UpdateTargetRotation();
		UpdateTargetPosition();
		if (IsJumping())
			return;

		if (!tasksToIgnore)
		{
			if (m_Jumping)
				TaskJump();
			else if (m_Aiming && !m_Shooting && m_MoveSpeed != .0f)
				SetMoveToDirectionAndAiming(m_interp.pos.vecTarget, m_vecMove, m_vecAim, m_MoveSpeed);
			else if (m_Aiming && !m_Shooting && m_MoveSpeed == .0f)
				TaskAimAt(m_vecAim, -1);
			else if (m_Shooting && m_MoveSpeed != .0f)
			{
				SetMoveToDirectionAndAiming(m_interp.pos.vecTarget, m_vecMove, m_vecAim, m_MoveSpeed, true);
				m_Shooting = false;
			}
			else if (m_Shooting && !m_Aiming)
			{
				TaskAimAt(m_vecAim, -1);
				TaskShootAt(m_vecAim, -1);
				m_Shooting = false;
			}
			else if (m_Shooting && m_MoveSpeed == .0f)
			{
				TaskShootAt(m_vecAim, 1);
				m_Shooting = false;
			}
			else if (m_MoveSpeed != .0f)
			{
				if (m_MoveSpeed != lastMoveSpeed)
					ClearTasks();
				else
					SetMoveToDirection(m_interp.pos.vecTarget, m_vecMove, m_MoveSpeed);
			}
			else
				ClearTasks();
		}
	}
	else
	{
		if (!CNetworkVehicle::GetByGUID(vehGUID)->GetStartEngine())
		{
			CNetworkVehicle::GetByGUID(vehGUID)->StartEngine();
		}
		if(is_active)
		AI::TASK_VEHICLE_DRIVE_TO_COORD(Handle, CNetworkVehicle::GetByGUID(vehGUID)->GetVehicle(), m_interp.pos.vecTarget.fX, m_interp.pos.vecTarget.fY, m_interp.pos.vecTarget.fZ, 100, 0, CNetworkVehicle::GetByGUID(vehGUID)->GetModel(), 16, 0.f, 0.f);
			//AI::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(Handle,)
	}
	lastMoveSpeed = m_MoveSpeed;
}

void CNetworkPlayer::DrawTag()
{
	if (ENTITY::IS_ENTITY_ON_SCREEN(Handle))
	{
		CVector3 vecCurPos = GetPosition();
		float health = (((m_Health < 100.f ? 100.f : m_Health) - 100.f) / 100.f);
		float distance = (vecCurPos - CLocalPlayer::Get()->GetPosition()).Length();
		if (distance < 100.f)
		{
			CGraphics::Get()->Draw3DText(m_Name, .5f, vecCurPos.fX, vecCurPos.fY, vecCurPos.fZ + 1.1f + (distance * 0.03f), { 0xFF, 0xFF, 0xFF, 0xFF });
			CGraphics::Get()->Draw3DProgressBar({ 0, 0, 0, 100 }, { 200, 50, 50, 200 }, 0.08f, 0.018f, vecCurPos.fX, vecCurPos.fY, vecCurPos.fZ + 1.1f + (distance * 0.03f), health);
		}
	}
}


void CNetworkPlayer::SetModel(Hash model)
{
	m_Model = model;
	CVector3 pos = GetPosition();
	float heading = GetHeading();
	ENTITY::DELETE_ENTITY(&Handle);
	if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_VALID(model))
		STREAMING::REQUEST_MODEL(model);
	while (!STREAMING::HAS_MODEL_LOADED(model))
		WAIT(0);
	Handle = PED::CREATE_PED(1, model, pos.fX, pos.fY, pos.fZ, heading, true, false);
	STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
	AI::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Handle, true);
	PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(Handle, false);
	PED::SET_PED_FLEE_ATTRIBUTES(Handle, 0, 0);
	PED::SET_PED_COMBAT_ATTRIBUTES(Handle, 17, 1);
	PED::SET_PED_CAN_RAGDOLL(Handle, false);
	PED::_SET_PED_RAGDOLL_FLAG(Handle, 1 | 2 | 4);
	ENTITY::SET_ENTITY_PROOFS(Handle, true, true, true, true, true, true, false, true);
}

void CNetworkPlayer::RemoveTargetPosition()
{
	m_interp.pos.ulFinishTime = 0;
}

void CNetworkPlayer::RemoveTargetRotation()
{
	m_interp.rot.ulFinishTime = 0;
}

void CNetworkPlayer::ResetInterpolation()
{
	RemoveTargetPosition();
	RemoveTargetRotation();
}