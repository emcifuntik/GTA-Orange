#pragma once

class ISteamUser
{
public:
	// returns the HSteamUser this interface represents
	// this is only used internally by the API, and by a few select interfaces that support multi-user
	virtual void GetHSteamUser() = 0;

	// returns true if the Steam client current has a live connection to the Steam servers. 
	// If false, it means there is no active connection due to either a networking issue on the local machine, or the Steam server is down/busy.
	// The Steam client will automatically be trying to recreate the connection as often as possible.
	virtual bool BLoggedOn() = 0;

	// returns the CSteamID of the account currently logged into the Steam client
	// a CSteamID is a unique identifier for an account, and used to differentiate users in all parts of the Steamworks API
	virtual void GetSteamID(int64_t **ptr) = 0;
};

class ISteamFriends
{
public:
	virtual const char *GetPersonaName() = 0;
};

class CSteamFriends :
	public ISteamFriends
{
public:
	virtual const char *GetPersonaName()
	{
		return "Funtik";
	}
};

class CSteamUser :
	public ISteamUser
{
public:
	virtual void GetHSteamUser() {}
	virtual bool BLoggedOn() { return true; }
	virtual void GetSteamID(int64_t** ptr)
	{
		(*ptr) = nullptr;
	}
};

enum SteamCallback
{
	UserStatsReceived = 1101,
	UserStatsStored,
	UserAchievementStored,
	GameOverlayActivated = 331,
	GamepadTextInputDismissed = 714,
	Unknown1 = 1005,
	MicroTxnAuthorizationResponse = 152,
	Unknown2 = 337
};

//void SteamAPI_RegisterCallback(void *obj, int callbackID);
//void SteamAPI_UnregisterCallback(void *obj);
//void * SteamApps();
//void * SteamUserStats();
//void * SteamUtils();
CSteamFriends * SteamFriends();
CSteamUser * SteamUser();
//bool SteamAPI_Init();
bool SteamAPI_RestartAppIfNecessary();
//void SteamAPI_RunCallbacks();
