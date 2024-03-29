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
	Vehicles.push_back(this);
}

RakNetGUID CNetworkVehicle::GetGUID()
{
	return rnGUID;
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
	rnGUID = data.GUID;
	vecPos = data.vecPos;
	vecRot = data.vecRot;
	usHealth = data.usHealth;
	vecMoveSpeed = data.vecMoveSpeed;
	hasDriver = data.hasDriver;
	driverGUID = data.driver;
}

void CNetworkVehicle::GetVehicleData(VehicleData & data)
{
	data.GUID = rnGUID;
	data.vecPos = vecPos;
	data.vecRot = vecRot;
	data.usHealth = usHealth;
	data.hashModel = hashModel;
	data.vecMoveSpeed = vecMoveSpeed;
	data.hasDriver = hasDriver;
	data.driver = driverGUID;
}


CNetworkVehicle::~CNetworkVehicle()
{
	
}

std::vector<CNetworkVehicle *> CNetworkVehicle::All()
{
	return Vehicles;
}

CNetworkVehicle * CNetworkVehicle::GetByGUID(RakNet::RakNetGUID GUID)
{
	for each (CNetworkVehicle *veh in Vehicles)
		if (veh->rnGUID == GUID)
			return veh;
	return nullptr;
}

void CNetworkVehicle::SendGlobal(RakNet::Packet *packet)
{
	for each(auto *veh in Vehicles)
	{
		RakNet::BitStream bsOut;

		VehicleData data;
		veh->GetVehicleData(data);

		data.RPM = 0.2;
		data.Burnout = false;

		bsOut.Write(data);

		CRPCPlugin::Get()->Signal("CreateVehicle", &bsOut, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, packet->guid, false, false);
	}
}
