#include "stdafx.h"

namespace FPlayer
{
	void SendNotification(RakNet::BitStream *bitStream, RakNet::Packet *packet) // string message
	{
		RakNet::RakString message;
		bitStream->Read(message);
		CUI::SendNotification(message.C_String());
	}

	void SendClientMessage(RakNet::BitStream *bitStream, RakNet::Packet *packet) // string message, color_t color
	{
		RakNet::RakString message;
		color_t color;
		bitStream->Read(message);
		bitStream->Read(color);
		CChat::Get()->AddChatMessage(message.C_String(), color);
	}

	void GivePlayerWeapon(RakNet::BitStream *bitStream, RakNet::Packet *packet) // Hash weapon, int ammo
	{
		Hash weapon;
		unsigned int ammo;
		bitStream->Read(weapon);
		bitStream->Read(ammo);
		CLocalPlayer::Get()->GiveWeapon(weapon, ammo);
	}

	void RemovePlayerWeapon(RakNet::BitStream *bitStream, RakNet::Packet *packet) // Hash weapon
	{
		Hash weapon;
		bitStream->Read(weapon);
		CLocalPlayer::Get()->RemoveWeapon(weapon);
	}

	void RemoveAllWeapons(RakNet::BitStream *bitStream, RakNet::Packet *packet) // no arguments
	{
		CLocalPlayer::Get()->RemoveAllWeapons();
	}

	void GivePlayerAmmo(RakNet::BitStream *bitStream, RakNet::Packet *packet) // Hash weapon, unsigned int ammo
	{
		Hash weapon;
		unsigned int ammo;
		bitStream->Read(weapon);
		bitStream->Read(ammo);
		CLocalPlayer::Get()->AddAmmo(weapon, ammo);
	}

	void RemovePlayerAmmo(RakNet::BitStream *bitStream, RakNet::Packet *packet) // Hash weapon, unsigned int ammo
	{
		Hash weapon;
		unsigned int ammo;
		bitStream->Read(weapon);
		bitStream->Read(ammo);
		CLocalPlayer::Get()->RemoveAmmo(weapon, ammo);
	}

	void SetPlayerMoney(RakNet::BitStream *bitStream, RakNet::Packet *packet)
	{

	}

	void SetPlayerPos(RakNet::BitStream *bitStream, RakNet::Packet *packet) // CVector3 pos
	{
		CVector3 pos;
		bitStream->Read(pos);
		CLocalPlayer::Get()->SetCoordsKeepVehicle(pos.fX, pos.fY, pos.fZ);
	}

	void SetPlayerHeading(RakNet::BitStream *bitStream, RakNet::Packet *packet) // float heading
	{
		float heading;
		bitStream->Read(heading);
		CLocalPlayer::Get()->SetHeading(heading);
	}

	void SetPlayerHealth(RakNet::BitStream *bitStream, RakNet::Packet *packet) // unsigned short health
	{
		unsigned short health;
		bitStream->Read(health);
		CLocalPlayer::Get()->SetHealth(health);
	}

	void SetPlayerArmour(RakNet::BitStream *bitStream, RakNet::Packet *packet) // unsigned short armour
	{
		unsigned short armour;
		bitStream->Read(armour);
		CLocalPlayer::Get()->SetArmour(armour);
	}

	void SetPlayerModel(RakNet::BitStream *bitStream, RakNet::Packet *packet) // Hash model
	{
		Hash model;
		bitStream->Read(model);
		CLocalPlayer::Get()->ChangeModel(model);
	}
}

