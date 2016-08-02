#include "stdafx.h"

std::vector<CNetworkVehicle *> CNetworkVehicle::Vehicles;

int CNetworkVehicle::Count()
{
	int _count = 0;
	for each (CNetworkVehicle *vehicle in Vehicles)
	{
		if (vehicle)
			_count++;
	}
	return _count;
}

CNetworkVehicle::CNetworkVehicle(Hash model, float x, float y, float z, float heading):hashModel(model),vecPos(x,y,z)
{
	rnGUID = RakNetGUID::RakNetGUID(rand());
	log << rnGUID.ToString();
	for each (CNetworkVehicle *vehicle in Vehicles)
	{
		if (vehicle == this) return;
	}
	Vehicles.push_back(this);
}

void CNetworkVehicle::SetPosition(CVector3 position)
{
	vecPos = position;
}

void CNetworkVehicle::SetDriver(CNetworkPlayer* driver)
{
	this->driver = driver;
}

void CNetworkVehicle::SetRotation(CVector3 rotation)
{
	vecRot = rotation;
}

void CNetworkVehicle::SetHealth(unsigned short health)
{
	usHealth = health;
}

void CNetworkVehicle::SetVehicleData(const VehicleData & data)
{
	//rnGUID = data.GUID;
	vecPos = data.vecPos;
	vecRot = data.vecRot;
	usHealth = data.usHealth;
	hashModel = data.hashModel;
	vecMoveSpeed = data.vecMoveSpeed;
}
void CNetworkVehicle::Tick()
{

}
void CNetworkVehicle::GetVehicleData(VehicleData & data)
{
	data.GUID = rnGUID;
	data.vecPos = vecPos;
	data.vecRot = vecRot;
	data.usHealth = usHealth;
	data.hashModel = hashModel;
	data.vecMoveSpeed = vecMoveSpeed;
}


CNetworkVehicle::~CNetworkVehicle()
{
	
}

std::vector<CNetworkVehicle *> CNetworkVehicle::All()
{
	return Vehicles;
}
