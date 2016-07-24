#include "stdafx.h"
using namespace tinyxml2;

int main(void)
{
	/*XmlDomDocument xmlReader("config.xml");
	tinyxml2::XMLElement* serverNameXML = xmlReader.FirstChildElement("config")->FirstChildElement("servername");*/

	XMLDocument doc;
	doc.LoadFile("config.xml");
	tinyxml2::XMLElement * root = doc.FirstChildElement("config");
	tinyxml2::XMLElement * serverNode = root->FirstChildElement("server");
	unsigned short port = serverNode->IntAttribute("port");
	unsigned short maxPlayers = serverNode->IntAttribute("maxplayers");

	std::cout << CConsole::Get()->Color(FOREGROUND_GREEN | FOREGROUND_INTENSITY) << "Starting the server..." << std::endl;
	std::cout << CConsole::Get()->Color(FOREGROUND_BLUE | FOREGROUND_INTENSITY) << "Hostname: ";
	std::cout << CConsole::Get()->Color(FOREGROUND_RED | FOREGROUND_INTENSITY) << serverNode->GetText() << std::endl;
	std::cout << CConsole::Get()->Color(FOREGROUND_BLUE | FOREGROUND_INTENSITY) << "Port: ";
	std::cout << CConsole::Get()->Color(FOREGROUND_RED | FOREGROUND_INTENSITY) << port << std::endl;
	std::cout << CConsole::Get()->Color(FOREGROUND_BLUE | FOREGROUND_INTENSITY) << "Maximum players: ";
	std::cout << CConsole::Get()->Color(FOREGROUND_RED | FOREGROUND_INTENSITY) << maxPlayers << std::endl;
	CConsole::Get()->Color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	auto netLoop = [=]() 
	{
		CNetworkConnection::Get()->Start(maxPlayers, port);
		for (;;)
		{
			RakSleep(15);
			CNetworkConnection::Get()->Tick();
			CNetworkPlayer::Tick();

			if (!(GetTickCount() % 1000))
			{
				std::stringstream ss;
				ss << serverNode->GetText() << ". Players online: " << CNetworkPlayer::Count();
				SetConsoleTitle(ss.str().c_str());
			}
		}
	};
	std::thread netThread(netLoop);
	netThread.detach();
	for (;;)
	{
		char *message = new char[256];
		std::cin.read(message, 256);

		delete message;
	}
	return 0;
}