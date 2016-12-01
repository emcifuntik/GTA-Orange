#include "stdafx.h"
#include "Natives.h"

void Action()
{
	bool teleported = false;
	while (true)
	{
		if (!teleported)
		{
			CGlobals::Get().InitializeOnline();
			ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0.f, 0.f, 73.f, true, false, false, false);
			CGlobals::Get().currentcam = 
		    CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", false);
			CAM::SET_CAM_COORD(CGlobals::Get().currentcam, 0.f, 0.f, 100.f);
			CAM::POINT_CAM_AT_COORD(CGlobals::Get().currentcam, 300.f, 300.f, 50.f);
			CAM::SET_CAM_ACTIVE(CGlobals::Get().currentcam, true);
			CAM::RENDER_SCRIPT_CAMS(true, false, 0, true, false);
			UI::DISPLAY_HUD(false);
			UI::DISPLAY_RADAR(false);
			CGlobals::Get().displayServerBrowser = true;
			teleported = true;
			CChat::Get()->AddChatMessage("Grand Theft Auto: Orange loaded");

			typedef int(*ShowAbilityBar)(bool);
			((ShowAbilityBar)CMemory::Find("40 53 48 83 EC 30 41 83 C9 FF 8A D9 88 ? ? ? ? ? 8B ? ? ? ? ?")())(false);
		}
		UI::SET_PAUSE_MENU_ACTIVE(false);
		scriptWait(0);
	}
}

SCRIPT("gameInit", Action, gameInit);
