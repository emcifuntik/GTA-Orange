#pragma once
class CConfig
{
	CConfig();

	static CConfig* singleInstance;
public:
	static CConfig* Get();
	std::string Hostname;
	unsigned short Port;
	unsigned short MaxPlayers;
	std::vector<std::string> Scripts;
	std::string LogTimeFormat;
	~CConfig();
};

