#pragma once

class CNetworkConnection
{
	static CNetworkConnection * singleInstance;
	CNetworkConnection();

	RPC4 rpc;
	RakNet::RakNetStatistics *stat;
	RakNet::Packet* packet;
	RakNet::SocketDescriptor socketDescriptors[2];
	RakNet::ConnectionAttemptResult connection;
	bool bConnected = false;
public:
	RakNet::RakPeerInterface *server;
	//Debug
	static int shoots;

	static CNetworkConnection * Get();

	bool Start(unsigned short maxPlayers, unsigned short port);
	void Tick();

	~CNetworkConnection();
};