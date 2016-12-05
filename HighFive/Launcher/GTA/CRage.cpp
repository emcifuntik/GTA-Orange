#include "stdafx.h"

PedFactoryHook* PedFactoryHook::singleInstance = nullptr;
VehicleFactoryHook* VehicleFactoryHook::singleInstance = nullptr;
bool SyncTree::initialized = false;
GetSyncTree_ SyncTree::GetSyncTree;

namespace rageGlobals
{
	void SetPlayerColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		unsigned char * colorAddress = (unsigned char *)((ULONGLONG)CMemory::Find("8B 0D ? ? ? ? 44 8B 4C DE 04 81 C9 00 00 00 FF").getOffset(2) + 4);
		for (int i = 0; i < 4; ++i)
		{
			(*colorAddress++) = b;
			(*colorAddress++) = g;
			(*colorAddress++) = r;
			(*colorAddress++) = a;
		}
	}
};

namespace GTA
{
	std::string CTask::GetTree(CTask *task, int n)
	{
		if (!n)
		{
			task = this;
			return VTasks::Get()->GetTaskName(this->GetID()) + GetTree(task->SubTask, n + 1);
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
			return res + GetTree(task->SubTask, n + 1);
		}
	}

	
};

GTA::CTask * CTaskTree::GetTaskByID(unsigned int taskID)
{
	for (GTA::CTask *task = GetTask(); task; task = task->SubTask)
		if (task->GetID() == taskID)
			return task;
	return nullptr;
}

CPed * CPed::GetFromScriptID(int Handle)
{
	typedef CPed*(*GetCEntity)(int);
	return (CPed*)((GetCEntity)CMemory::Find("40 53 48 83 EC 20 E8 ? ? ? ? 48 8B D8 48 85 C0 74 19 4C 8B 00 8B 15 ? ? ? ? 48 8B C8 41 FF 50 08 84 C0 74 05 48 8B C"
		"3 EB 02 33 C0 48 83 C4 20 5B C3 48 89 5C 24 ? 45 33 C9")())(Handle);
}
