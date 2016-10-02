#include "stdafx.h"

CConfig *CConfig::singleInstance = nullptr;

CConfig::CConfig()
{
	doc.LoadFile((CGlobals::Get().highFivePath + "\\config.xml").c_str());
	if (doc.Error())
	{
		uiPort = 7788;
		sIP = "";
		sNickName = std::string("Player");
		CGlobals::Get().serverPort = uiPort;
		strcpy_s(CGlobals::Get().serverIP, 32, sIP.c_str());
		strcpy_s(CGlobals::Get().nickName, 32, sNickName.c_str());
		Save();
	}
	else
	{
		tinyxml2::XMLElement * root = doc.FirstChildElement("config");
		tinyxml2::XMLElement * serverNode = root->FirstChildElement("server");
		uiPort = serverNode->IntAttribute("port");
		sIP = std::string(serverNode->GetText());
		sNickName = std::string(root->FirstChildElement("player")->GetText());
		CGlobals::Get().serverPort = uiPort;
		strcpy_s(CGlobals::Get().serverIP, 32, sIP.c_str());
		strcpy_s(CGlobals::Get().nickName, 32, sNickName.c_str());
	}
}


void CConfig::Save()
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode * pRoot = doc.NewElement("config");
	doc.InsertFirstChild(pRoot);

	tinyxml2::XMLElement * pServer = doc.NewElement("server");
	pServer->SetText(sIP.c_str());
	pServer->SetAttribute("port", (int64_t)uiPort);
	pRoot->InsertEndChild(pServer);

	tinyxml2::XMLElement * pPlayer = doc.NewElement("player");
	pPlayer->SetText(sNickName.c_str());
	pRoot->InsertEndChild(pPlayer);

	tinyxml2::XMLError eResult = doc.SaveFile((CGlobals::Get().highFivePath + "\\config.xml").c_str());
	if (eResult != tinyxml2::XMLError::XML_SUCCESS)
		throw std::exception("TinyXML Error");
}

CConfig::~CConfig()
{
}
