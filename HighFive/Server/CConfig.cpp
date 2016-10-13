#include "stdafx.h"

CConfig* CConfig::singleInstance = nullptr;


CConfig::CConfig()
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("config.xml");
	tinyxml2::XMLElement * root = doc.FirstChildElement("config");
	tinyxml2::XMLElement * serverNode = root->FirstChildElement("server");
	Hostname = serverNode->GetText();
	Port = serverNode->IntAttribute("port");
	MaxPlayers = serverNode->IntAttribute("maxplayers");

	tinyxml2::XMLElement * resources = root->FirstChildElement("resources");
	for (tinyxml2::XMLElement* child = resources->FirstChildElement("resource"); child != NULL; child = child->NextSiblingElement())
	{
		Resources.push_back(child->GetText());
	}

	tinyxml2::XMLElement * logtimeformat = root->FirstChildElement("logtime");
	LogTimeFormat = logtimeformat->GetText();
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
