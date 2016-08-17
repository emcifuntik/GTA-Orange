#pragma once

class CPedestrian;

class CLocalPlayer: public CPedestrian
{
	static CLocalPlayer* Instance;
	CLocalPlayer();
public:
#if _DEBUG
	bool isDebug = false;
#endif
	CVector3 *aimPosition = nullptr;
	Hash newModel = 0;

	static CLocalPlayer *Get();

	void ChangeModel(Hash model);
	void Connect();
	void Tick();
	void GetOnFootSync(OnFootSyncData& onfoot);
	void SendOnFootData();
	void SendTasks();
	void SetMoney(int money);
	~CLocalPlayer();
};

