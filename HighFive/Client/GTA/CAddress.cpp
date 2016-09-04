#include "stdafx.h"

namespace GTA
{
	CAddress* CAddress::singleInstance = nullptr;
	CAddress::CAddress()
	{
		std::ifstream addressesFile("highfive.dat", std::ifstream::binary);
		bool needToRecreate = false;
		if (!addressesFile.is_open())
			needToRecreate = true;
		if (!needToRecreate)
		{
			std::streampos begin, end;
			begin = addressesFile.tellg();
			addressesFile.seekg(0, std::ios::end);
			end = addressesFile.tellg();
			size_t fileSize = end - begin;
			addressesFile.seekg(0, std::ios::beg);
			if (fileSize != (ADDR_COUNT * 4))
				needToRecreate = true;
		}

		if(needToRecreate)
		{
			std::ofstream addressWriteFile("highfive.dat", std::ifstream::binary);
			addresses[CWORLD_ADDRESS] = CMemory::Find("48 8B 05 ? ? ? ? 45 ? ? ? ? 48 8B 48 08 48 85 C9 74 07")->getOffset(3);//CWorld
			addressWriteFile.write((char*)&addresses[CWORLD_ADDRESS], sizeof(DWORD));
			log_debug << "CWORLD_ADDRESS: 0x" << std::hex << addresses[CWORLD_ADDRESS] << std::endl;

			addresses[LANG_CHANGE] = CMemory::Find("C6 05 ? ? ? ? 01 8B 8F A0 04 00 00")->getOffset(2)+1;//Language change byte
			addressWriteFile.write((char*)&addresses[LANG_CHANGE], sizeof(DWORD));
			log_debug << "LANG_CHANGE: 0x" << std::hex << addresses[LANG_CHANGE] << std::endl;

			addresses[COLOR_ADDRESS] = CMemory::Find("8B 0D ? ? ? ? 44 8B 4C DE 04 81 C9 00 00 00 FF")->getOffset(2)+4;//Player color
			addressWriteFile.write((char*)&addresses[COLOR_ADDRESS], sizeof(DWORD));
			log_debug << "COLOR_ADDRESS: 0x" << std::hex << addresses[COLOR_ADDRESS] << std::endl;

			addresses[GET_TASK_BY_ID] = CMemory::Find("48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 41 54 41 55 41 56 41 57 48 83 EC 20 33 F6 B8 DB 00 00 00")->getFunc();//Load new game
			addressWriteFile.write((char*)&addresses[GET_TASK_BY_ID], sizeof(DWORD));
			log_debug << "GET_TASK_BY_ID: 0x" << std::hex << addresses[GET_TASK_BY_ID] << std::endl;

			addresses[VEHICLE_FACTORY] = CMemory::Find("48 83 EC 28 B9 08 00 00 00 E8 ? ? ? ? 48 85 C0 74 11 48 8B C8 E8 ? ? ? ? 48 89 05 ? ? ? ?")->getOffset(30);//Player color
			addressWriteFile.write((char*)&addresses[VEHICLE_FACTORY], sizeof(DWORD));
			log_debug << "VEHICLE_FACTORY: 0x" << std::hex << addresses[VEHICLE_FACTORY] << std::endl;

			addresses[DISABLE_NORTH_BLIP] = CMemory::Find("E8 ? ? ? ? 41 B8 ? ? ? ? 8B D0 89 05 ? ? ? ? 41 8D 48 FC")->getFunc();//Disable north blip
			addressWriteFile.write((char*)&addresses[DISABLE_NORTH_BLIP], sizeof(DWORD));
			log_debug << "DISABLE_NORTH_BLIP: 0x" << std::hex << addresses[DISABLE_NORTH_BLIP] << std::endl;

			addresses[INITIALIZE_ONLINE] = CMemory::Find("48 89 5C 24 ? 57 48 83 EC 40 33 FF 40 38 3D ? ? ? ?")->getFunc();//Initialize online stuff
			addressWriteFile.write((char*)&addresses[INITIALIZE_ONLINE], sizeof(DWORD));
			log_debug << "INITIALIZE_ONLINE: 0x" << std::hex << addresses[INITIALIZE_ONLINE] << std::endl;

			addresses[DISABLE_PAUSE_ESC] = CMemory::Find("E8 ? ? ? ? C6 05 ? ? ? ? ? EB 24")->getFunc();//Disable esc pause
			addressWriteFile.write((char*)&addresses[DISABLE_PAUSE_ESC], sizeof(DWORD));
			log_debug << "DISABLE_PAUSE_ESC: 0x" << std::hex << addresses[DISABLE_PAUSE_ESC] << std::endl;

			addresses[DISABLE_VEH_POPULATION1] = CMemory::Find("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 20 E8 ? ? ? ? 45 33 E4")->getFunc();//DISABLE_VEH_POPULATION1
			addressWriteFile.write((char*)&addresses[DISABLE_VEH_POPULATION1], sizeof(DWORD));
			log_debug << "DISABLE_VEH_POPULATION1: 0x" << std::hex << addresses[DISABLE_VEH_POPULATION1] << std::endl;

			addresses[DISABLE_VEH_POPULATION4] = CMemory::Find("E8 ? ? ? ? 39 05 ? ? ? ? 7D C5")->getFunc();//DISABLE_VEH_POPULATION4
			addressWriteFile.write((char*)&addresses[DISABLE_VEH_POPULATION4], sizeof(DWORD));
			log_debug << "DISABLE_VEH_POPULATION4: 0x" << std::hex << addresses[DISABLE_VEH_POPULATION4] << std::endl;

			addresses[CRASH_LOAD_MODELS_TOO_QUICKLY] = CMemory::Find("0F 84 ? ? ? ? 44 39 87 ? ? ? ? 0F 8E ? ? ? ?")->getFunc();//CRASH_LOAD_MODELS_TOO_QUICKLY
			addressWriteFile.write((char*)&addresses[CRASH_LOAD_MODELS_TOO_QUICKLY], sizeof(DWORD));
			log_debug << "CRASH_LOAD_MODELS_TOO_QUICKLY: 0x" << std::hex << addresses[CRASH_LOAD_MODELS_TOO_QUICKLY] << std::endl;

			addresses[INTENTIONAL_CRASH] = CMemory::Find("E8 ? ? ? ? 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 85 C9")->getFunc();//INTENTIONAL_CRASH
			addressWriteFile.write((char*)&addresses[INTENTIONAL_CRASH], sizeof(DWORD));
			log_debug << "INTENTIONAL_CRASH: 0x" << std::hex << addresses[INTENTIONAL_CRASH] << std::endl;

			addresses[VAR_VEHICLE_DENSITY1] = CMemory::Find("C7 05 ? ? ? ? ? ? ? ? C7 05 ? ? ? ? ? ? ? ? C7 05 ? ? ? ? ? ? ? ? 88 05 ? ? ? ? F3 0F 11 05 ? ? ? ?")->getOffset(2);//VAR_VEHICLE_DENSITY1
			addressWriteFile.write((char*)&addresses[VAR_VEHICLE_DENSITY1], sizeof(DWORD));
			log_debug << "VAR_VEHICLE_DENSITY1: 0x" << std::hex << addresses[VAR_VEHICLE_DENSITY1] << std::endl;

			addresses[VAR_VEHICLE_DENSITY2] = CMemory::Find("C7 05 ? ? ? ? ? ? ? ? C7 05 ? ? ? ? ? ? ? ? C7 05 ? ? ? ? ? ? ? ? 88 05 ? ? ? ? F3 0F 11 05 ? ? ? ?")->getOffset(12);//VAR_VEHICLE_DENSITY2
			addressWriteFile.write((char*)&addresses[VAR_VEHICLE_DENSITY2], sizeof(DWORD));
			log_debug << "VAR_VEHICLE_DENSITY2: 0x" << std::hex << addresses[VAR_VEHICLE_DENSITY2] << std::endl;

			addresses[VAR_VEHICLE_DENSITY3] = CMemory::Find("C7 05 ? ? ? ? ? ? ? ? C7 05 ? ? ? ? ? ? ? ? C7 05 ? ? ? ? ? ? ? ? 88 05 ? ? ? ? F3 0F 11 05 ? ? ? ?")->getOffset(22);//VAR_VEHICLE_DENSITY3
			addressWriteFile.write((char*)&addresses[VAR_VEHICLE_DENSITY3], sizeof(DWORD));
			log_debug << "VAR_VEHICLE_DENSITY3: 0x" << std::hex << addresses[VAR_VEHICLE_DENSITY3] << std::endl;

			addresses[VAR_VEHICLE_DENSITY_NOP] = CMemory::Find("C7 05 ? ? ? ? ? ? ? ? C7 05 ? ? ? ? ? ? ? ? C7 05 ? ? ? ? ? ? ? ? 88 05 ? ? ? ? F3 0F 11 05 ? ? ? ?")->getFunc();//VAR_VEHICLE_DENSITY3
			addressWriteFile.write((char*)&addresses[VAR_VEHICLE_DENSITY_NOP], sizeof(DWORD));
			log_debug << "VAR_VEHICLE_DENSITY_NOP: 0x" << std::hex << addresses[VAR_VEHICLE_DENSITY_NOP] << std::endl;

			addresses[PED_DENSITY1] = CMemory::Find("C7 05 ? ? ? ? 00 00 80 3F C7 05 ? ? ? ? 00 00 80 3F C7 05 ? ? ? ? 00 00 80 3F C7 05 ? ? ? ? 00 00 80 3F 74 05 E8 ? ? ? ?")->getOffset(2);//PED_DENSITY1
			addressWriteFile.write((char*)&addresses[PED_DENSITY1], sizeof(DWORD));
			log_debug << "PED_DENSITY1: 0x" << std::hex << addresses[PED_DENSITY1] << std::endl;

			addresses[PED_DENSITY2] = CMemory::Find("C7 05 ? ? ? ? 00 00 80 3F C7 05 ? ? ? ? 00 00 80 3F C7 05 ? ? ? ? 00 00 80 3F C7 05 ? ? ? ? 00 00 80 3F 74 05 E8 ? ? ? ?")->getOffset(12);//PED_DENSITY2
			addressWriteFile.write((char*)&addresses[PED_DENSITY2], sizeof(DWORD));
			log_debug << "PED_DENSITY2: 0x" << std::hex << addresses[PED_DENSITY2] << std::endl;

			addresses[PED_DENSITY3] = CMemory::Find("C7 05 ? ? ? ? 00 00 80 3F C7 05 ? ? ? ? 00 00 80 3F C7 05 ? ? ? ? 00 00 80 3F C7 05 ? ? ? ? 00 00 80 3F 74 05 E8 ? ? ? ?")->getOffset(22);//PED_DENSITY3
			addressWriteFile.write((char*)&addresses[PED_DENSITY3], sizeof(DWORD));
			log_debug << "PED_DENSITY3: 0x" << std::hex << addresses[PED_DENSITY3] << std::endl;

			addresses[PED_DENSITY4] = CMemory::Find("C7 05 ? ? ? ? 00 00 80 3F C7 05 ? ? ? ? 00 00 80 3F C7 05 ? ? ? ? 00 00 80 3F C7 05 ? ? ? ? 00 00 80 3F 74 05 E8 ? ? ? ?")->getOffset(32);//PED_DENSITY4
			addressWriteFile.write((char*)&addresses[PED_DENSITY4], sizeof(DWORD));
			log_debug << "PED_DENSITY4: 0x" << std::hex << addresses[PED_DENSITY4] << std::endl;

			addresses[PED_DENSITY_NOP] = CMemory::Find("C7 05 ? ? ? ? 00 00 80 3F C7 05 ? ? ? ? 00 00 80 3F C7 05 ? ? ? ? 00 00 80 3F C7 05 ? ? ? ? 00 00 80 3F 74 05 E8 ? ? ? ?")->getFunc();//PED_DENSITY_NOP
			addressWriteFile.write((char*)&addresses[PED_DENSITY_NOP], sizeof(DWORD));
			log_debug << "PED_DENSITY_NOP: 0x" << std::hex << addresses[PED_DENSITY_NOP] << std::endl;

			addresses[DISABLE_LOGO] = CMemory::Find("40 53 48 83 EC 20 48 83 3D ? ? ? ? ? 0F 85 ? ? ? ? 8B 05 ? ? ? ? 4C 8D 44 24 ? 48 8D 54 24 ? 48 8D 0D ? ? ? ? 89 44 24 30 E8 ? ? ? ? 48 63 18 83 FB FF 0F 84 ? ? ? ?")->getFunc();//DISABLE_LOGO
			addressWriteFile.write((char*)&addresses[DISABLE_LOGO], sizeof(DWORD));
			log_debug << "DISABLE_LOGO: 0x" << std::hex << addresses[DISABLE_LOGO] << std::endl;

			addresses[SHOW_TOOL_TIPS] = CMemory::Find("48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 45 8B E0")->getFunc();//SHOW_TOOL_TIPS
			addressWriteFile.write((char*)&addresses[SHOW_TOOL_TIPS], sizeof(DWORD));
			log_debug << "SHOW_TOOL_TIPS: 0x" << std::hex << addresses[SHOW_TOOL_TIPS] << std::endl;

			addresses[SOCIAL_CLUB_NEWS] = CMemory::Find("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 33 ED 48 8B D9 40 38 69 1C")->getFunc();//SOCIAL_CLUB_NEWS
			addressWriteFile.write((char*)&addresses[SOCIAL_CLUB_NEWS], sizeof(DWORD));
			log_debug << "SOCIAL_CLUB_NEWS: 0x" << std::hex << addresses[SOCIAL_CLUB_NEWS] << std::endl;

			addresses[LOAD_SCREENS] = CMemory::Find("E8 ? ? ? ? 8B CB 40 88 2D ? ? ? ?")->getFunc();//LOAD_SCREENS
			addressWriteFile.write((char*)&addresses[LOAD_SCREENS], sizeof(DWORD));
			log_debug << "LOAD_SCREENS: 0x" << std::hex << addresses[LOAD_SCREENS] << std::endl;

			addresses[GTAMP_NOP1] = CMemory::Find("E8 ? ? ? ? 48 8B D8 48 85 C0 75 30")->getFunc();//GTAMP_NOP1
			addressWriteFile.write((char*)&addresses[GTAMP_NOP1], sizeof(DWORD));
			log_debug << "GTAMP_NOP1: 0x" << std::hex << addresses[GTAMP_NOP1] << std::endl;

			addresses[GTAMP_NOP2] = CMemory::Find("E8 ? ? ? ? E8 ? ? ? ? E8 ? ? ? ? B9 ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ?")->getFunc();//GTAMP_NOP2
			addressWriteFile.write((char*)&addresses[GTAMP_NOP2], sizeof(DWORD));
			log_debug << "GTAMP_NOP2: 0x" << std::hex << addresses[GTAMP_NOP2] << std::endl;

			addresses[GTAMP_NOP3] = CMemory::Find("E8 ? ? ? ? E8 ? ? ? ? B9 ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ?")->getFunc();//GTAMP_NOP3
			addressWriteFile.write((char*)&addresses[GTAMP_NOP3], sizeof(DWORD));
			log_debug << "GTAMP_NOP3: 0x" << std::hex << addresses[GTAMP_NOP3] << std::endl;

			addresses[LOAD_SINGLE_PLAYER1] = CMemory::Find("48 83 EC 28 85 D2 78 71 75 0F")->getFunc();//LOAD_SINGLE_PLAYER1
			addressWriteFile.write((char*)&addresses[LOAD_SINGLE_PLAYER1], sizeof(DWORD));
			log_debug << "LOAD_SINGLE_PLAYER1: 0x" << std::hex << addresses[LOAD_SINGLE_PLAYER1] << std::endl;

			addresses[LOAD_SINGLE_PLAYER2] = CMemory::Find("48 83 EC 28 B9 ? ? ? ? E8 ? ? ? ? B9 ? ? ? ? E8 ? ? ? ? B1 01")->getFunc();//LOAD_SINGLE_PLAYER2
			addressWriteFile.write((char*)&addresses[LOAD_SINGLE_PLAYER2], sizeof(DWORD));
			log_debug << "LOAD_SINGLE_PLAYER2: 0x" << std::hex << addresses[LOAD_SINGLE_PLAYER2] << std::endl;

			addresses[GAME_VIEWPORT] = CMemory::Find("4C 8B 3D ? ? ? ? 4D 85 FF 0F 84 ? ? ? ? 48 8B 0D ? ? ? ? 33 DB 0F B7 41 08")->getOffset(3);//GAME_VIEWPORT
			addressWriteFile.write((char*)&addresses[GAME_VIEWPORT], sizeof(DWORD));
			log_debug << "GAME_VIEWPORT: 0x" << std::hex << addresses[GAME_VIEWPORT] << std::endl;

			addresses[REPLAY_INTERFACES] = CMemory::Find("48 8D 0D ? ? ? ? 48 8B D7 E8 ? ? ? ? 48 8D 0D ? ? ? ? 8A D8 E8 ? ? ? ? 84 DB 75 13 48 8D 0D ? ? ? ?")->getOffset(3);//REPLAY_INTERFACES
			addressWriteFile.write((char*)&addresses[REPLAY_INTERFACES], sizeof(DWORD));
			log_debug << "REPLAY_INTERFACES: 0x" << std::hex << addresses[REPLAY_INTERFACES] << std::endl;

			addresses[INIT_ONLINE_COMPONENTS] = CMemory::Find("40 53 48 83 EC 50 80 3D ? ? ? ? ? C6 05 ? ? ? ? ?")->getFunc();//INIT_ONLINE_COMPONENTS
			addressWriteFile.write((char*)&addresses[INIT_ONLINE_COMPONENTS], sizeof(DWORD));
			log_debug << "INIT_ONLINE_COMPONENTS: 0x" << std::hex << addresses[INIT_ONLINE_COMPONENTS] << std::endl;

			addresses[ABILITY_BAR_VISIBLITY] = CMemory::Find("40 53 48 83 EC 30 41 83 C9 FF 8A D9 88 ? ? ? ? ? 8B ? ? ? ? ?")->getFunc();//ABILITY_BAR_VISIBLITY
			addressWriteFile.write((char*)&addresses[ABILITY_BAR_VISIBLITY], sizeof(DWORD));
			log_debug << "ABILITY_BAR_VISIBLITY: 0x" << std::hex << addresses[ABILITY_BAR_VISIBLITY] << std::endl;

			addresses[MULTIPLAYER_MENU] = CMemory::Find("80 3D ? ? ? ? ? 74 1B 84 DB 74 10 ? ? ? ? ? ? ? ? ? ? ? ? ? ? EB 39")->getFunc();//MULTIPLAYER_MENU
			addressWriteFile.write((char*)&addresses[MULTIPLAYER_MENU], sizeof(DWORD));
			log_debug << "MULTIPLAYER_MENU: 0x" << std::hex << addresses[MULTIPLAYER_MENU] << std::endl;

			addresses[PED_CHANGE_MODEL] = CMemory::Find("40 55 53 57 48 8B EC 48 83 EC 30 8B F9")->getFunc();//PED_CHANGE_MODEL
			addressWriteFile.write((char*)&addresses[PED_CHANGE_MODEL], sizeof(DWORD));
			log_debug << "PED_CHANGE_MODEL: 0x" << std::hex << addresses[PED_CHANGE_MODEL] << std::endl;

			addresses[PED_TASK_MOVE_TO_COORD] = CMemory::Find("48 8B C4 48 89 58 08 48 89 68 10 57 48 81 EC 80 00 00 00 0F 29 70 E8")->getFunc();//PED_TASK_MOVE_TO_COORD
			addressWriteFile.write((char*)&addresses[PED_TASK_MOVE_TO_COORD], sizeof(DWORD));
			log_debug << "PED_TASK_MOVE_TO_COORD: 0x" << std::hex << addresses[PED_TASK_MOVE_TO_COORD] << std::endl;

			addresses[PED_TASK_AIM_AT_COORD_AND_STAND_STILL] = CMemory::Find("41 83 F8 FF 0F ? ? ? ? ? 48 8B C4 48 89 58 08 48 89 68 10 56 57 41 56 48 83 EC 60")->getFunc();//PED_TASK_AIM_AT_COORD_AND_STAND_STILL
			addressWriteFile.write((char*)&addresses[PED_TASK_AIM_AT_COORD_AND_STAND_STILL], sizeof(DWORD));
			log_debug << "PED_TASK_AIM_AT_COORD_AND_STAND_STILL: 0x" << std::hex << addresses[PED_TASK_AIM_AT_COORD_AND_STAND_STILL] << std::endl;

			addresses[PED_TASK_AIM_AT_COORD_AND_MOVE_TO_COORD] = CMemory::Find("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 30 0F 29 74 24 ? 49 8B F8 48 8B DA 0F 28 F3 48 8B F1 E8 ? ? ? ? 48 8D 05 ? ? ? ? 48 8D 8E ? ? ? ?")->getFunc();//PED_TASK_AIM_AT_COORD_AND_MOVE_TO_COORD
			addressWriteFile.write((char*)&addresses[PED_TASK_AIM_AT_COORD_AND_MOVE_TO_COORD], sizeof(DWORD));
			log_debug << "PED_TASK_AIM_AT_COORD_AND_MOVE_TO_COORD: 0x" << std::hex << addresses[PED_TASK_AIM_AT_COORD_AND_MOVE_TO_COORD] << std::endl;

			addresses[RENDERING_TOGGLE_LASER_SIGHT] = CMemory::Find("80 3D ? ? ? ? ? 0F 29 70 E8 48 8B F2")->getOffset(2) + 1;//RENDERING_TOGGLE_LASER_SIGHT
			addressWriteFile.write((char*)&addresses[RENDERING_TOGGLE_LASER_SIGHT], sizeof(DWORD));
			log_debug << "RENDERING_TOGGLE_LASER_SIGHT: 0x" << std::hex << addresses[RENDERING_TOGGLE_LASER_SIGHT] << std::endl;

			addresses[DISABLE_WANTED_GENERATION_1] = CMemory::Find("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 30 8B 05 ? ? ? ? 8B B9 ? ? ? ?")->getFunc();//DISABLE_WANTED_GENERATION_1
			addressWriteFile.write((char*)&addresses[DISABLE_WANTED_GENERATION_1], sizeof(DWORD));
			log_debug << "DISABLE_WANTED_GENERATION_1: 0x" << std::hex << addresses[DISABLE_WANTED_GENERATION_1] << std::endl;

			addresses[DISABLE_WANTED_GENERATION_2] = CMemory::Find("0F 84 ? ? ? ? 44 39 87 ? ? ? ? 0F 8E ? ? ? ?")->getFunc();//DISABLE_WANTED_GENERATION_2
			addressWriteFile.write((char*)&addresses[DISABLE_WANTED_GENERATION_2], sizeof(DWORD));
			log_debug << "DISABLE_WANTED_GENERATION_2: 0x" << std::hex << addresses[DISABLE_WANTED_GENERATION_2] << std::endl;

			addresses[SOME_STRANGE_HOOK] = CMemory::Find("A8 FC 75 06 80 7F 36 04")->getFunc() - 0x42;//SOME_STRANGE_HOOK
			addressWriteFile.write((char*)&addresses[SOME_STRANGE_HOOK], sizeof(DWORD));
			log_debug << "SOME_STRANGE_HOOK: 0x" << std::hex << addresses[SOME_STRANGE_HOOK] << std::endl;

			addresses[CREATE_NETWORK_EVENT_BINDINGS] = CMemory::Find("48 83 EC 28 E8 ? ? ? ? 48 8B ? ? ? ? ? 4C 8D ? ? ? ? ? 4C 8D ? ? ? ? ? BA 03 00 00 00 E8 ? ? ? ?")->getFunc();//CREATE_NETWORK_EVENT_BINDINGS
			addressWriteFile.write((char*)&addresses[CREATE_NETWORK_EVENT_BINDINGS], sizeof(DWORD));
			log_debug << "CREATE_NETWORK_EVENT_BINDINGS: 0x" << std::hex << addresses[CREATE_NETWORK_EVENT_BINDINGS] << std::endl;

			addresses[LOAD_NEW_GAME] = CMemory::Find("40 53 48 83 EC 20 33 DB 8B CB E8 ? ? ? ? 84 C0 75 2C")->getFunc();//LOAD_NEW_GAME
			addressWriteFile.write((char*)&addresses[LOAD_NEW_GAME], sizeof(DWORD));
			log_debug << "LOAD_NEW_GAME: 0x" << std::hex << addresses[LOAD_NEW_GAME] << std::endl;

			addresses[OPEN_CHEAT_WINDOW] = CMemory::Find("40 55 48 8B EC 48 83 EC 50 C6 05 ? ? ? ? ? 48 8B 11 48 8B 41 ? 48")->getFunc();//OPEN_CHEAT_WINDOW
			addressWriteFile.write((char*)&addresses[OPEN_CHEAT_WINDOW], sizeof(DWORD));
			log_debug << "OPEN_CHEAT_WINDOW: 0x" << std::hex << addresses[OPEN_CHEAT_WINDOW] << std::endl;

			addresses[RESET_VEHICLE_DENSITY_LAST_FRAME] = CMemory::Find("33 C0 0F 57 C0 C7 05 ? ? ? ? ? ? ? ?")->getFunc();//RESET_VEHICLE_DENSITY_LAST_FRAME
			addressWriteFile.write((char*)&addresses[RESET_VEHICLE_DENSITY_LAST_FRAME], sizeof(DWORD));
			log_debug << "RESET_VEHICLE_DENSITY_LAST_FRAME: 0x" << std::hex << addresses[RESET_VEHICLE_DENSITY_LAST_FRAME] << std::endl;

			addresses[SET_CLOCK_FORWARD_AFTER_DEATH] = CMemory::Find("40 53 48 83 EC 20 48 8B D9 48 83 C1 10 E8 ? ? ? ? 48 8B CB 8B D0")->getFunc();//SET_CLOCK_FORWARD_AFTER_DEATH
			addressWriteFile.write((char*)&addresses[SET_CLOCK_FORWARD_AFTER_DEATH], sizeof(DWORD));
			log_debug << "SET_CLOCK_FORWARD_AFTER_DEATH: 0x" << std::hex << addresses[SET_CLOCK_FORWARD_AFTER_DEATH] << std::endl;

			addresses[DISABLE_LOADING_MP_DLC_CONTENT] = CMemory::Find("48 89 5C 24 ? 57 48 83 EC 20 8A 81 ? ? ? ? 8B FA")->getFunc();//DISABLE_LOADING_MP_DLC_CONTENT
			addressWriteFile.write((char*)&addresses[DISABLE_LOADING_MP_DLC_CONTENT], sizeof(DWORD));
			log_debug << "DISABLE_LOADING_MP_DLC_CONTENT: 0x" << std::hex << addresses[DISABLE_LOADING_MP_DLC_CONTENT] << std::endl;

			//DISABLE_LOADING_MP_DLC_CONTENT

			addressWriteFile.close();
		}
		else
		{
			for (int i = 0; i < ADDR_COUNT; ++i)
				addressesFile.read((char*)(&addresses[i]), sizeof(int32_t));
			addressesFile.close();
		}
	}
};
