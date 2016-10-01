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

#include "Natives.h"

int CommandProcessor(std::string command)
{
	std::vector<std::string> params = split(command, ' ');
	command = params[0];
	params.erase(params.begin());
	if (!command.compare("/quit") || !command.compare("/q"))
	{
		ExitProcess(EXIT_SUCCESS);
		return true;
	}
	if (!command.compare("/vehicle"))
	{
		if (!params.size())
		{
			CChat::Get()->AddChatMessage("USAGE: /vehicle [modelname]", 0xAAAAAAFF);
			return true;
		}
		command.erase(0, 9);
		Vector3 spos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
		Hash c = GAMEPLAY::GET_HASH_KEY((char*)command.c_str());
		VEHICLE::CREATE_VEHICLE(c,spos.x,spos.x,spos.z,0.0f,true,true);
		return true;
	}
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
		for (GTA::CTask *task = CWorld::Get()->CPedPtr->TasksPtr->PrimaryTasks->GetTask(); task; task = task->SubTask)
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
					for (lastChild = parent; lastChild->SubTask; lastChild = lastChild->SubTask);
					
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