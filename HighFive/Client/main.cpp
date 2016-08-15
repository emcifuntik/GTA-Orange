#include "stdafx.h"

void InitGameScript() {
	srand(GetTickCount());
	RunGameScript();
}

void OnKeyboardMessage(DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow)
{
	if (isUpNow || wasDownBefore)
	{
		if (key == VK_F8) {
			if (CNetworkConnection::Get()->IsConnected())
				CNetworkConnection::Get()->Disconnect();
		}
		if (key == VK_F9) {
			if(CNetworkConnection::Get()->IsConnected())
				CNetworkConnection::Get()->Disconnect();
			if (!CNetworkConnection::Get()->Connect(CConfig::Get()->sIP.c_str(), CConfig::Get()->uiPort)) {
				CChat::Get()->AddChatMessage("Can't connect to the server", { 255, 0, 0, 255 });
			}
		}
		if (key == VK_F5) {
			CLocalPlayer::Get()->GiveWeapon(0x2BE6766B, 9999);
			CLocalPlayer::Get()->GiveWeapon(0x05FC3C11, 9999);
			CLocalPlayer::Get()->GiveWeapon(0x3656C8C1, 9999);
			CLocalPlayer::Get()->GiveWeapon(0xFDBC8A50, 9999);
			CLocalPlayer::Get()->GiveWeapon(0x0C472FE2, 9999);
			CLocalPlayer::Get()->GiveWeapon(0x33058E22, 9999);
			CLocalPlayer::Get()->GiveWeapon(0xA284510B, 9999);
			CLocalPlayer::Get()->GiveWeapon(0xB1CA77B1, 9999);
			CLocalPlayer::Get()->GiveWeapon(0x42BF8A85, 9999);
			CLocalPlayer::Get()->GiveWeapon(0xD04C944D, 9999);
		}
		if (key == VK_NUMPAD5)
		{
			CLocalPlayer::Get()->newModel = GAMEPLAY::GET_HASH_KEY((char*)(models[(GetTickCount() % 30) + 100]));
		}
		if (key == VK_NUMPAD8)
		{
			CVector3 pos = CLocalPlayer::Get()->GetPosition();
			pos.fZ += 10.f;
			CLocalPlayer::Get()->SetPosition(pos);
		}
		/*if (key == VK_NUMPAD1)
		{
			CWorld::Get()->CPedPtr->CPedWeaponManagerPtr->CWeaponPtr->CWeaponMethods->func_1 = [](__int64 a1, char a2)
			{
				std::stringstream ss;
				ss << "Called func_1(" << a1 << ", " << a2 << ");";
				CChat::Get()->AddChatMessage(ss.str())
				__int64 result = 0;
				return result;
			};
		}
		if (key == VK_NUMPAD2)
		{
			CWorld::Get()->CPedPtr->CPedWeaponManagerPtr->CWeaponPtr->CWeaponMethods->func_2 = [](__int64 a1, char *a2, __int64 a3)
			{
				std::stringstream ss;
				ss << "Called func_2(" << a1 << ", " << a2 << ", " << a3 << ");";
				MessageBoxA(NULL, ss.str().c_str(), "Function hooking", MB_OK);
				char result = 0;
				return result;
			};
		}*/
		/*if (key == VK_NUMPAD3)
		{
			CWorld::Get()->CPedPtr->CPedWeaponManagerPtr->CPedWeaponManagerMethods->func_3 = [](__int64 a1, int a2, __int64 a3)
			{
				std::stringstream ss;
				ss << "Called func_3(" << a1 << ", " << a2 << ", " << a3 << ");";
				MessageBoxA(NULL, ss.str().c_str(), "Function hooking", MB_OK);
				int result = 0;
				return result;
			};
		}
		if (key == VK_NUMPAD4)
		{
			CWorld::Get()->CPedPtr->CPedWeaponManagerPtr->CPedWeaponManagerMethods->func_4 = [](__int64 a1)
			{
				std::stringstream ss;
				ss << "Called func_4(" << a1 << ");";
				MessageBoxA(NULL, ss.str().c_str(), "Function hooking", MB_OK);
				int result = 0;
				return result;
			};
		}*/
	}
}

void ChatRendering()
{
	CChat::Get()->RegisterCommandProcessor(CommandProcessor);
	for (;;)
	{
		CChat::Get()->Render();
		CChat::Get()->Input();
		WAIT(0);
	}
}

void NetworkTick()
{
	TRACE("Trace test");
	// Hook ped create
	PedFactoryHook::Get()->CreateHook = CWorld::Get()->CPedFactoryPtr->Create;
	CWorld::Get()->CPedFactoryPtr->Create = &hookCreatePed;

	// Hook vehicle create
	VehicleFactoryHook::Get()->CreateHook = CVehicleFactory::Get()->Create;
	CVehicleFactory::Get()->Create = &hookCreateVehicle;

	static auto _replayFunc1 = ReplayInterfaces::Get()->ReplayInterfacePed->virtualFunctions->Function1;
	ReplayInterfaces::Get()->ReplayInterfacePed->virtualFunctions->Function1 = [](int64_t a1, char a2)
	{
		auto ret = _replayFunc1(a1, a2);
		log_debug << "ReplayFunc1, 0x" << std::hex << a1 << ", " << (int)a2 << std::endl;
		return ret;
	};


	//CTaskTreeFunctions::Get()->func_1 = [](int64_t a1, int32_t a2) {
	//	std::stringstream ss;
	//	ss << "func_1(0x" << std::hex << a1 << ", " << a2 << ");";
	//	CChat::Get()->AddChatMessage(ss.str());
	//	return (__int64)nullptr;
	//};

	/*static auto oldFunction_3 = CTaskTreeFunctions::Get()->func_3;
	CTaskTreeFunctions::Get()->func_3 = [](int64_t ptr1, int64_t ptr2, int a3) {
		std::stringstream ss;
		ss << "func_3(0x" << std::hex << ptr1 << ", " << ptr2 << ", " << a3 << ");";
		CChat::Get()->AddChatMessage(ss.str());
		return oldFunction_3(ptr1, ptr2, a3);
	};

	static auto oldFunction_5 = CTaskTreeFunctions::Get()->func_5;
	CTaskTreeFunctions::Get()->func_5 = [](int64_t ptr1, int64_t ptr2, float a3) {
		std::stringstream ss;
		ss << "func_5(0x" << std::hex << ptr1 << ", " << ptr2 << ", " << std::dec << (int)a3 << ");";
		CChat::Get()->AddChatMessage(ss.str());
		return oldFunction_5(ptr1, ptr2, a3);
	};*/

	/*
	static auto oldFunctionMove_1 = CWorld::Get()->CPedPtr->TasksPtr->CTaskTreeMovementPtr->CTaskTreeMovementMethods->func_1;
	CWorld::Get()->CPedPtr->TasksPtr->CTaskTreeMovementPtr->CTaskTreeMovementMethods->func_1 = [](int64_t* a1, int32_t a2) {
		std::stringstream ss;
		ss << "func_1(0x" << std::hex << a1 << ", " << a2 << ");";
		CChat::Get()->AddChatMessage(ss.str());
		return oldFunctionMove_1(a1, a2);
	};

	static auto oldFunctionMove_2 = CWorld::Get()->CPedPtr->TasksPtr->CTaskTreeMovementPtr->CTaskTreeMovementMethods->func_2;
	CWorld::Get()->CPedPtr->TasksPtr->CTaskTreeMovementPtr->CTaskTreeMovementMethods->func_2 = [](int64_t a1) {
		std::stringstream ss;
		ss << "func_2(0x" << std::hex << a1 << ");";
		CChat::Get()->AddChatMessage(ss.str());
		return oldFunctionMove_2(a1);
	};

	static auto oldFunctionMove_3 = CWorld::Get()->CPedPtr->TasksPtr->CTaskTreeMovementPtr->CTaskTreeMovementMethods->func_3;
	CWorld::Get()->CPedPtr->TasksPtr->CTaskTreeMovementPtr->CTaskTreeMovementMethods->func_3 = [](int64_t* a1, int64_t a2, int32_t a3) {
		std::stringstream ss;
		ss << "func_3(0x" << std::hex << a1 << ", " << a2 << ", " << a3 << ");";
		CChat::Get()->AddChatMessage(ss.str());
		return oldFunctionMove_3(a1, a2, a3);
	};

	static auto oldFunctionMove_4 = CWorld::Get()->CPedPtr->TasksPtr->CTaskTreeMovementPtr->CTaskTreeMovementMethods->func_4;
	CWorld::Get()->CPedPtr->TasksPtr->CTaskTreeMovementPtr->CTaskTreeMovementMethods->func_4 = [](int64_t a1, signed char a2, uint32_t a3) {
		std::stringstream ss;
		ss << "func_4(0x" << std::hex << a1 << ", " << std::dec << (int)a2 << ", " << std::hex << a3 << ");";
		CChat::Get()->AddChatMessage(ss.str());
		return oldFunctionMove_4(a1, a2, a3);
	};

	static auto oldFunctionMove_5 = CWorld::Get()->CPedPtr->TasksPtr->CTaskTreeMovementPtr->CTaskTreeMovementMethods->func_5;
	CWorld::Get()->CPedPtr->TasksPtr->CTaskTreeMovementPtr->CTaskTreeMovementMethods->func_5 = [](int64_t a1, int64_t a2, float a3) {
		std::stringstream ss;
		ss << "func_5(0x" << std::hex << a1 << ", " << a2 << ", " << std::dec << a3 << ");";
		CChat::Get()->AddChatMessage(ss.str());
		return oldFunctionMove_5(a1, a2, a3);
	};

	static auto oldFunctionMove_9 = CWorld::Get()->CPedPtr->TasksPtr->CTaskTreeMovementPtr->CTaskTreeMovementMethods->func_9;
	CWorld::Get()->CPedPtr->TasksPtr->CTaskTreeMovementPtr->CTaskTreeMovementMethods->func_9 = [](int64_t a1, int64_t a2, unsigned int a3, char a4) {
		std::stringstream ss;
		ss << "func_9(0x" << std::hex << a1 << ", " << a2 << ", " << std::dec << a3 << ", " << (int)a4 << ");";
		CChat::Get()->AddChatMessage(ss.str());
		return oldFunctionMove_9(a1, a2, a3, a4);
	};*/
}

void LocalTick()
{
	for (;;)
	{
		CLocalPlayer::Get()->Tick();
		if (CNetworkConnection::Get()->IsConnected()) {
			if (CNetworkConnection::Get()->IsConnectionEstablished())
				if(!CLocalPlayer::Get()->IsFalling())
					CLocalPlayer::Get()->SendOnFootData();
		}
		WAIT(0);
		#pragma region Debug stuff
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
				int primaryActive = ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->TasksPtr->PrimaryTasks->ActiveTask;
				if (primaryActive > -1)
				{
					std::stringstream ss2;
					GTA::CTask *primaryTask = ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->TasksPtr->PrimaryTasks->TasksArray[primaryActive];
					ss2 << "Primary task: " << primaryTask->GetTree() << std::endl;
					CGraphics::Get()->Draw3DText(ss2.str(), 0.3f, ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Position.fX,
						ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Position.fY,
						ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Position.fZ + 1.0f, { 255, 255, 255, 255 });
				}
				int secondaryActive = ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->TasksPtr->SecondaryTasks->ActiveTask;
				if (secondaryActive > -1)
				{
					std::stringstream ss2;
					GTA::CTask *secondaryTask = ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->TasksPtr->SecondaryTasks->TasksArray[secondaryActive];
					ss2 << "Secondary task: " << secondaryTask->GetTree() << std::endl;
					CGraphics::Get()->Draw3DText(ss2.str(), 0.3f, ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Position.fX,
						ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Position.fY,
						ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Position.fZ + 0.5f, { 255, 255, 255, 255 });
				}
				int movementActive = ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->TasksPtr->MovementTasks->ActiveTask;
				if (movementActive > -1)
				{
					std::stringstream ss2;
					GTA::CTask *movementTask = ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->TasksPtr->MovementTasks->TasksArray[movementActive];
					ss2 << "Movement task: " << movementTask->GetTree() << std::endl;
					CGraphics::Get()->Draw3DText(ss2.str(), 0.3f, ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Position.fX,
						ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Position.fY,
						ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->Position.fZ, { 255, 255, 255, 255 });
				}
				int motionActive = ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->TasksPtr->MotionTasks->ActiveTask;
				if (motionActive > -1)
				{
					std::stringstream ss2;
					GTA::CTask *motionTask = ReplayInterfaces::Get()->ReplayInterfacePed->pool[i]->TasksPtr->MotionTasks->TasksArray[motionActive];
					ss2 << "Motion task: " << motionTask->GetTree() << std::endl;
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
		#pragma endregion
	}
}

void RunGameScript() {
	for(;;)
	{
		if (CNetworkConnection::Get()->IsConnected()) {
			CNetworkConnection::Get()->Tick();
			CNetworkPlayer::Tick();
		}
		WAIT(10);
	}
}
