#pragma once

class CPedestrian;

class CLocalPlayer: public CPedestrian
{
	static CLocalPlayer* Instance;
	CLocalPlayer();
public:
	Hash newModel = 0;

	static float offsetX;
	static float offsetY;
	static float alpha;
	static CLocalPlayer *Get();

	void ChangeModel(Hash model);
	void Connect();
	void Tick();
	void GetOnFootSync(OnFootSyncData& onfoot);
	void CLocalPlayer::SendOnFootData();
	void SetMoney(int money);
	void ShowNotification(std::string text);
	bool GetAimPosition(CVector3 & aimPos);
	~CLocalPlayer();
};

