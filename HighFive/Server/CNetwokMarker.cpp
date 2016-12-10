#include "stdafx.h"

std::vector<CNetworkMarker *> CNetworkMarker::GlobalMarkers;
std::vector<CNetworkMarker *> CNetworkMarker::PlayerMarkers;

CNetworkMarker::CNetworkMarker(float x, float y, float z, float height, float radius, int playerid)
{
	RakNet::BitStream bsOut;

	rnGUID = RakNetGUID::RakNetGUID(rand());

	bsOut.Write(rnGUID);
	bsOut.Write(x);
	bsOut.Write(y);
	bsOut.Write(z);

	bsOut.Write(height);
	bsOut.Write(radius);

	vecPos = CVector3(x, y, z);
	this->height = height;
	this->radius = radius;
	this->playerid = playerid;

	if (playerid == -1)
	{
		CRPCPlugin::Get()->Signal("CreateMarker", &bsOut, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);
		GlobalMarkers.push_back(this);
	}
	else {
		RakNetGUID guid = CNetworkPlayer::GetByID(playerid)->GetGUID();
		CRPCPlugin::Get()->Signal("CreateMarker", &bsOut, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, guid, false, false);
		PlayerMarkers.push_back(this);
	}

}

void CNetworkMarker::Delete()
{
}


CNetworkMarker::~CNetworkMarker()
{

}

void CNetworkMarker::SendGlobal(RakNet::Packet *packet)
{
	for each(auto *Marker in GlobalMarkers)
	{
		RakNet::BitStream bsOut;

		bsOut.Write(Marker->rnGUID);
		bsOut.Write(Marker->vecPos.fX);
		bsOut.Write(Marker->vecPos.fY);
		bsOut.Write(Marker->vecPos.fZ);
		bsOut.Write(Marker->height);
		bsOut.Write(Marker->radius);

		CRPCPlugin::Get()->Signal("CreateMarker", &bsOut, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, packet->guid, false, false);
	}
}

CNetworkMarker * CNetworkMarker::GetByGUID(RakNetGUID guid)
{
	for each (CNetworkMarker *Marker in GlobalMarkers)
		if (Marker && Marker->rnGUID == guid)
			return Marker;

	for each (CNetworkMarker *Marker in PlayerMarkers)
		if (Marker && Marker->rnGUID == guid)
			return Marker;

	return nullptr;
}

std::vector<CNetworkMarker *> CNetworkMarker::AllGlobal()
{
	return GlobalMarkers;
}

