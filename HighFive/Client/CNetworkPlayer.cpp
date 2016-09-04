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

void CNetworkPlayer::Clear()
{
	for each(CNetworkPlayer* player in PlayersPool)
	{
		PED::DELETE_PED(&(player->Handle));
		delete player;
	}
	PlayersPool.erase(PlayersPool.begin(), PlayersPool.end());
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

std::vector<CNetworkPlayer*> CNetworkPlayer::All()
{
	return PlayersPool;
}

void CNetworkPlayer::DeleteByGUID(RakNet::RakNetGUID guid)
{
	for (int i = 0; i < PlayersPool.size(); ++i)
	{
		if (PlayersPool[i]->m_GUID == guid)
		{
			PED::DELETE_PED(&PlayersPool[i]->Handle);
			delete PlayersPool[i];
			PlayersPool.erase(PlayersPool.begin() + i, PlayersPool.begin() + i + 1);
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
	pedHandler = (CPed*)getScriptHandleBaseAddress(Handle);
	STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(m_Model);
	AI::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Handle, true);
	/*PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(Handle, false);
	PED::SET_PED_FLEE_ATTRIBUTES(Handle, 0, 0);
	PED::SET_PED_COMBAT_ATTRIBUTES(Handle, 17, 1);
	PED::SET_PED_CAN_RAGDOLL(Handle, false);
	PED::_SET_PED_RAGDOLL_FLAG(Handle, 1 | 2 | 4);*/
	//pedHandler->Flags |= 1 << 30;
	pedHandler->Flags |= 1 << 6;
	ENTITY::SET_ENTITY_PROOFS(Handle, true, true, true, true, true, true, true, true);
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

void CNetworkPlayer::SetOnFootData(OnFootSyncData data, unsigned long ulDelay)
{
	SetHealth(data.usHealth);
	m_Health = data.usHealth;
	if (m_Health <= 100.f)
		return;
	else if(pedJustDead)
	{
		if (ENTITY::IS_ENTITY_A_PED(Handle))
			PED::DELETE_PED(&Handle);
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
	SetTargetPosition(data.vecPos, ulDelay);
	if(!m_Aiming && !m_Shooting)
		SetTargetRotation(data.vecRot, ulDelay);
	SetArmour(data.usArmour);
	if(GetCurrentWeapon() != data.ulWeapon)
		SetCurrentWeapon(data.ulWeapon, true);
	//SetAmmo(data.ulWeapon, 9999);
	SetDucking(data.bDuckState);
	m_Ducking = data.bDuckState;
	SetMovementVelocity(data.vecMoveSpeed);
	pedHandler->MoveSpeed = data.fMoveSpeed;
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
		SetPosition(vecNewPosition, false);
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
		SetRotation(vecNewRotation, false);
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
	if (PED::IS_PED_DEAD_OR_DYING(Handle, true) && !pedJustDead)
	{
		pedJustDead = true;
		ENTITY::DELETE_ENTITY(&Handle);
		return;
	}
		
	if(!m_Shooting && !m_Aiming)
		UpdateTargetRotation();
	UpdateTargetPosition();
	SetMovementVelocity(m_vecMove);
	PED::SET_PED_ACCURACY(Handle, 100);
	BuildTasksQueue();
}

void CNetworkPlayer::SetMoveToDirection(CVector3 vecPos, CVector3 vecMove, float iMoveSpeed)
{
	if (IsSpawned())
	{
		float tX = (vecPos.fX + (vecMove.fX * 10));
		float tY = (vecPos.fY + (vecMove.fY * 10));
		float tZ = (vecPos.fZ + (vecMove.fZ * 10));
		TaskMove(CVector3(tX, tY, tZ), iMoveSpeed);
	}
}

void CNetworkPlayer::SetMoveToDirectionAndAiming(CVector3 vecPos, CVector3 vecMove, CVector3 aimPos, float moveSpeed, bool shooting)
{
	if (IsSpawned())
	{
		float tX = (vecPos.fX + (vecMove.fX * 10));
		float tY = (vecPos.fY + (vecMove.fY * 10));
		float tZ = (vecPos.fZ + (vecMove.fZ * 10));
		//MemoryHook::call<void, Ped, float, float, float, float, float, float, float, BOOL, float, float, BOOL, Any, BOOL, Hash>((*GTA::CAddress::Get())[PED_TASK_AIM_AT_COORD_AND_STAND_STILL], Handle, tX, tY,
		//	tZ, aimPos.fX, aimPos.fY, aimPos.fZ, 1.f, 0, 0x3F000000, 0x40800000, 1, (shooting ? 0 : 1024), 1, 3337513804U);
		AI::TASK_GO_TO_COORD_WHILE_AIMING_AT_COORD(Handle, tX, tY,
			tZ, aimPos.fX, aimPos.fY, aimPos.fZ, 1.f, 0, 0x3F000000, 0x40800000, 1, (shooting ? 0 : 1024), 1, 3337513804U);
	}
}

void CNetworkPlayer::BuildTasksQueue()
{
	if (tasksToIgnore > 0)
	{
		tasksToIgnore--;
		return;
	}
	if (m_Jumping)
	{
		TaskJump();
	}
	else if (m_Aiming && !m_Shooting)
	{
		if (m_MoveSpeed != .0f)
		{
			SetMoveToDirectionAndAiming(m_interp.pos.vecTarget, m_vecMove, m_vecAim, 3.0f, false);
		}
		else
		{
			TaskAimAt(m_vecAim, -1);
		}
	}
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
		SetMoveToDirection(m_interp.pos.vecTarget, m_vecMove, m_MoveSpeed);
	}
	else
	{
		AI::CLEAR_PED_TASKS(Handle);
	}
	/*RakNet::BitStream bsOut;
	bsOut.Write((unsigned char)ID_SEND_TASKS);
	bool foundPrimary = false;*/
	/*std::vector<CSerialisedFSMTaskInfo*> taskClones;
	pedHandler->WalkSpeed = CWorld::Get()->CPedPtr->WalkSpeed;
	pedHandler->MoveSpeed = CWorld::Get()->CPedPtr->MoveSpeed;
	pedHandler->MoveSpeed2 = CWorld::Get()->CPedPtr->MoveSpeed2;
	pedHandler->MoveSpeed3 = CWorld::Get()->CPedPtr->MoveSpeed3;
	pedHandler->MoveSpeed4 = CWorld::Get()->CPedPtr->MoveSpeed4;*/

	/*if (CWorld::Get()->CPedPtr->TasksPtr->PrimaryTasks->GetTask()->GetID() == GTA::CTaskPlayerOnFoot)
	{
		if (pedHandler->TasksPtr->PrimaryTasks->GetTask()->GetID() != GTA::CTaskPlayerOnFoot)
		{
			pedHandler->TasksPtr->PrimaryTasks->AssignTask(CWorld::Get()->CPedPtr->TasksPtr->PrimaryTasks->GetTask()->Clone(), GTA::TASK_PRIORITY_HIGH);
		}
	}*/
	

	/*if (taskClones.size())
	{
		GTA::CTask* parentTask = nullptr;
		GTA::CTask* cursorTask = nullptr;
		for each (auto serTask in taskClones)
		{
			if (!parentTask)
			{
				parentTask = (GTA::CTask*)serTask->GetTask();
				parentTask->Deserialize(serTask);
				cursorTask = parentTask;
			}
			else
			{
				GTA::CTask *tempTask = (GTA::CTask*)serTask->GetTask();
				tempTask->Deserialize(serTask);
				TRACEN();
				cursorTask->SetSubTask(0, tempTask);
				cursorTask = tempTask;
				TRACEN();
			}
		}
		pedHandler->TasksPtr->PrimaryTasks->AssignTask(parentTask, GTA::TASK_PRIORITY_HIGHEST);
	}
	*/
	/*auto curPedTask = pedHandler->TasksPtr->PrimaryTasks->GetTask();
	auto nextTask = (GTA::CTask*)((CSerialisedFSMTaskInfo*)ptr)->GetTask();
	if (nextTask->GetID() == curPedTask->GetID())
	{
		curPedTask->Deserialize(ptr);
		rage::sysMemAllocator::Get()->free(ptr, rage::HEAP_TASK_CLONE);
		rage::sysMemAllocator::Get()->free(nextTask, rage::HEAP_TASK);
	}
	else
		pedHandler->TasksPtr->PrimaryTasks->AssignTask(nextTask, GTA::TASK_PRIORITY_HIGHEST);*/
	/*if (foundPrimary)
	{
		CNetworkConnection::Get()->client->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
	}*/

	//for (GTA::CTask *task = CWorld::Get()->CPedPtr->TasksPtr->MovementTasks->GetTask(); task; task = task->Child)
	//{
	//	if (!task->IsSerializable())
	//		continue;
	//	void* ser = task->Serialize();
	//	if (ser)
	//	{
	//		GTA::CTask* tsk = (GTA::CTask*)((CSerialisedFSMTaskInfo*)ser)->GetTask();
	//		log_debug << "Task: 0x" << std::hex << tsk << std::endl;
	//		//if (pedHandler->TasksPtr->PrimaryTasks->GetTask() && pedHandler->TasksPtr->PrimaryTasks->GetTask()->GetID() != tsk->GetID())
	//		{
	//			pedHandler->TasksPtr->MovementTasks->AssignTask(tsk, GTA::TASK_PRIORITY_HIGHEST);
	//		}
	//		/*else
	//		{
	//		rage::sysMemAllocator::Get()->free(tsk);
	//		auto ret = ((CSerialisedFSMTaskInfo*)ser)->SetData(pedHandler->TasksPtr->PrimaryTasks->GetTask());
	//		}*/
	//		rage::sysMemAllocator::Get()->free(ser, rage::HEAP_TASK_CLONE);
	//		break;
	//	}
	//}
	//for (GTA::CTask *task = CWorld::Get()->CPedPtr->TasksPtr->MotionTasks->GetTask(); task; task = task->Child)
	//{
	//	if (!task->IsSerializable())
	//		continue;
	//	void* ser = task->Serialize();
	//	if (ser)
	//	{
	//		GTA::CTask* tsk = (GTA::CTask*)((CSerialisedFSMTaskInfo*)ser)->GetTask();
	//		log_debug << "Task: 0x" << std::hex << tsk << std::endl;
	//		//if (pedHandler->TasksPtr->PrimaryTasks->GetTask() && pedHandler->TasksPtr->PrimaryTasks->GetTask()->GetID() != tsk->GetID())
	//		{
	//			pedHandler->TasksPtr->MotionTasks->AssignTask(tsk, GTA::TASK_PRIORITY_HIGHEST);
	//		}
	//		/*else
	//		{
	//		rage::sysMemAllocator::Get()->free(tsk);
	//		auto ret = ((CSerialisedFSMTaskInfo*)ser)->SetData(pedHandler->TasksPtr->PrimaryTasks->GetTask());
	//		}*/
	//		rage::sysMemAllocator::Get()->free(ser, rage::HEAP_TASK_CLONE);
	//		break;
	//	}
	//}
	//if (CWorld::Get()->CPedPtr->TasksPtr->PrimaryTasks->GetTask())
	//{

	//	GTA::CTask *curTask = CWorld::Get()->CPedPtr->TasksPtr->PrimaryTasks->GetTask();
	//	if (curTask->GetID() == GTA::CTaskPlayerOnFoot)
	//	{
	//		curTask = curTask->Child;
	//		if (curTask && curTask->GetID() == GTA::CTaskPlayerWeapon)
	//		{
	//			curTask = curTask->Child;
	//			if (curTask && curTask->GetID() == GTA::CTaskWeapon)
	//			{
	//				curTask = curTask->Child;
	//				if (curTask && curTask->GetID() == GTA::CTaskGun)
	//				{
	//					void* ptr = curTask->Serialize();
	//					

	//					//curTask = curTask->Child;
	//					//if (curTask && curTask->GetID() == GTA::CTaskAimGunOnFoot)
	//					//{
	//					//	void* ptr2 = curTask->Serialize();
	//					//	GTA::CTask* tsk2 = (GTA::CTask*)((CSerialisedFSMTaskInfo*)ptr2)->GetTask();
	//					//	tsk->Child = tsk2;
	//					//	tsk2->Parent = tsk;
	//					//}
	//				}
	//			}
	//		}
	//	}
	//}
}

void CNetworkPlayer::DrawTag()
{
	if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(CLocalPlayer::Get()->GetHandle(), Handle, 17))
	{
		CVector3 *vecCurPos = &pedHandler->Position;
		float health = (((m_Health < 100.f ? 100.f : m_Health) - 100.f) / (pedHandler->MaxHealth-100.f));
		float distance = ((*vecCurPos) - CWorld::Get()->CPedPtr->Position).Length();
		if (distance < 100.f)
		{
			color_t bgColor, fgColor;
			if (health > 0.2f)
			{
				bgColor = { 50, 100, 50, 150 };
				fgColor = { 100, 200, 100, 150 };
			}
			else
			{
				bgColor = { 150, 30, 30, 150 };
				fgColor = { 230, 70, 70, 150 };
			}
			CGraphics::Get()->Draw3DText(m_Name, .5f, vecCurPos->fX, vecCurPos->fY, vecCurPos->fZ + 1.1f + (distance * 0.03f), { 0xFF, 0xFF, 0xFF, 0xFF });
			CGraphics::Get()->Draw3DProgressBar(bgColor, fgColor, 0.08f, 0.012f, vecCurPos->fX, vecCurPos->fY, vecCurPos->fZ + 1.1f + (distance * 0.03f), health);
		}
	}
}


void CNetworkPlayer::SetModel(Hash model)
{
	m_Model = model;
	//MemoryHook::call<int, int>((*GTA::CAddress::Get())[PED_CHANGE_MODEL], Handle, model);
	CVector3 pos = GetPosition();
	float heading = GetHeading();
	ENTITY::DELETE_ENTITY(&Handle);
	if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_VALID(model))
		STREAMING::REQUEST_MODEL(model);
	while (!STREAMING::HAS_MODEL_LOADED(model))
		WAIT(0);
	Handle = PED::CREATE_PED(1, model, pos.fX, pos.fY, pos.fZ, heading, true, false);
	pedHandler = (CPed*)getScriptHandleBaseAddress(Handle);
	STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
	AI::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Handle, true);
	/*PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(Handle, false);
	PED::SET_PED_FLEE_ATTRIBUTES(Handle, 0, 0);
	PED::SET_PED_COMBAT_ATTRIBUTES(Handle, 17, 1);
	PED::SET_PED_CAN_RAGDOLL(Handle, false);
	PED::_SET_PED_RAGDOLL_FLAG(Handle, 1 | 2 | 4);*/
	//pedHandler->Flags |= 1 << 30;
	pedHandler->Flags |= 1 << 6;
	ENTITY::SET_ENTITY_PROOFS(Handle, true, true, true, true, true, true, true, true);
	
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
