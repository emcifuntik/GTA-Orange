#include "stdafx.h"
#include "Natives.h"

void Action()
{
	bool teleported = false;
	while (true)
	{
		if (!teleported)
		{
			ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0.f, 0.f, 73.f, true, false, false, false);
			/*auto model = Utils::Hash("mp_m_freemode_01");
			if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_VALID(model))
			STREAMING::REQUEST_MODEL(model);
			while (!STREAMING::HAS_MODEL_LOADED(model))
			scriptWait(0);
			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), model);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);*/

			Cam firstCam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", false);
			CAM::SET_CAM_COORD(firstCam, 0.f, 0.f, 100.f);
			CAM::POINT_CAM_AT_COORD(firstCam, 300.f, 300.f, 50.f);
			CAM::SET_CAM_ACTIVE(firstCam, true);
			CAM::RENDER_SCRIPT_CAMS(true, false, 0, true, false);
			UI::DISPLAY_HUD(false);
			UI::DISPLAY_RADAR(false);
			teleported = true;
		}
		scriptWait(0);
	}
}

SCRIPT("gameInit", Action);