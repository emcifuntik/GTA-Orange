#include "stdafx.h"

std::vector<CNetworkVehicle *> CNetworkVehicle::VehiclePool;

CNetworkVehicle::CNetworkVehicle(Hash model, float x, float y, float z, float heading):CVehicle(model, x, y, z, heading)
{
	VehiclePool.push_back(this);
}

CNetworkVehicle::~CNetworkVehicle()
{
}

void CNetworkVehicle::Tick()
{
	for each (CNetworkVehicle * vehicle in VehiclePool)
	{
		if (vehicle)
			vehicle->Interpolate();
	}
}

std::vector<CNetworkVehicle*> CNetworkVehicle::All()
{
	return VehiclePool;
}

CNetworkVehicle * CNetworkVehicle::GetByGUID(RakNet::RakNetGUID GUID)
{
	for each (CNetworkVehicle *_vehicle in VehiclePool)
	{
		if (_vehicle->m_GUID == GUID)
			return _vehicle;
	}
	return nullptr;
}

void CNetworkVehicle::SetTargetPosition(const CVector3& vecPosition, unsigned long ulDelay)
{
	// Are we spawned?
	if (this)
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

void CNetworkVehicle::SetTargetRotation(const CVector3& vecRotation, unsigned long ulDelay)
{
	// Are we spawned?
	if (this)
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

void CNetworkVehicle::SetMoveToDirection(CVector3 vecPos, CVector3 vecMove, float iMoveSpeed)
{
	if (this)
	{
		float tX = (vecPos.fX + (vecMove.fX * 10));
		float tY = (vecPos.fY + (vecMove.fY * 10));
		float tZ = (vecPos.fZ + (vecMove.fZ * 10));
		TaskMove(tX, tY, tZ, iMoveSpeed);
	}
}

void CNetworkVehicle::SetVehicleData(VehicleData data, unsigned long ulDelay)
{
	m_vecMove = data.vecMoveSpeed;
	SetTargetPosition(data.vecPos, ulDelay);
	SetTargetRotation(data.vecRot, ulDelay);
	SetHealth(data.usHealth);
	SetMovementVelocity(data.vecMoveSpeed);
}

void CNetworkVehicle::UpdateTargetPosition()
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

void CNetworkVehicle::UpdateTargetRotation()
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

void CNetworkVehicle::SetPosition(const CVector3& vecPosition, bool bResetInterpolation)
{
	// Are we spawned?
	if (this)
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

void CNetworkVehicle::SetRotation(const CVector3& vecRotation, bool bResetInterpolation)
{
	// Are we spawned?
	if (this)
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

void CNetworkVehicle::Interpolate()
{
	// Are we not getting in/out of a vehicle?
	if (this)
	{
		UpdateTargetPosition();
		UpdateTargetRotation();
		//driver->ClearTasks();
		SetMoveToDirection(m_interp.pos.vecTarget, m_vecMove, 3.f);
		SetMovementVelocity(m_vecMove);
		//UpdateTargetHeading();
	}
}


void CNetworkVehicle::RemoveTargetPosition()
{
	m_interp.pos.ulFinishTime = 0;
}

void CNetworkVehicle::RemoveTargetRotation()
{
	m_interp.rot.ulFinishTime = 0;
}

void CNetworkVehicle::ResetInterpolation()
{
	RemoveTargetPosition();
	RemoveTargetRotation();
}

