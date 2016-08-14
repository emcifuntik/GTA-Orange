#include "stdafx.h"

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

int CommandProcessor(std::string command)
{
	std::vector<std::string> params = split(command, ' ');
	command = params[0];
	params.erase(params.begin());
	if (!command.compare("/model"))
	{
		CLocalPlayer::Get()->newModel = GAMEPLAY::GET_HASH_KEY((char*)(models[std::atoi(params[0].c_str())]));
		return true;
	}
	if (!command.compare("/vehicle"))
	{
		Hash vehHash = GAMEPLAY::GET_HASH_KEY("adder");
		CNetworkVehicle *veh = new CNetworkVehicle(vehHash, 0.f, 0.f, 77.f, 0.f);
		return true;
	}
#if _DEBUG
	if (!command.compare("/debug"))
	{
		TG(CLocalPlayer::Get()->isDebug);
		return true;
	}
#endif
	return false;
}