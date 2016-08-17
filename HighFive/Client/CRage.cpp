#include "stdafx.h"

PedFactoryHook* PedFactoryHook::singleInstance = nullptr;
VehicleFactoryHook* VehicleFactoryHook::singleInstance = nullptr;


namespace rageGlobals
{
	void AllowChangeLanguage(bool toggle)
	{
		bool *_addr = (bool*)((intptr_t)GetModuleHandle(NULL) + 0x293A657);
		(*_addr) = toggle;
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