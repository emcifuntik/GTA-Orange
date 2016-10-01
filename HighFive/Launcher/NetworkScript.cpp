#include "stdafx.h"
#include "Natives.h"

ULONGLONG lastSendTick = 0;

void NetworkAction()
{
	for (;;)
	{
		CLocalPlayer::Get()->Tick();
		if (CNetworkConnection::Get()->IsConnected()) {
			if (CNetworkConnection::Get()->IsConnectionEstablished())
			{
				CLocalPlayer::Get()->SendOnFootData();
				if (CLocalPlayer::Get()->updateTasks)
				{
					CLocalPlayer::Get()->updateTasks ^= 1;
					//CLocalPlayer::Get()->SendTasks();
				}
			}
		}
		if ((GetTickCount64() + 10) >= lastSendTick)
		{
			if (CNetworkConnection::Get()->IsConnected()) {
				CNetworkConnection::Get()->Tick();
				CNetworkPlayer::Tick();
			}
		}
#if _DEBUG
		if (CLocalPlayer::Get()->isDebug)
		{
			std::stringstream ss;
			ss << "Peds pool: " << ReplayInterfaces::Get()->ReplayInterfacePed->pool.Count() << " / " << ReplayInterfaces::Get()->ReplayInterfacePed->pool.Capacity() << std::endl <<
				"Vehicles pool: " << ReplayInterfaces::Get()->ReplayInterfaceVeh->pool.Count() << " / " << ReplayInterfaces::Get()->ReplayInterfaceVeh->pool.Capacity() << std::endl <<
				"Objects pool: " << ReplayInterfaces::Get()->ReplayInterfaceObject->pool.Count() << " / " << ReplayInterfaces::Get()->ReplayInterfaceObject->pool.Capacity();
			CUI::PrintText(ss.str(), 0.23f, 0.85f, 0x21, 0x96, 0xF3, 0xFF, 0.3f);

			for (int i = 0, cnt = 0; i < ReplayInterfaces::Get()->ReplayInterfacePed->pool.Capacity(); ++i)
			{
				if (ReplayInterfaces::Get()->ReplayInterfacePed->pool.GetHandle(i) == -1)
					continue;
				if ((ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Position - CWorld::Get()->CPedPtr->Position).Length() > 50.f)
					continue;
				cnt++;
				ss = std::stringstream();
				ss << "Handle: " << ReplayInterfaces::Get()->ReplayInterfacePed->pool.GetHandle(i) << std::endl;
				CGraphics::Get()->Draw3DText(ss.str(), 0.3f, ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Position.fX,
					ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Position.fY,
					ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Position.fZ + 1.2f, { 255, 255, 255, 255 });
				int primaryActive = ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->TasksPtr->PrimaryTasks->ActiveTask;
				if (primaryActive > -1)
				{
					std::stringstream ss2;
					GTA::CTask *primaryTask = ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->TasksPtr->PrimaryTasks->TasksArray[primaryActive];
					ss2 << "P: " << primaryTask->GetTree() << std::endl;
					CGraphics::Get()->Draw3DText(ss2.str(), 0.3f, ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Position.fX,
						ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Position.fY,
						ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Position.fZ + 1.0f, { 255, 255, 255, 255 });
				}
				int secondaryActive = ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->TasksPtr->SecondaryTasks->ActiveTask;
				if (secondaryActive > -1)
				{
					std::stringstream ss2;
					GTA::CTask *secondaryTask = ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->TasksPtr->SecondaryTasks->TasksArray[secondaryActive];
					ss2 << "S: " << secondaryTask->GetTree() << std::endl;
					CGraphics::Get()->Draw3DText(ss2.str(), 0.3f, ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Position.fX,
						ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Position.fY,
						ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Position.fZ + 0.5f, { 255, 255, 255, 255 });
				}
				int movementActive = ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->TasksPtr->MovementTasks->ActiveTask;
				if (movementActive > -1)
				{
					std::stringstream ss2;
					GTA::CTask *movementTask = ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->TasksPtr->MovementTasks->TasksArray[movementActive];
					ss2 << "M: " << movementTask->GetTree() << std::endl;
					CGraphics::Get()->Draw3DText(ss2.str(), 0.3f, ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Position.fX,
						ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Position.fY,
						ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Position.fZ, { 255, 255, 255, 255 });
				}
				int motionActive = ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->TasksPtr->MotionTasks->ActiveTask;
				if (motionActive > -1)
				{
					std::stringstream ss2;
					GTA::CTask *motionTask = ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->TasksPtr->MotionTasks->TasksArray[motionActive];
					ss2 << "MN: " << motionTask->GetTree() << std::endl;
					CGraphics::Get()->Draw3DText(ss2.str(), 0.3f, ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Position.fX,
						ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Position.fY,
						ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Position.fZ - 0.5f, { 255, 255, 255, 255 });
				}
				/*ss << "Handle: " << ReplayInterfaces::Get()->ReplayInterfacePed->pool.GetHandle(i) << std::endl <<
				"Position: " << ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Position.ToString() << std::endl <<
				"Health: " << ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Health << std::endl <<
				"Model: 0x" << std::hex << ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->PedModelInfo->ModelHash << std::endl <<
				ss2.str();*/


				if (cnt >= ReplayInterfaces::Get()->ReplayInterfacePed->pool.Count())
					break;
			}

			/*for (int i = 0, cnt = 0; i < ReplayInterfaces::Get()->ReplayInterfaceVeh->pool.Capacity(); ++i)
			{
			if (ReplayInterfaces::Get()->ReplayInterfaceVeh->pool.GetHandle(i) == -1)
			continue;
			if ((ReplayInterfaces::Get()->ReplayInterfaceVeh->pool[i]->Position - CWorld::Get()->CPedPtr->Position).Length() > 50.f)
			continue;
			cnt++;
			ss = std::stringstream();
			ss << "Handle: " << ReplayInterfaces::Get()->ReplayInterfaceVeh->pool.GetHandle(i) << std::endl <<
			"Position: " << ReplayInterfaces::Get()->ReplayInterfaceVeh->pool[i]->Position.ToString() << std::endl <<
			"Model: 0x" << std::hex << ReplayInterfaces::Get()->ReplayInterfaceVeh->pool[i]->VehicleModelInfo->ModelHash;
			CGraphics::Get()->Draw3DText(ss.str(), 0.3f, ReplayInterfaces::Get()->ReplayInterfaceVeh->pool[i]->Position.fX,
			ReplayInterfaces::Get()->ReplayInterfaceVeh->pool[i]->Position.fY,
			ReplayInterfaces::Get()->ReplayInterfaceVeh->pool[i]->Position.fZ, { 255, 255, 255, 255 });
			if (cnt >= ReplayInterfaces::Get()->ReplayInterfaceVeh->pool.Count())
			break;
			}

			for (int i = 0, cnt = 0; i < ReplayInterfaces::Get()->ReplayInterfaceObject->pool.Capacity(); ++i)
			{
			if (ReplayInterfaces::Get()->ReplayInterfaceObject->pool.GetHandle(i) == -1)
			continue;
			if ((ReplayInterfaces::Get()->ReplayInterfaceObject->pool[i]->Position - CWorld::Get()->CPedPtr->Position).Length() > 50.f)
			continue;
			cnt++;
			ss = std::stringstream();
			ss << "Handle: " << ReplayInterfaces::Get()->ReplayInterfaceObject->pool.GetHandle(i) << std::endl <<
			"Position: " << ReplayInterfaces::Get()->ReplayInterfaceObject->pool[i]->Position.ToString() << std::endl <<
			"Model: 0x" << std::hex << ReplayInterfaces::Get()->ReplayInterfaceObject->pool[i]->ModelInfo->ModelHash;
			CGraphics::Get()->Draw3DText(ss.str(), 0.3f, ReplayInterfaces::Get()->ReplayInterfaceObject->pool[i]->Position.fX,
			ReplayInterfaces::Get()->ReplayInterfaceObject->pool[i]->Position.fY,
			ReplayInterfaces::Get()->ReplayInterfaceObject->pool[i]->Position.fZ, { 255, 255, 255, 255 });
			if (cnt >= ReplayInterfaces::Get()->ReplayInterfaceObject->pool.Count())
			break;
			}*/
		}
#endif
		scriptWait(0);
	}
}

SCRIPT("networkScript", NetworkAction, networkAction);