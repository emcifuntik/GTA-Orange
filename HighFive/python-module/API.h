#pragma once
#include <string>
#include "../../Shared/CVector3.h"

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

	//TODO
	//virtual bool PlayerExists(long playerid) = 0;
	//virtual bool VehicleExists(long playerid) = 0;
	//virtual int CreateVehicle(long hash, float x, float y, float z, float pitch, float yaw, float roll) = 0;
	virtual bool SetVehiclePosition(int vehicleid, float x, float y, float z) = 0;
	virtual CVector3 GetVehiclePosition(int vehicleid) = 0;

	virtual bool CreatePickup(int type, float x, float y, float z, float scale) = 0;
	virtual unsigned long CreateBlipForAll(float x, float y, float z, float scale, int color, int sprite) = 0;
	virtual void SetBlipScale(unsigned long guid, float scale) = 0;

	virtual bool Print3DText(const char * text, float x, float y, float z, float scale) = 0;
};

class API:
	public APIBase 
{
public:
	static API * instance;
	static void Set(API * api){instance = api;}
	static API& Get(){return *instance;}
};
