#include "stdafx.h"

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
				log << "Server not started" << std::endl;
				exit(EXIT_FAILURE);
			}
			else
				log << "Server started" << std::endl;
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
				log << "Player disconnected " << packet->systemAddress.ToString(true) << std::endl;

				CNetworkPlayer *player = CNetworkPlayer::GetByGUID(packet->guid);
				UINT playerID = player->GetID();
				Squirrel::PlayerDisconnect(playerID, 1);
				delete player;

				bsOut.Write((unsigned char)ID_PLAYER_LEFT);
				bsOut.Write(playerID);

				server->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
				break;
			}
			case ID_NEW_INCOMING_CONNECTION:
			{
				log << "Incoming connection from " << packet->systemAddress.ToString(true) << std::endl;

				break;
			}
			case ID_CONNECT_TO_SERVER:
			{
				RakNet::RakString playerName;
				bsIn.Read(playerName);
				CNetworkPlayer *player = new CNetworkPlayer(packet->guid);
				player->SetName(playerName.C_String());

				Squirrel::PlayerConnect(player->GetID());

				bsOut.Write((unsigned char)ID_CONNECT_TO_SERVER);

				server->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);


				RakNet::BitStream bsveh;
				int count = CNetworkVehicle::Count();
				bsveh.Write((unsigned char)ID_VEHICLE_SYNC);
				bsveh.Write(count);
				for each (CNetworkVehicle *temp in CNetworkVehicle::All())
				{
					VehicleData data;
					temp->GetVehicleData(data);
					bsveh.Write(data);
				}
				log << "LOL1";
				server->Send(&bsveh, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
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
				player->SetOnFootData(data);
				
				/*if (Squirrel::PlayerUpdate(player->GetID()) == SQFalse)
					break;*/

				bsOut.Write((unsigned char)ID_SEND_PLAYER_DATA);
				bsOut.Write(packet->guid);
				RakNet::RakString rsName(player->GetName().c_str());
				bsOut.Write(rsName);

				player->GetOnFootData(data);
#if 0
				data.vecPos.fX += 3.f;
				data.vecPos.fY += 3.f;
				if (data.vehGuid > 0)
				{
					for each (CNetworkVehicle *veh in CNetworkVehicle::All())
					{
						int temp = veh->rnGUID.ToUint32(veh->rnGUID);
						log << temp << std::endl;
						if (data.vehGuid != temp) { data.vehGuid = temp; break; }
					}
				}
#endif		

				bsOut.Write(data);
#if 0 
				server->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
#else
				server->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, true);
#endif
				bsOut.Reset();
				break;
			}
			case ID_VEHICLE_SYNC:
			{


				break;
			}
			case ID_SEND_VEHICLE_DATA:
			{
				VehicleData data;
				bsIn.Read(data);
				CNetworkVehicle *veh = new CNetworkVehicle(data.hashModel, data.vecPos.fX, data.vecPos.fY, data.vecPos.fZ, data.vecRot.fZ);
				veh->SetVehicleData(data);
				log << "CREATE VEHICLE";
				//server->Send(&bsIn, MEDIUM_PRIORITY, UNRELIABLE_SEQUENCED, 0, packet->systemAddress, true);
				RakNet::BitStream bsOut;
				int count = CNetworkVehicle::Count();
				bsOut.Write((unsigned char)ID_VEHICLE_SYNC);
				bsOut.Write(count);
				for each (CNetworkVehicle *temp in CNetworkVehicle::All())
				{
					VehicleData data;
					temp->GetVehicleData(data);
					bsOut.Write(data);
				}
				server->Send(&bsOut, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
				break;
			}
			case ID_CONNECTED_PING:
			case ID_UNCONNECTED_PING:
			{
				log << "Ping from " << packet->systemAddress.ToString(true) << std::endl;
				break;
			}
			case ID_CONNECTION_LOST:
			{
				log << "Connection with " << packet->systemAddress.ToString(true) << " lost" << std::endl;
				//OnPlayerDisconnect(sLUA, SPlayer::GetByGUID(packet->guid)->GetID());

				CNetworkPlayer *player = CNetworkPlayer::GetByGUID(packet->guid);
				UINT playerID = player->GetID();
				Squirrel::PlayerDisconnect(playerID, 2);

				delete player;
				CNetworkPlayer::Remove(playerID);

				bsOut.Write((unsigned char)ID_PLAYER_LEFT);
				bsOut.Write(playerID);

				server->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
				break;
			}
			default:
			{
				log << "Unknown packet identifier: " << packet->data << std::endl;
				break;
			}
		}
	}
}
