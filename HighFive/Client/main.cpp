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
			if (!CNetworkConnection::Get()->Connect("25.69.172.216", 7788)) {
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
		if (key == VK_NUMPAD5)
		{
			CLocalPlayer::Get()->newModel = GAMEPLAY::GET_HASH_KEY((char*)(models[(GetTickCount() % 30) + 100]));
		}
		if (key == VK_NUMPAD8)
		{
			CLocalPlayer::Get()->offsetY += CLocalPlayer::Get()->alpha;
		}
		if (key == VK_NUMPAD2)
		{
			CLocalPlayer::Get()->offsetY -= CLocalPlayer::Get()->alpha;
		}
		if (key == VK_NUMPAD6)
		{
			CLocalPlayer::Get()->offsetX += CLocalPlayer::Get()->alpha;
		}
		if (key == VK_NUMPAD4)
		{
			CLocalPlayer::Get()->offsetX -= CLocalPlayer::Get()->alpha;
		}
		if (key == VK_NUMPAD7)
		{
			CLocalPlayer::Get()->alpha *= 10.f;
		}
		if (key == VK_NUMPAD1)
		{
			CLocalPlayer::Get()->alpha /= 10.f;
		}
		if (key == VK_F4)
		{
			/*intptr_t baseAddress = (intptr_t)GetModuleHandle(NULL);
			intptr_t worldPtr = baseAddress + 0x228FA58;*/
			/*int(*LoadGameNow)(char);
			char* func = Memory::Find("33 C9 E8 ? ? ? ? 8B 0D ? ? ? ? 48 8B 5C 24 ? 8D 41 FC 83 F8 01 0F 47 CF 89 0D ? ? ? ?")->get<char>(2);
			Memory::set_call(&LoadGameNow, func);
			LoadGameNow(0);*/
		}
		/*if (key == VK_F10) {
			Vector3 playerOffsetLocation = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(LocalPlayer->playerPed, 0.0, 3.0, 0.0);
			Hash playermodel1 = GAMEPLAY::GET_HASH_KEY("a_f_y_skater_01");
			Ped player33;

			if (STREAMING::IS_MODEL_IN_CDIMAGE(playermodel1) && STREAMING::IS_MODEL_VALID(playermodel1))

				STREAMING::REQUEST_MODEL(playermodel1);
			while (!STREAMING::HAS_MODEL_LOADED(playermodel1))
				WAIT(0);
			player33 = PED::CREATE_PED(4, playermodel1, playerOffsetLocation.x, playerOffsetLocation.y, playerOffsetLocation.z, 0.0f, true, true);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(playermodel1);

			PED::SET_PED_FLEE_ATTRIBUTES(player33, 0, 0);
			PED::SET_PED_COMBAT_ATTRIBUTES(player33, 17, 1);
			PED::SET_PED_CAN_RAGDOLL(player33, false);

			AI::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(player33, true);
		}*/
	}
}

void Rendering()
{
	CChat::Get()->RegisterCommandProcessor(CommandProcessor);
	for (;;)
	{
		CLocalPlayer::Get()->Tick();

		CChat::Get()->Render();
		CChat::Get()->Input();
		std::stringstream ss;
		ss << "Tasks to ignore: " << CNetworkPlayer::ignoreTasks;
		CUI::PrintText(ss.str().c_str(), 0.8, 0.8);

		CNetworkPlayer::Tick();
		WAIT(0);
	}
}

void RunGameScript() {
	for(;;)
	{
		if (CNetworkConnection::Get()->IsConnected()) {
			CNetworkConnection::Get()->Tick();
			if(CNetworkConnection::Get()->IsConnectionEstablished())
				CLocalPlayer::Get()->SendOnFootData();
		}
		WAIT(15);
	}
}
