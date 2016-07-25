#pragma once
class CNetworkPlayer
{
	// Static
	static std::vector<CNetworkPlayer*> _players;
	static void AddPlayer(CNetworkPlayer*);
	
	// Non-static
	unsigned int uiID;
	RakNet::RakNetGUID rnGUID;
	Hash hModel;
	bool bDead = false;
	bool bDucking = false;
	bool bBlipVisible = true;
	float fHeading;
	float fMoveSpeed;
	unsigned long ulWeapon;
	unsigned int uAmmo;
	unsigned short usHealth = 200;
	unsigned short usArmour = 0;
	bool bJumping = false;
	bool bAiming = false;
	bool bShooting = false;
	CVector3 vecPosition;
	CVector3 vecRotation;
	CVector3 vecMoveSpeed;
	CVector3 vecAim;
	std::string sName;
	size_t uMoney;
	float fTagDrawDistance = 50.f;
public:
	CNetworkPlayer(RakNet::RakNetGUID GUID);
	~CNetworkPlayer();

	static void Each(void(*func)(CNetworkPlayer*));
	static CNetworkPlayer *GetByGUID(RakNet::RakNetGUID GUID);
	static CNetworkPlayer *GetByID(UINT playerID);
	static void Tick();
	static UINT Count();
	static void Remove(int playerid);

	unsigned int GetID() { return uiID; }
	RakNet::RakNetGUID GetGUID() { return rnGUID; }
	void SetOnFootData(const OnFootSyncData& data);
	void GetOnFootData(OnFootSyncData& data);
	void HideBlip() { bBlipVisible = false; }
	void ShowBlip() { bBlipVisible = true; }
	bool IsBlipVisible() { return bBlipVisible; }
	void SetName(std::string playername) { sName = playername; }
	std::string GetName() { return sName; }
	void SetMoney(size_t money) { uMoney = money; }
	void GiveMoney(size_t money) { uMoney += money; }
	size_t GetMoney() { return uMoney; }
	void SetPosition(const CVector3& position) { vecPosition = position; }
	void GetPosition(CVector3& position) { position = vecPosition; }
	void SetHeading(float heading) { fHeading = heading; }
	float GetHeading() { return fHeading; }
	float GetTagDrawDistance() { return fTagDrawDistance; }
};