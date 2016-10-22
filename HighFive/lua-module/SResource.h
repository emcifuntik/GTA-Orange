#pragma once
class SResource
{
public:
	SResource(const char* _name);
	bool Start();
	bool OnPlayerConnect(long playerid);
	bool OnTick();
	~SResource();
};

