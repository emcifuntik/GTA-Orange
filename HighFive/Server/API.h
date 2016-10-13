#pragma once
#include <string>

class APIBase {
public:
	//Player
	virtual bool SetPlayerPosition(long playerid, float x, float y, float z) = 0;
	virtual CVector3 GetPlayerPosition(long playerid) = 0;
	virtual bool IsPlayerInRange(long playerid, float x, float y, float z, float range) = 0;
	virtual bool SetPlayerHeading(long playerid, float angle) = 0;
	virtual bool GivePlayerWeapon(long playerid, long weapon, long ammo) = 0;
	virtual bool GivePlayerAmmo(long playerid, long weapon, long ammo) = 0;
	virtual bool GivePlayerMoney(long playerid, long money) = 0;
	virtual bool SetPlayerMoney(long playerid, long money) = 0;
	virtual bool ResetPlayerMoney(long playerid) = 0;
	virtual size_t GetPlayerMoney(long playerid) = 0;
	virtual bool SetPlayerModel(long playerid, long model) = 0;
	virtual long GetPlayerModel(long playerid) = 0;
	virtual bool SetPlayerName(long playerid, const char * name) = 0;
	virtual std::string GetPlayerName(long playerid) = 0;
	virtual bool SetPlayerHealth(long playerid, float health) = 0;
	virtual float GetPlayerHealth(long playerid) = 0;
	virtual bool SetPlayerArmour(long playerid, float armour) = 0;
	virtual float GetPlayerArmour(long playerid) = 0;
	virtual bool SetPlayerColor(long playerid, unsigned int color) = 0;
	virtual unsigned int GetPlayerColor(long playerid) = 0;
	virtual void BroadcastClientMessage(const char * message, unsigned int color) = 0;
	virtual bool SendClientMessage(long playerid, const char * message, unsigned int color) = 0;
	//World
	virtual void Print(const char * message) = 0;
	virtual long Hash(const char * str) = 0;
};

class API: 
	public APIBase 
{
	static API * instance;
public:
	//Player
	bool SetPlayerPosition(long playerid, float x, float y, float z);
	CVector3 GetPlayerPosition(long playerid);
	bool IsPlayerInRange(long playerid, float x, float y, float z, float range);
	bool SetPlayerHeading(long playerid, float angle);
	bool GivePlayerWeapon(long playerid, long weapon, long ammo);
	bool GivePlayerAmmo(long playerid, long weapon, long ammo);
	bool GivePlayerMoney(long playerid, long money);
	bool SetPlayerMoney(long playerid, long money);
	bool ResetPlayerMoney(long playerid);
	size_t GetPlayerMoney(long playerid);
	bool SetPlayerModel(long playerid, long model);
	long GetPlayerModel(long playerid);
	bool SetPlayerName(long playerid, const char * name);
	std::string GetPlayerName(long playerid);
	bool SetPlayerHealth(long playerid, float health);
	float GetPlayerHealth(long playerid);
	bool SetPlayerArmour(long playerid, float armour);
	float GetPlayerArmour(long playerid);
	bool SetPlayerColor(long playerid, unsigned int color);
	unsigned int GetPlayerColor(long playerid);
	void BroadcastClientMessage(const char * message, unsigned int color);
	bool SendClientMessage(long playerid, const char * message, unsigned int color);

	//Vehicle
	bool CreateVehicle(long hash, float x, float y, float z, float heading);

	bool SetVehiclePosition(const char * text, float x, float y, float z, float scale);

	CVector3 GetVehiclePosition(const char * text, float x, float y, float z, float scale);

	bool CreatePickup(int type, float x, float y, float z, float scale);

	//World
	void Print(const char * message);
	bool Print3DText(const char * text, float x, float y, float z, float scale);
	long Hash(const char * str);

	static API * Get()
	{
		if (!instance)
			instance = new API();
		return instance;
	}
};
