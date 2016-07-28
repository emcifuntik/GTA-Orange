#include "stdafx.h"

std::vector<CNetworkVehicle *> CNetworkVehicle::VehiclePool;

CNetworkVehicle::CNetworkVehicle(Hash model, float x, float y, float z, float heading):CVehicle(model, x, y, z, heading)
{
	VehiclePool.push_back(this);
}

CNetworkVehicle::~CNetworkVehicle()
{
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

void CNetworkVehicle::SetVehicleData(VehicleData data)
{
	SetPosition(data.vecPos);
	SetRotation(data.vecRot);
	SetHealth(data.usHealth);
}
