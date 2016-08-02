#include "stdafx.h"

CNetworkConnection *CNetworkConnection::singleInstance = nullptr;

CNetworkConnection::CNetworkConnection()
{
	client = RakNet::RakPeerInterface::GetInstance();
}

CNetworkConnection::~CNetworkConnection()
{
	
}

CNetworkConnection * CNetworkConnection::Get()
{
	if (!singleInstance)
		singleInstance = new CNetworkConnection();
	return singleInstance;
}

bool CNetworkConnection::Connect(std::string host, unsigned short port)
{
	if (!host.empty() && port)
	{
		RakNet::SocketDescriptor socketDescriptor(0, 0);

		socketDescriptor.socketFamily = AF_INET;
		client->Startup(8, &socketDescriptor, 1);
		client->SetOccasionalPing(true);
		std::stringstream ss;
		ss << "Connecting to " << host << ":" << port;
		CChat::Get()->AddChatMessage(ss.str());
		connection = client->Connect(host.c_str(), port, 0, 0);
		RakAssert(connection == RakNet::CONNECTION_ATTEMPT_STARTED);
		bConnected = true;


		//CRPCPlugin::Get()->BindFunctions();
		return true;
	}
	return false;
}

void CNetworkConnection::Disconnect()
{
	bConnected = false;
	client->Shutdown(300);
	CChat::Get()->Clear();
	CUI::SendNotification("~b~Disconnected");
}

void CNetworkConnection::Tick()
{
	for (packet = client->Receive(); packet; client->DeallocatePacket(packet), packet = client->Receive()) {
		unsigned char packetID = packet->data[0];
		RakNet::BitStream bsIn(packet->data, packet->length, false);
		RakNet::BitStream bsOut;
		bsIn.IgnoreBytes(sizeof(unsigned char));

		switch (packetID) {
			case ID_CONNECTION_REQUEST_ACCEPTED:
			{
				CLocalPlayer::Get()->FreezePosition(false);
				CLocalPlayer::Get()->SetVisible(true);
				RakString playerName(CConfig::Get()->sNickName.c_str());
				bsOut.Write((unsigned char)ID_CONNECT_TO_SERVER);
				bsOut.Write(playerName);
				CLocalPlayer::Get()->SetMoney(0);
				CLocalPlayer::Get()->SetCoordsKeepVehicle(0.f, 0.f, 73.5f);

				
				client->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);

/*				WAIT(0);
				Hash adder = Utils::Hash("Adder");
				CNetworkVehicle *veh = new CNetworkVehicle(adder, -3.f, 6.f, 73.f, 0.f);
				VehicleData data;
				data.hashModel = adder;
				data.vecRot = CVector3(0.f, 0.f, 0.f);
				data.vecPos = CVector3(-3.f,6.f,73.f);*/

				/*RakNet::BitStream bsVehicle;
				bsVehicle.Write((unsigned char)ID_SEND_VEHICLE_DATA);
				bsVehicle.Write(data);
				client->Send(&bsVehicle, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);*/
				break;
			}
			case ID_CONNECTION_ATTEMPT_FAILED:
			{
				CLocalPlayer::Get()->SetMoney(0);
				CUI::SendNotification("~r~Not connected");
				break;
			}
			case ID_NO_FREE_INCOMING_CONNECTIONS:
			{
				CLocalPlayer::Get()->SetMoney(0);
				CUI::SendNotification("~r~Server is full!");
				break;
			}
			case ID_DISCONNECTION_NOTIFICATION:
			{
				CLocalPlayer::Get()->SetMoney(0);

				CUI::SendNotification("~r~Connection closed!");
				break;
			}
			case ID_CONNECTION_LOST:
			{
				CLocalPlayer::Get()->SetMoney(0);
				CUI::SendNotification("~r~Connection Lost!");
				break;
			}
			case ID_CONNECTION_BANNED:
			{
				CLocalPlayer::Get()->SetMoney(0);
				CUI::SendNotification("~r~You are banned!");
				break;
			}
			case ID_CONNECT_TO_SERVER:
			{
				bEstablished = true;
				break;
			}
			case ID_SEND_PLAYER_DATA:
			{


				RakNet::BitStream bsIn(packet->data, packet->length, false);
				bsIn.IgnoreBytes(sizeof(unsigned char));
				OnFootSyncData data;
				RakNet::RakNetGUID playerGUID;
				RakNet::RakString rsName;
				bsIn.Read(playerGUID);
				bsIn.Read(rsName);
				bsIn.Read(data);
				CNetworkPlayer::hFutureModel = data.hModel;
				CNetworkPlayer *remotePlayer = CNetworkPlayer::GetByGUID(playerGUID);
				if(rsName.GetLength())
					remotePlayer->SetName(std::string(rsName.C_String()));
				remotePlayer->SetOnFootData(data, 100);
				if (data.bShooting)
					remotePlayer->Interpolate();
				break;
			}
			case ID_SEND_VEHICLE_DATA:
			{
				break;
			}
			case ID_VEHICLE_SYNC:
			{

				int count;

				bsIn.Read(count);
				CUI::SendNotification(std::to_string(count));
				for (int i = 0; i < count; ++i)
				{
					VehicleData data;
					bsIn.Read(data);
					CNetworkVehicle * veh = CNetworkVehicle::GetByGUID(data.GUID);
					if (!veh)
					{
						veh = new CNetworkVehicle(data.hashModel, data.vecPos.fX, data.vecPos.fY, data.vecPos.fZ, data.vecRot.fZ);
						veh->m_GUID = data.GUID;

						CChat::Get()->AddChatMessage("Vehicle created", { 0, 255, 0, 255 });
						veh->SetVehicleData(data);
					}
					
				}
				break;
			}
			case ID_PLAYER_LEFT:
			{
				break;
			}
			default:
			{
				std::stringstream ss;
				ss << "[RakNet] Unknown message id: " << (int)packet->data[0] << ", message: " << packet->data;
				CChat::Get()->AddChatMessage(ss.str(), { 255, 100, 100, 255 });
				break;
			}
		}
	}
}
