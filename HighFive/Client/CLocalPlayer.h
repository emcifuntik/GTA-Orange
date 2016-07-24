#pragma once

class CPedestrian;

class CLocalPlayer: public CPedestrian
{
	static CLocalPlayer* Instance;
	CLocalPlayer();
public:
	static CLocalPlayer *Get();

	void SetModel(Hash model);
	void Connect();
	void Tick();
	void GetOnFootSync(OnFootSyncData& onfoot);
	void CLocalPlayer::SendOnFootData();
	void ShowNotification(std::string text);
	void GetAimPosition(CVector3 & aimPos);
	~CLocalPlayer();
};

