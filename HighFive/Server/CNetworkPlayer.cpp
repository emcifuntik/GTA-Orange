#include "stdafx.h"

std::vector<CNetworkPlayer*> CNetworkPlayer::_players;

void CNetworkPlayer::Each(void(*func)(CNetworkPlayer *))
{
	for each (CNetworkPlayer *player in _players)
		if (player)
			func(player);
}

CNetworkPlayer * CNetworkPlayer::GetByGUID(RakNet::RakNetGUID GUID)
{
	for each (CNetworkPlayer *player in _players)
		if (player->rnGUID == GUID)
			return player;
	CNetworkPlayer *player = new CNetworkPlayer(GUID);
	return player;
}

CNetworkPlayer * CNetworkPlayer::GetByID(UINT playerID)
{
	if (playerID < _players.size())
		return _players[playerID];
	return nullptr;
}

void CNetworkPlayer::AddPlayer(CNetworkPlayer *player)
{
	int playerID = -1;
	for (size_t i = 0; i < _players.size(); ++i)
	{
		if (!_players[i])
		{
			playerID = (int)i;
			break;
		}
	}
	if (playerID == -1)
	{
		player->uiID = (unsigned int)_players.size();
		_players.push_back(player);
	}
	else
	{
		player->uiID = (unsigned int)playerID;
		_players[playerID] = player;
	}
}

CNetworkPlayer::CNetworkPlayer(RakNet::RakNetGUID GUID):rnGUID(GUID)
{
	AddPlayer(this);
}

CNetworkPlayer::~CNetworkPlayer()
{
}

void CNetworkPlayer::SetOnFootData(const OnFootSyncData& data)
{
	hModel = data.hModel;
	bJumping = data.bJumping;
	fMoveSpeed = data.fMoveSpeed;
	vecPosition = data.vecPos;
	vecRotation = data.vecRot;
	fHeading = data.fHeading;
	ulWeapon = data.ulWeapon;
	uAmmo = data.uAmmo;
	usHealth = data.usHealth;
	usArmour = data.usArmour;
	bDucking = data.bDuckState;
	vecMoveSpeed = data.vecMoveSpeed;
	vecAim = data.vecAim;
	bAiming = data.bAiming;
	bShooting = data.bShooting;
}

void CNetworkPlayer::GetOnFootData(OnFootSyncData& data)
{
	data.hModel = hModel;
	data.bJumping = bJumping;
	data.fMoveSpeed = fMoveSpeed;
	data.vecPos = vecPosition;
	data.vecRot = vecRotation;
	data.fHeading = fHeading;
	data.ulWeapon = ulWeapon;
	data.uAmmo = uAmmo;
	data.usHealth = usHealth;
	data.usArmour = usArmour;
	data.bDuckState = bDucking;
	data.vecMoveSpeed = vecMoveSpeed;
	data.vecAim = vecAim;
	data.bAiming = bAiming;
	data.bShooting = bShooting;
}

void CNetworkPlayer::Tick()
{
	for each (CNetworkPlayer *player in _players)
	{
		if (!player)
			continue;
		if (player->usHealth <= 0 && !player->bDead)
		{
			// Call death callback
			player->bDead = true;
		}

		if (player->usHealth > 0 && player->bDead) {
			// Spawn player here
			player->bDead = false;
		}
	}
}

UINT CNetworkPlayer::Count()
{
	UINT count = 0;
	for each (CNetworkPlayer *player in _players)
	{
		if (player)
			count++;
	}
	return count;
}

void CNetworkPlayer::Remove(int playerid)
{
	_players[playerid] = nullptr;
}
