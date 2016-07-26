#pragma once
class CRPCPlugin
{
	static CRPCPlugin* singleInstance;
	CRPCPlugin();
public:
	static CRPCPlugin* Get();
	void BindFunctions();

	RPC4 rpc;
	~CRPCPlugin();
};

