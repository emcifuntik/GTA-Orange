#pragma once

class CNetworkVehicle : public CVehicle
{
	static std::vector<CNetworkVehicle *> VehiclePool;
	Vehicle vehicle;
public:
	RakNet::RakNetGUID	m_GUID;
	CNetworkVehicle(Hash model, float x, float y, float z, float heading);
	static std::vector<CNetworkVehicle*> All();
	static CNetworkVehicle * GetByGUID(RakNet::RakNetGUID GUID);
	void SetVehicleData(VehicleData data);

	~CNetworkVehicle();
};

