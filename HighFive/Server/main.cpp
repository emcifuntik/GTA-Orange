#include "stdafx.h"
using namespace tinyxml2;

int main(void)
{
	log << "Starting the server..." << std::endl;
	log << "Hostname: " << color::lred << CConfig::Get()->Hostname << std::endl;
	log << "Port: " << color::lred << CConfig::Get()->Port << std::endl;
	log << "Maximum players: " << color::lred << CConfig::Get()->MaxPlayers << std::endl;
	
	for each (std::string scriptName in CConfig::Get()->Scripts)
	{
		if (Python::Get()->Connect(scriptName.c_str()))
		{
			log << "Script " << color::green << scriptName << color::white << " loaded" << std::endl;
			Python::Get()->pCallFunc("onScriptInit", NULL);
		}
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
					<< "Packet loss: " << std::setprecision(2) << std::fixed << stat.packetlossTotal * 100 << "%";
				SetConsoleTitle(ss.str().c_str());
				lastTick = GetTickCount();
			}
		}
	};
	std::thread netThread(netLoop);
	netThread.detach();

	for (;;)
	{
		std::string msg;
		std::getline(std::cin, msg);
		if (!msg.compare("exit") || !msg.compare("kill"))
		{
			log << "Terminating server..." << std::endl;
			break;
		}
		else
		{
			CPyArgBuilder args;
			args << msg;
			Python::Get()->pCallFunc("OnServerCommand", args());
		}
	}
	netThread.~thread();
	delete Python::Get();
	return 0;
}