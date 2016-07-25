#include "stdafx.h"

int CNetworkConnection::shoots = 0;

CNetworkConnection * CNetworkConnection::singleInstance = nullptr;

CNetworkConnection::CNetworkConnection()
{
	server = RakNet::RakPeerInterface::GetInstance();
}

CNetworkConnection * CNetworkConnection::Get()
{
	if (!singleInstance)
		singleInstance = new CNetworkConnection();
	return singleInstance;
}

CNetworkConnection::~CNetworkConnection()
{
	server->Shutdown(300);
	RakNet::RakPeerInterface::DestroyInstance(server);
}

bool CNetworkConnection::Start(unsigned short maxPlayers, unsigned short port)
{
	if (maxPlayers && port)
	{
		socketDescriptors[0].port = port;
		socketDescriptors[0].socketFamily = AF_INET; // Test out IPV4
		socketDescriptors[1].port = port;
		socketDescriptors[1].socketFamily = AF_INET6; // Test out IPV6
		bool result = server->Startup(maxPlayers, socketDescriptors, 2) == RakNet::RAKNET_STARTED;
		server->SetMaximumIncomingConnections(maxPlayers);
		if (!result)
		{
			result = server->Startup(maxPlayers, socketDescriptors, 1) == RakNet::RAKNET_STARTED;
			if (!result)
			{
				std::cout << "Server not started" << std::endl;
				exit(EXIT_FAILURE);
			}
			else
				std::cout << "Server started" << std::endl;
		}
		server->SetTimeoutTime(15000, RakNet::UNASSIGNED_SYSTEM_ADDRESS);
		return true;
	}
	return false;
}

void CNetworkConnection::Tick()
{
	for (packet = server->Receive(); packet; server->DeallocatePacket(packet), packet = server->Receive())
	{
		unsigned char packetIdentifier = packet->data[0];
		RakNet::BitStream bsIn(packet->data, packet->length, false);
		bsIn.IgnoreBytes(sizeof(unsigned char));
		RakNet::BitStream bsOut;

		switch (packetIdentifier)
		{
			case ID_DISCONNECTION_NOTIFICATION:
			{
				std::cout << "Player disconnected " << packet->systemAddress.ToString(true) << std::endl;

				CNetworkPlayer *player = CNetworkPlayer::GetByGUID(packet->guid);
				UINT playerID = player->GetID();
				delete player;

				bsOut.Write((unsigned char)ID_PLAYER_LEFT);
				bsOut.Write(playerID);

				server->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
				break;
			}
			case ID_NEW_INCOMING_CONNECTION:
			{
				std::cout << "Incoming connection from " << packet->systemAddress.ToString(true) << std::endl;
				break;
			}
			case ID_CONNECT_TO_SERVER:
			{
				RakNet::RakString playerName;
				bsIn.Read(playerName);
				CNetworkPlayer *player = new CNetworkPlayer(packet->guid);
				player->SetName(playerName.C_String());
				bsOut.Write((unsigned char)ID_CONNECT_TO_SERVER);
				server->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
				break;
			}
			case ID_CHAT_MESSAGE:
			{
				RakNet::RakString playerText;
				bsIn.Read(playerText);

				/*if (OnPlayerTextMessage(sLUA, SPlayer::GetByGUID(packet->guid)->GetID(), std::string(playerText.C_String())) == 0)
				{
					std::stringstream ss;
					ss << "~b~" << SPlayer::GetByGUID(packet->guid)->GetName() << ":~w~ " << playerText.C_String();
					playerText = ss.str().c_str();
					bsOut.Write(playerText);
					NetworkManager->rpc.Signal("SendMessageToPlayer", &bsOut, HIGH_PRIORITY, RELIABLE_SEQUENCED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);
				}*/
				break;
			}
			case ID_SEND_PLAYER_DATA:
			{
				CNetworkPlayer *player = CNetworkPlayer::GetByGUID(packet->guid);
				OnFootSyncData data;
				bsIn.Read(data);
				if (data.bShooting)
					shoots++;
				player->SetOnFootData(data);
				
				/*if (OnPlayerUpdate(sLUA, player->GetID()) == 0)
					break;*/

				bsOut.Write((unsigned char)ID_SEND_PLAYER_DATA);
				bsOut.Write(packet->guid);

				player->GetOnFootData(data);
				/*data.vecPos.fX += 1.f;
				data.vecPos.fY += 1.f;*/
				bsOut.Write(data);
				server->Send(&bsOut, MEDIUM_PRIORITY, UNRELIABLE, 0, /*RakNet::UNASSIGNED_SYSTEM_ADDRESS*/packet->systemAddress, true);
				bsOut.Reset();
				break;
			}
			case ID_SEND_VEHICLE_DATA:
			{
				//OnPlayerUpdate(sLUA, SPlayer::GetByGUID(packet->guid)->GetID());
				server->Send(&bsIn, MEDIUM_PRIORITY, UNRELIABLE_SEQUENCED, 0, packet->systemAddress, true);
				break;
			}
			case ID_CONNECTED_PING:
			case ID_UNCONNECTED_PING:
			{
				std::cout << "Ping from " << packet->systemAddress.ToString(true) << std::endl;
				break;
			}
			case ID_CONNECTION_LOST:
			{
				std::cout << "Connection with " << packet->systemAddress.ToString(true) << " lost" << std::endl;
				//OnPlayerDisconnect(sLUA, SPlayer::GetByGUID(packet->guid)->GetID());

				CNetworkPlayer *player = CNetworkPlayer::GetByGUID(packet->guid);
				UINT playerID = player->GetID();
				delete player;
				CNetworkPlayer::Remove(playerID);

				bsOut.Write((unsigned char)ID_PLAYER_LEFT);
				bsOut.Write(playerID);

				server->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
				break;
			}
			default:
			{
				std::cout << "Unknown packet identifier: " << packet->data << std::endl;
				break;
			}
		}
	}
}
