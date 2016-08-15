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
		Hash vehHash = Utils::Hash("adder");
		CNetworkVehicle *veh = new CNetworkVehicle(vehHash, 0.f, 0.f, 77.f, 0.f);
		return true;
	}
#if _DEBUG
	if (!command.compare("/debug"))
	{
		TG(CLocalPlayer::Get()->isDebug);
		return true;
	}
	if (!command.compare("/allocate"))
	{
		LPVOID memoryRegion = rage::sysMemAllocator::Get()->allocate(0xC0, 16);
		int64_t ptr = (int64_t)VTasks::Get()->CTaskJumpVault_Create((int64_t)memoryRegion, 0x108);
		log_info << "CTaskJumpVault: 0x" << std::hex << ptr << std::endl;
		CWorld::Get()->CPedPtr->TasksPtr->PrimaryTasks->AssignTask((GTA::CTask*)ptr, GTA::TASK_PRIORITY_HIGH);
		return true;
	}
#endif
	return false;
}