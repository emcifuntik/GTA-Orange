#include "stdafx.h"
using namespace tinyxml2;

int main(void)
{
	/*XmlDomDocument xmlReader("config.xml");
	tinyxml2::XMLElement* serverNameXML = xmlReader.FirstChildElement("config")->FirstChildElement("servername");*/

	log << "Starting the server..." << std::endl;
	log << "Hostname: " << color::lred << CConfig::Get()->Hostname << std::endl;
	log << "Port: " << color::lred << CConfig::Get()->Port << std::endl;
	log << "Maximum players: " << color::lred << CConfig::Get()->MaxPlayers << std::endl;

	// Register squirrel functions
	RegisterScriptFunctions();
	// Loading squrrel scripts
	for each (std::string scriptName in CConfig::Get()->Scripts)
	{
		Squirrel *script = new Squirrel((std::string("scripts/") + scriptName).c_str());
		if (script->IsReady())
			log << "Script " << color::green << scriptName << color::white << " loaded" << std::endl;
		else
			log << "Script " << color::red << scriptName << color::white << " not loaded" << std::endl;
	}

	auto netLoop = [=]() 
	{
		CNetworkConnection::Get()->Start(CConfig::Get()->MaxPlayers, CConfig::Get()->Port);
		CRPCPlugin::Get();
		DWORD lastTick = 0;
		RakNet::RakNetStatistics stat;
		for (;;)
		{
			RakSleep(5);
			CNetworkConnection::Get()->Tick();
			CNetworkPlayer::Tick();
			
			if ((GetTickCount() - lastTick) > 100)
			{
				CNetworkConnection::Get()->server->GetStatistics(0, &stat);
				std::stringstream ss;
				ss << CConfig::Get()->Hostname << ". Players online: " << CNetworkPlayer::Count() << ", " 
					<< "Packet loss: " << std::setprecision(2) << std::fixed << stat.packetlossTotal*100 << "%";
				SetConsoleTitle(ss.str().c_str());
				lastTick = GetTickCount();
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