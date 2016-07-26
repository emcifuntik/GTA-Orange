#include "stdafx.h"

CRPCPlugin* CRPCPlugin::singleInstance = nullptr;

CRPCPlugin::CRPCPlugin()
{
	CNetworkConnection::Get()->server->AttachPlugin(this);
}

CRPCPlugin *CRPCPlugin::Get()
{
	if (!singleInstance)
		singleInstance = new CRPCPlugin();
	return singleInstance;
}


CRPCPlugin::~CRPCPlugin()
{
	RPC4::DestroyInstance(this);
}
