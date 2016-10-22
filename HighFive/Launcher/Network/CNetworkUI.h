#pragma once

struct screenInfo_
{
	bool shown = false;
	char* msg;

};

class CNetworkUI
{
	static CNetworkUI* Instance;
public:
	CNetworkUI();
	bool Render();
	bool SetScreenInfo(const char* msg);
	bool UnsetScreenInfo();
	~CNetworkUI();
	static CNetworkUI* Get();
};