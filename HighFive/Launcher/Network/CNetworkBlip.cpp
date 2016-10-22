#include "stdafx.h"
#include "CNetworkBlip.h"

std::vector<CNetworkBlip *> CNetworkBlip::BlipPool;

CNetworkBlip::CNetworkBlip(RakNetGUID guid, float x, float y, float z, float scale, int color, int sprite)
{
	m_GUID = guid;
	this->vecPos = CVector3(x, y, z);
	this->scale = scale;
	this->color = color;
	this->sprite = sprite;

	Handle = UI::ADD_BLIP_FOR_COORD(x, y, z);
	UI::SET_BLIP_SCALE(Handle, scale);
	UI::SET_BLIP_AS_SHORT_RANGE(Handle, false);

	BlipPool.push_back(this);
}

void CNetworkBlip::SetScale(float scale)
{
	UI::SET_BLIP_SCALE(Handle, scale);
}

CNetworkBlip::~CNetworkBlip()
{
}

std::vector<CNetworkBlip*> CNetworkBlip::All()
{
	return BlipPool;
}

CNetworkBlip * CNetworkBlip::GetByGUID(RakNet::RakNetGUID GUID)
{
	for each (CNetworkBlip *_Blip in BlipPool)
	{
		if (_Blip->m_GUID == GUID)
			return _Blip;
	}
	return nullptr;
}
