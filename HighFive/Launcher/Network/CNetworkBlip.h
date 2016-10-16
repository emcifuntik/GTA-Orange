#pragma once

class CNetworkBlip
{
	static std::vector<CNetworkBlip *> BlipPool;

	CVector3 vecPos;
	float scale;
	int color;
	int sprite;
public:
	RakNet::RakNetGUID	m_GUID;
	CNetworkBlip(RakNetGUID guid, float x, float y, float z, float scale, int color, int sprite);
	static std::vector<CNetworkBlip*> All();
	static CNetworkBlip * GetByGUID(RakNet::RakNetGUID GUID);

	~CNetworkBlip();
};

