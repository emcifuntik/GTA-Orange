#pragma once

class CNetworkVehicle : public CVehicle
{
	static std::vector<CNetworkVehicle *> VehiclePool;
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
	CVector3			m_vecMove;
	CNetworkVehicle();
public:
	RakNet::RakNetGUID	m_GUID;
	CNetworkVehicle(Hash model, float x, float y, float z, float heading);
	static std::vector<CNetworkVehicle*> All();
	static CNetworkVehicle * GetByGUID(RakNet::RakNetGUID GUID);
	static void Tick();

	void SetPosition(const CVector3 & vecPosition, bool bResetInterpolation);
	void SetRotation(const CVector3 & vecRotation, bool bResetInterpolation);

	void SetTargetPosition(const CVector3& vecPosition, unsigned long ulDelay);
	void SetTargetRotation(const CVector3& vecRotation, unsigned long ulDelay);
	void SetMoveToDirection(CVector3 vecPos, CVector3 vecMove, float iMoveSpeed);
	void SetVehicleData(VehicleData data, unsigned long ulDelay);

	bool HasTargetPosition() { return (m_interp.pos.ulFinishTime != 0); }
	bool HasTargetRotation() { return (m_interp.rot.ulFinishTime != 0); }

	void UpdateTargetPosition();
	void UpdateTargetRotation();

	void RemoveTargetPosition();
	void RemoveTargetRotation();
	void ResetInterpolation();

	void Interpolate();

	~CNetworkVehicle();
};

