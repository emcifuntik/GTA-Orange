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
		if (key == VK_NUMPAD5)
		{
			CLocalPlayer::Get()->newModel = GAMEPLAY::GET_HASH_KEY((char*)(models[(GetTickCount() % 30) + 100]));
		}
		if (key == VK_NUMPAD8)
		{
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
