#pragma once

class CPedestrian;

class CLocalPlayer: public CPedestrian
{
	static CLocalPlayer* Instance;
	CLocalPlayer();
public:
	CVector3 *aimPosition = nullptr;
	Hash newModel = 0;

	static CLocalPlayer *Get();

	void ChangeModel(Hash model);
	void Connect();
	void Tick();
	void GetOnFootSync(OnFootSyncData& onfoot);
	void CLocalPlayer::SendOnFootData();
	void SetMoney(int money);
	~CLocalPlayer();
};

