#include "stdafx.h"

std::vector<CNetworkBlip *> CNetworkBlip::GlobalBlips;

CNetworkBlip::CNetworkBlip(float x, float y, float z, float scale, int color, int sprite)
{
	RakNet::BitStream bsOut;

	rnGUID = RakNetGUID::RakNetGUID(rand());

	bsOut.Write(rnGUID);
	bsOut.Write(x);
	bsOut.Write(y);
	bsOut.Write(z);
	bsOut.Write(scale);
	bsOut.Write(color);
	bsOut.Write(sprite);

	CRPCPlugin::Get()->Signal("CreateBlip", &bsOut, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);
	
	vecPos = CVector3(x, y, z);
	this->scale = scale;
	this->color = color;
	this->sprite = sprite;

	GlobalBlips.push_back(this);
}

void CNetworkBlip::SetPosition(CVector3 position)
{
}

void CNetworkBlip::Delete()
{
}


CNetworkBlip::~CNetworkBlip()
{

}

void CNetworkBlip::SendGlobal(RakNet::Packet *packet)
{
	for each(auto *blip in GlobalBlips)
	{
		RakNet::BitStream bsOut;

		bsOut.Write(blip->rnGUID);
		bsOut.Write(blip->vecPos.fX);
		bsOut.Write(blip->vecPos.fY);
		bsOut.Write(blip->vecPos.fZ);
		bsOut.Write(blip->scale);
		bsOut.Write(blip->color);
		bsOut.Write(blip->sprite);

		CRPCPlugin::Get()->Signal("CreateBlip", &bsOut, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, packet->guid, false, false);
	}
}

std::vector<CNetworkBlip *> CNetworkBlip::AllGlobal()
{
	return GlobalBlips;
}

