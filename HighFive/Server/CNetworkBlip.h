#pragma once
class CNetworkBlip
{
	static std::vector<CNetworkBlip *> GlobalBlips;
	CVector3 vecPos;
	float scale;
	int color;
	int sprite;
public:
	RakNet::RakNetGUID rnGUID;
	static std::vector<CNetworkBlip *> AllGlobal();
	CNetworkBlip(float x, float y, float z, float scale, int color, int sprite);

	void SetPosition(CVector3 position);

	void Delete();

	~CNetworkBlip();
	static void SendGlobal(RakNet::Packet * packet);
};

