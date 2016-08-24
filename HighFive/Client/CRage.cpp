#include "stdafx.h"

PedFactoryHook* PedFactoryHook::singleInstance = nullptr;
VehicleFactoryHook* VehicleFactoryHook::singleInstance = nullptr;
bool SyncTree::initialized = false;

namespace rageGlobals
{
	void AllowChangeLanguage(bool toggle)
	{
		bool *_addr = hook::value<bool*>(0x293A657);// (bool*)((intptr_t)GetModuleHandle(NULL) + 0x293A657);
		(*_addr) = toggle;
	}
	void SetPlayerColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		(*hook::value<unsigned char *>(0x1ECD18C)) = r;
		(*hook::value<unsigned char *>(0x1ECD18D)) = g;
		(*hook::value<unsigned char *>(0x1ECD18E)) = b;
		(*hook::value<unsigned char *>(0x1ECD18F)) = a;
	}
};

namespace GTA
{
	std::string CTask::GetTree(CTask *task, int n)
	{
		if (!n)
		{
			task = this;
			return VTasks::Get()->GetTaskName(this->GetID()) + GetTree(task->Child, n + 1);
		}
		else
		{
			std::string res("\n");
			if (!task)
				return res;
			for (int i = 0; i < n; ++i)
				res += "-";
			res += " ";
			res += VTasks::Get()->GetTaskName(task->GetID());
			return res + GetTree(task->Child, n + 1);
		}
	}

	
};

GTA::CTask * CTaskTree::FindTask(int64_t taskID)
{
	for (GTA::CTask *task = this->GetTask(); task; task = task->Child)
	{
		if (task->GetID() == taskID)
			return task;
	}
	return nullptr;
}
