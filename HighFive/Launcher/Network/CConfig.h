#pragma once
class CConfig
{
	static CConfig *singleInstance;
	CConfig();
public:
	static CConfig *Get()
	{
		if (!singleInstance)
			singleInstance = new CConfig();
		return singleInstance;
	}

	tinyxml2::XMLDocument doc;
	const char *sFileName = "config.xml";
	std::string sNickName;
	std::string sIP;
	unsigned int uiPort;

	~CConfig();
};

