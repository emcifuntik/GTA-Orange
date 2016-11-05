#pragma once
class SResource
{
public:
	SResource(const char* _name);
	bool Start();
	bool OnPlayerConnect(long playerid);
	bool OnTick();
	bool OnKeyStateChanged(long playerid, int keycode, bool isUp);
	~SResource();
};

