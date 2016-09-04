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
#if _DEBUG
	if (!command.compare("/model"))
	{
		if (!params.size())
		{
			CChat::Get()->AddChatMessage("USAGE: /model [model id]", 0xAAAAAAFF);
			return true;
		}
		CLocalPlayer::Get()->newModel = GAMEPLAY::GET_HASH_KEY((char*)(models[std::atoi(params[0].c_str())]));
		return true;
	}
	if (!command.compare("/anim"))
	{
		if (!params.size())
		{
			CChat::Get()->AddChatMessage("USAGE: /anim [ped id]", 0xAAAAAAFF);
			return true;
		}
		int handler = std::atoi(params[0].c_str());
		int setToPed = std::atoi(params[1].c_str());
		auto pool = &ReplayInterfaces::Get()->ReplayInterfacePed->pool;
		int pedID = -1;
		for (int i = 0; i < pool->Capacity(); ++i)
		{
			if (pool->GetHandle(i) == handler)
			{
				pedID = i;
				break;
			}
		}
		if (pedID == -1)
		{
			CChat::Get()->AddChatMessage("ERROR: Ped with this id not found", 0xFFAAAAFF);
			return true;
		}
		CPed *ped = (*pool)[pedID];
		GTA::CTask *parent = nullptr;
		for (GTA::CTask *task = CWorld::Get()->CPedPtr->TasksPtr->PrimaryTasks->GetTask(); task; task = task->Child)
		{
			if (!task->IsSerializable())
				continue;
			auto ptr = task->Serialize();
			if (ptr)
			{
				//log_debug << "Size: " << ptr->Size() << std::endl;
				auto nextTask = (GTA::CTask*) ptr->GetTask();
				nextTask->Deserialize(ptr);
				if (!parent)
				{
					log_debug << "0x" << std::hex << nextTask << std::endl;
					if (setToPed)
						ped->TasksPtr->PrimaryTasks->AssignTask(nextTask, GTA::TASK_PRIORITY_HIGH);
					parent = nextTask;
				}
				else
				{
					GTA::CTask *lastChild;
					for (lastChild = parent; lastChild->Child; lastChild = lastChild->Child);
					
				}
				rage::sysMemAllocator::Get()->free(ptr, rage::HEAP_TASK_CLONE);
			}
			break;
		}
		return true;
	}
	if (!command.compare("/debug"))
	{
		TG(CLocalPlayer::Get()->isDebug);
		return true;
	}
#endif
	return false;
}