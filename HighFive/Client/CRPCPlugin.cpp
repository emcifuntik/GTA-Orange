#include "stdafx.h"

CRPCPlugin* CRPCPlugin::singleInstance = nullptr;

CRPCPlugin::CRPCPlugin()
{
	CNetworkConnection::Get()->client->AttachPlugin(&rpc);
}

void CRPCPlugin::BindFunctions()
{
	#pragma region Player functions
	rpc.RegisterSlot("SendNotification", FPlayer::SendNotification, 0);
	rpc.RegisterSlot("SendClientMessage", FPlayer::SendClientMessage, 0);
	rpc.RegisterSlot("GivePlayerWeapon", FPlayer::GivePlayerWeapon, 0);
	rpc.RegisterSlot("RemovePlayerWeapon", FPlayer::RemovePlayerWeapon, 0);
	rpc.RegisterSlot("RemoveAllWeapons", FPlayer::RemoveAllWeapons, 0);
	rpc.RegisterSlot("GivePlayerAmmo", FPlayer::GivePlayerAmmo, 0);
	rpc.RegisterSlot("RemovePlayerAmmo", FPlayer::RemovePlayerAmmo, 0);
	rpc.RegisterSlot("SetPlayerMoney", FPlayer::SetPlayerMoney, 0);
	rpc.RegisterSlot("SetPlayerPos", FPlayer::SetPlayerPos, 0);
	rpc.RegisterSlot("SetPlayerHeading", FPlayer::SetPlayerHeading, 0);
	rpc.RegisterSlot("SetPlayerHealth", FPlayer::SetPlayerHealth, 0);
	rpc.RegisterSlot("SetPlayerArmour", FPlayer::SetPlayerArmour, 0);
	rpc.RegisterSlot("SetPlayerModel", FPlayer::SetPlayerModel, 0);
	#pragma endregion

}

CRPCPlugin * CRPCPlugin::Get()
{
	if (!singleInstance)
		singleInstance = new CRPCPlugin();
	return singleInstance;
}

CRPCPlugin::~CRPCPlugin()
{
	CNetworkConnection::Get()->client->AttachPlugin(&rpc);
}