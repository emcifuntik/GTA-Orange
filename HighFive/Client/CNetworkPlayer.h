#pragma once

class CNetworkPlayer: public CPedestrian
{
private:
	static std::vector<CNetworkPlayer *> PlayersPool;
	struct
	{
		struct
		{
			CVector3      vecStart;
			CVector3      vecTarget;
			CVector3      vecError;
			float         fLastAlpha;
			unsigned long ulStartTime;
			unsigned long ulFinishTime;
		} pos;
		struct
		{
			float         fStart;
			float         fTarget;
			float         fError;
			float         fLastAlpha;
			unsigned long ulStartTime;
			unsigned long ulFinishTime;
		} heading;
		struct
		{
			CVector3      vecStart;
			CVector3      vecTarget;
			CVector3      vecError;
			float         fLastAlpha;
			unsigned long ulStartTime;
			unsigned long ulFinishTime;
		} rot;
	}					m_interp;
	RakNet::RakNetGUID	m_GUID;
	std::string			m_Name;
	CVector3			m_vecMove;
	bool				m_Spawned = false;
	bool				m_Ducking = false;
	bool				m_Jumping = false;
	bool				m_TagVisible = true;
	float				m_BlendRatio;
	float				lastBlendRatio;
	int					updateTick = 0;
	int					lastTick = 0;
	int					tasksToIgnore = 0;
	CNetworkPlayer();
public:
	static std::vector<CNetworkPlayer*> All();
	static void DeleteNotExists(const std::vector<RakNet::RakNetGUID>& GUIDs);
	static CNetworkPlayer * GetByGUID(RakNet::RakNetGUID GUID);
	static void Tick();

	void UpdateLastTickTime();
	int GetTickTime();
	
	std::string GetName() { return m_Name; }
	void SetName(std::string Name) { m_Name = Name; }

	bool IsSpawned();
	void SetPosition(const CVector3 & vecPosition, bool bResetInterpolation);
	void SetRotation(const CVector3 & vecRotation, bool bResetInterpolation);
	void Spawn(const CVector3& vecPosition);

	void SetTargetPosition(const CVector3& vecPosition, unsigned long ulDelay);
	void SetTargetRotation(const CVector3& vecRotation, unsigned long ulDelay);
	void SetMoveToDirection(CVector3 vecPos, CVector3 vecMove, float iMoveSpeed);
	void SetOnFootData(OnFootSyncData data, unsigned long ulDelay);

	bool HasTargetPosition() { return (m_interp.pos.ulFinishTime != 0); }
	bool HasTargetRotation() { return (m_interp.rot.ulFinishTime != 0); }

	void UpdateTargetPosition();
	void UpdateTargetRotation();

	void SetModel(Hash model);

	void RemoveTargetPosition();
	void RemoveTargetRotation();
	void ResetInterpolation();

	void Interpolate();

	void DrawTag();

	~CNetworkPlayer();
};
