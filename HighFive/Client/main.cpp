#include "stdafx.h"

void InitGameScript() {
	srand(GetTickCount());
	RunGameScript();
}

void OnKeyboardMessage(DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow)
{
	if (isUpNow || wasDownBefore)
	{
		if (key == VK_F8 && !CNetworkConnection::Get()->IsConnected()) {
			if (!CNetworkConnection::Get()->Connect(CConfig::Get()->sIP.c_str(), CConfig::Get()->uiPort)) {
				CChat::Get()->AddChatMessage("Can't connect to the server", { 255, 0, 0, 255 });
			}
		}
		if (key == VK_F9) {
			if(!CNetworkConnection::Get()->IsConnected())
				CChat::Get()->AddChatMessage("Not connected");
			else CNetworkConnection::Get()->Disconnect();
		}
		if (key == VK_F5) {
			CLocalPlayer::Get()->GiveWeapon(0x2BE6766B, 9999);
			CLocalPlayer::Get()->GiveWeapon(0x05FC3C11, 9999);
			
		}
		if (key == VK_NUMPAD7)
		{
			for each(CNetworkPlayer *tmp in CNetworkPlayer::All())
			{
				tmp->is_active = true;
			}
		}
		if (key == VK_NUMPAD6)
		{
			Hash adder = Utils::Hash("Adder");
			//CNetworkVehicle *veh = new CNetworkVehicle(adder, -3.f, 6.f, 73.f, 0.f);
			VehicleData data;
			data.hashModel = adder;
			data.vecRot = CVector3(0.f, 0.f, 0.f);
			data.vecPos = CVector3(-3.f, 6.f, 73.f);

			RakNet::BitStream bsVehicle;
				bsVehicle.Write((unsigned char)ID_SEND_VEHICLE_DATA);
				bsVehicle.Write(data);

				CNetworkConnection::Get()->client->Send(&bsVehicle, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
				RakNet::BitStream bsOut;
				bsOut.Write((MessageID)ID_VEHICLE_SYNC);
				CNetworkConnection::Get()->client->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
		}
		if (key == VK_NUMPAD5)
		{
			CLocalPlayer::Get()->newModel = GAMEPLAY::GET_HASH_KEY((char*)(models[(GetTickCount() % 30) + 100]));
		}
		if (key == VK_NUMPAD8)
		{
		}
		if (key == VK_F4)
		{

			int(*LoadGameNow)(char);

			//2 bytes from the first byte, starting from 0
			char* func = Memory::Find("33 C9 E8 ? ? ? ? 8B 0D ? ? ? ? 48 8B 5C 24 ? 8D 41 FC 83 F8 01 0F 47 CF 89 0D ? ? ? ?")->get<char>(2);
			Memory::set_call(&LoadGameNow, func);

			//Usage:
			LoadGameNow(0);
			/*intptr_t baseAddress = (intptr_t)GetModuleHandle(NULL);
			intptr_t worldPtr = baseAddress + 0x228FA58;*/
			/*int(*LoadGameNow)(char);
			char* func = Memory::Find("33 C9 E8 ? ? ? ? 8B 0D ? ? ? ? 48 8B 5C 24 ? 8D 41 FC 83 F8 01 0F 47 CF 89 0D ? ? ? ?")->get<char>(2);
			Memory::set_call(&LoadGameNow, func);
			LoadGameNow(0);*/


			/*
			//Disable game saving
			char* location = hook::pattern("8B 49 10 85 C9 74 1B").count(1).get(0).get<char>(5);
			hook::nop(location, 2);
			char* location2 = hook::pattern("FF C9 0F 85 ? ? ? ? B1 01 E8 ? ? ? ? 85 C0 75 6C").count(1).get(0).get<char>(2);
			void* jmpAddress = hook::pattern("F7 43 ? ? ? ? ? 74 04 32 C0 EB 34 48 8D 0D ? ? ? ? E8 ? ? ? ?").count(1).get(0).get<void>(0);
			hook::jump(location2, jmpAddress);
*/
		}
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
	/*for (;;)
	{
		WAIT(0);
	}*/
}

void LocalTick()
{
	for (;;)
	{
		CLocalPlayer::Get()->Tick();
		if (CNetworkConnection::Get()->IsConnected()) {
			if (CNetworkConnection::Get()->IsConnectionEstablished())
				CLocalPlayer::Get()->SendOnFootData();
		}
		WAIT(0);
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
