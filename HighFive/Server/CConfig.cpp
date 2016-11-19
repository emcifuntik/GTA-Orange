#include "stdafx.h"

CConfig* CConfig::singleInstance = nullptr;


CConfig::CConfig()
{
	std::ifstream fin("config.yml");
	YAML::Parser parser(fin);

	YAML::Node doc;
	parser.GetNextDocument(doc);

	doc["name"] >> Hostname;
	doc["port"] >> Port;
	doc["players"] >> MaxPlayers;

	const YAML::Node& resources = doc["resources"];

	for (unsigned i = 0; i < resources.size(); i++) {
		std::string res;;
		resources[i] >> res;
		Resources.push_back(res);
	}
}

CConfig* CConfig::Get()
{
	if (!singleInstance)
		singleInstance = new CConfig();
	return singleInstance;
}


CConfig::~CConfig()
{
}
