#include "stdafx.h"

bool steamUserCalled = false;

void SteamAPI_RegisterCallback(void *obj, int callbackID)
{

}

void SteamAPI_UnregisterCallback(void *obj)
{

}

void * SteamApps()
{
	return nullptr;
}

void * SteamUserStats()
{
	return nullptr;
}

void * SteamUtils()
{
	return nullptr;
}

CSteamFriends * SteamFriends()
{
	log_debug << __FUNCTION__ << " called" << std::endl;
	return new CSteamFriends();
}

CSteamUser * SteamUser()
{
	log_debug << __FUNCTION__ << " called" << std::endl;
	return new CSteamUser();
}

bool SteamAPI_Init()
{
	return true;
}

bool SteamAPI_RestartAppIfNecessary()
{
	return false;
}

void SteamAPI_RunCallbacks()
{
	return;
}
