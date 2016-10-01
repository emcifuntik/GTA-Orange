#include "stdafx.h"

CConfig *CConfig::singleInstance = nullptr;

CConfig::CConfig()
{
	doc.LoadFile("config.xml");
	tinyxml2::XMLElement * root = doc.FirstChildElement("config");
	tinyxml2::XMLElement * serverNode = root->FirstChildElement("server");
	uiPort = serverNode->IntAttribute("port");
	sIP = std::string(serverNode->GetText());
	sNickName = std::string(root->FirstChildElement("player")->GetText());
}


CConfig::~CConfig()
{
}
