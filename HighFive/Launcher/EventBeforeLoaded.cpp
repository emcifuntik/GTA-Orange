#include "stdafx.h"

typedef struct {
	char *name;
	bool enable;
} ScriptInfo;

ScriptInfo scriptnames[748] = {
	{ "abigail1", false },
	{ "abigail2", false },
	{ "achievement_controller", false },
	{ "act_cinema", false },
	{ "af_intro_t_sandy", false },
	{ "agency_heist1", false },
	{ "agency_heist2", false },
	{ "agency_heist3a", false },
	{ "agency_heist3b", false },
	{ "agency_prep1", false },
	{ "agency_prep2amb", false },
	{ "aicover_test", false },
	{ "ainewengland_test", false },
	{ "altruist_cult", false },
	{ "ambientblimp", false },
	{ "ambient_diving", false },
	{ "ambient_mrsphilips", false },
	{ "ambient_solomon", false },
	{ "ambient_sonar", false },
	{ "ambient_tonya", false },
	{ "ambient_tonyacall", false },
	{ "ambient_tonyacall2", false },
	{ "ambient_tonyacall5", false },
	{ "ambient_ufos", false },
	{ "am_airstrike", false },
	{ "am_ammo_drop", false },
	{ "am_armwrestling", false },
	{ "am_armybase", false },
	{ "am_backup_heli", false },
	{ "am_boat_taxi", false },
	{ "am_bru_box", false },
	{ "am_car_mod_tut", false },
	{ "am_challenges", false },
	{ "am_contact_requests", false },
	{ "am_cp_collection", false },
	{ "am_crate_drop", false },
	{ "am_criminal_damage", false },
	{ "am_cr_securityvan", false },
	{ "am_darts", false },
	{ "am_dead_drop", false },
	{ "am_destroy_veh", false },
	{ "am_distract_cops", false },
	{ "am_doors", false },
	{ "am_ferriswheel", false },
	{ "am_gang_call", false },
	{ "am_ga_pickups", false },
	{ "am_heist_int", false },
	{ "am_heli_taxi", false },
	{ "am_hold_up", false },
	{ "am_hot_property", false },
	{ "am_hot_target", false },
	{ "am_hunt_the_beast", false },
	{ "am_imp_exp", false },
	{ "am_joyrider", false },
	{ "am_kill_list", false },
	{ "am_king_of_the_castle", false },
	{ "am_launcher", false },
	{ "am_lester_cut", false },
	{ "am_lowrider_int", false },
	{ "am_mission_launch", false },
	{ "am_mp_carwash_launch", false },
	{ "am_mp_garage_control", false },
	{ "am_mp_property_ext", false },
	{ "am_mp_property_int", false },
	{ "am_mp_yacht", false },
	{ "am_npc_invites", false },
	{ "am_pass_the_parcel", false },
	{ "am_penned_in", false },
	{ "am_pi_menu", false },
	{ "am_plane_takedown", false },
	{ "am_prison", false },
	{ "am_prostitute", false },
	{ "am_rollercoaster", false },
	{ "am_rontrevor_cut", false },
	{ "am_taxi", false },
	{ "am_vehicle_spawn", true },
	{ "animal_controller", false },
	{ "appbroadcast", false },
	{ "appcamera", false },
	{ "appchecklist", false },
	{ "appcontacts", false },
	{ "appemail", false },
	{ "appextraction", false },
	{ "apphs_sleep", false },
	{ "appinternet", false },
	{ "appjipmp", false },
	{ "appmedia", false },
	{ "appmpbossagency", false },
	{ "appmpemail", false },
	{ "appmpjoblistnew", false },
	{ "apporganiser", false },
	{ "apprepeatplay", false },
	{ "appsettings", false },
	{ "appsidetask", false },
	{ "apptextmessage", false },
	{ "apptrackify", false },
	{ "appvlsi", false },
	{ "appzit", false },
	{ "armenian1", false },
	{ "armenian2", false },
	{ "armenian3", false },
	{ "assassin_bus", false },
	{ "assassin_construction", false },
	{ "assassin_hooker", false },
	{ "assassin_multi", false },
	{ "assassin_rankup", false },
	{ "assassin_valet", false },
	{ "atm_trigger", false },
	{ "audiotest", false },
	{ "autosave_controller", false },
	{ "bailbond1", false },
	{ "bailbond2", false },
	{ "bailbond3", false },
	{ "bailbond4", false },
	{ "bailbond_launcher", false },
	{ "barry1", false },
	{ "barry2", false },
	{ "barry3", false },
	{ "barry3a", false },
	{ "barry3c", false },
	{ "barry4", false },
	{ "benchmark", false },
	{ "bigwheel", false },
	{ "bj", false },
	{ "blimptest", false },
	{ "blip_controller", true },
	{ "bootycallhandler", false },
	{ "bootycall_debug_controller", false },
	{ "buddydeathresponse", false },
	{ "bugstar_mission_export", false },
	{ "buildingsiteambience", false },
	{ "building_controller", false },
	{ "cablecar", false },
	{ "camera_test", false },
	{ "cam_coord_sender", true },
	{ "candidate_controller", false },
	{ "carmod_shop", false },
	{ "carsteal1", false },
	{ "carsteal2", false },
	{ "carsteal3", false },
	{ "carsteal4", false },
	{ "carwash1", false },
	{ "carwash2", false },
	{ "car_roof_test", false },
	{ "celebrations", false },
	{ "celebration_editor", false },
	{ "cellphone_controller", false },
	{ "cellphone_flashhand", false },
	{ "charactergoals", false },
	{ "charanimtest", false },
	{ "cheat_controller", false },
	{ "chinese1", false },
	{ "chinese2", false },
	{ "chop", false },
	{ "clothes_shop_mp", false },
	{ "clothes_shop_sp", false },
	{ "code_controller", false },
	{ "combat_test", false },
	{ "comms_controller", false },
	{ "completionpercentage_controller", false },
	{ "component_checker", false },
	{ "context_controller", false },
	{ "controller_ambientarea", false },
	{ "controller_races", false },
	{ "controller_taxi", false },
	{ "controller_towing", false },
	{ "controller_trafficking", false },
	{ "coordinate_recorder", true },
	{ "country_race", false },
	{ "country_race_controller", false },
	{ "creation_startup", false },
	{ "creator", false },
	{ "custom_config", false },
	{ "cutscenemetrics", false },
	{ "cutscenesamples", false },
	{ "cutscene_test", false },
	{ "darts", false },
	{ "debug", false },
	{ "debug_app_select_screen", false },
	{ "debug_launcher", false },
	{ "density_test", false },
	{ "dialogue_handler", false },
	{ "director_mode", false },
	{ "docks2asubhandler", false },
	{ "docks_heista", false },
	{ "docks_heistb", false },
	{ "docks_prep1", false },
	{ "docks_prep2b", false },
	{ "docks_setup", false },
	{ "dreyfuss1", false },
	{ "drf1", false },
	{ "drf2", false },
	{ "drf3", false },
	{ "drf4", false },
	{ "drf5", false },
	{ "drunk", false },
	{ "drunk_controller", false },
	{ "dynamixtest", false },
	{ "email_controller", false },
	{ "emergencycall", false },
	{ "emergencycalllauncher", false },
	{ "epscars", false },
	{ "epsdesert", false },
	{ "epsilon1", false },
	{ "epsilon2", false },
	{ "epsilon3", false },
	{ "epsilon4", false },
	{ "epsilon5", false },
	{ "epsilon6", false },
	{ "epsilon7", false },
	{ "epsilon8", false },
	{ "epsilontract", false },
	{ "epsrobes", false },
	{ "event_controller", false },
	{ "exile1", false },
	{ "exile2", false },
	{ "exile3", false },
	{ "exile_city_denial", false },
	{ "extreme1", false },
	{ "extreme2", false },
	{ "extreme3", false },
	{ "extreme4", false },
	{ "fairgroundhub", false },
	{ "fake_interiors", false },
	{ "fameorshame_eps", false },
	{ "fameorshame_eps_1", false },
	{ "fame_or_shame_set", false },
	{ "family1", false },
	{ "family1taxi", false },
	{ "family2", false },
	{ "family3", false },
	{ "family4", false },
	{ "family5", false },
	{ "family6", false },
	{ "family_scene_f0", false },
	{ "family_scene_f1", false },
	{ "family_scene_m", false },
	{ "family_scene_t0", false },
	{ "family_scene_t1", false },
	{ "fanatic1", false },
	{ "fanatic2", false },
	{ "fanatic3", false },
	{ "fbi1", false },
	{ "fbi2", false },
	{ "fbi3", false },
	{ "fbi4", false },
	{ "fbi4_intro", false },
	{ "fbi4_prep1", false },
	{ "fbi4_prep2", false },
	{ "fbi4_prep3", false },
	{ "fbi4_prep3amb", false },
	{ "fbi4_prep4", false },
	{ "fbi4_prep5", false },
	{ "fbi5a", false },
	{ "filenames.txt", false },
	{ "finalea", false },
	{ "finaleb", false },
	{ "finalec1", false },
	{ "finalec2", false },
	{ "finale_choice", false },
	{ "finale_credits", false },
	{ "finale_endgame", false },
	{ "finale_heist1", false },
	{ "finale_heist2a", false },
	{ "finale_heist2b", false },
	{ "finale_heist2_intro", false },
	{ "finale_heist_prepa", false },
	{ "finale_heist_prepb", false },
	{ "finale_heist_prepc", false },
	{ "finale_heist_prepd", false },
	{ "finale_heist_prepeamb", false },
	{ "finale_intro", false },
	{ "floating_help_controller", false },
	{ "flowintrotitle", false },
	{ "flowstartaccept", false },
	{ "flow_autoplay", false },
	{ "flow_controller", false },
	{ "flow_help", false },
	{ "flyunderbridges", false },
	{ "fmmc_launcher", false },
	{ "fmmc_playlist_controller", false },
	{ "fm_bj_race_controler", false },
	{ "fm_capture_creator", false },
	{ "fm_deathmatch_controler", false },
	{ "fm_deathmatch_creator", false },
	{ "fm_hideout_controler", false },
	{ "fm_hold_up_tut", false },
	{ "fm_horde_controler", false },
	{ "fm_impromptu_dm_controler", false },
	{ "fm_intro", false },
	{ "fm_intro_cut_dev", false },
	{ "fm_lts_creator", false },
	{ "fm_maintain_cloud_header_data", false },
	{ "fm_maintain_transition_players", false },
	{ "fm_main_menu", false },
	{ "fm_mission_controller", false },
	{ "fm_mission_creator", false },
	{ "fm_race_controler", false },
	{ "fm_race_creator", false },
	{ "forsalesigns", false },
	{ "fps_test", false },
	{ "fps_test_mag", false },
	{ "franklin0", false },
	{ "franklin1", false },
	{ "franklin2", false },
	{ "freemode", false },
	{ "freemode_init", false },
	{ "friendactivity", false },
	{ "friends_controller", false },
	{ "friends_debug_controller", false },
	{ "fullmap_test", true },
	{ "fullmap_test_flow", true },
	{ "game_server_test", false },
	{ "gb_assault", false },
	{ "gb_bellybeast", false },
	{ "gb_carjacking", false },
	{ "gb_collect_money", false },
	{ "gb_deathmatch", false },
	{ "gb_finderskeepers", false },
	{ "gb_fivestar", false },
	{ "gb_hunt_the_boss", false },
	{ "gb_point_to_point", false },
	{ "gb_rob_shop", false },
	{ "gb_sightseer", false },
	{ "gb_terminate", false },
	{ "gb_yacht_rob", false },
	{ "general_test", false },
	{ "golf", false },
	{ "golf_ai_foursome", false },
	{ "golf_ai_foursome_putting", false },
	{ "golf_mp", false },
	{ "gpb_andymoon", false },
	{ "gpb_baygor", false },
	{ "gpb_billbinder", false },
	{ "gpb_clinton", false },
	{ "gpb_griff", false },
	{ "gpb_jane", false },
	{ "gpb_jerome", false },
	{ "gpb_jesse", false },
	{ "gpb_mani", false },
	{ "gpb_mime", false },
	{ "gpb_pameladrake", false },
	{ "gpb_superhero", false },
	{ "gpb_tonya", false },
	{ "gpb_zombie", false },
	{ "gtest_airplane", false },
	{ "gtest_avoidance", false },
	{ "gtest_boat", false },
	{ "gtest_divingfromcar", false },
	{ "gtest_divingfromcarwhilefleeing", false },
	{ "gtest_helicopter", false },
	{ "gtest_nearlymissedbycar", false },
	{ "gunclub_shop", false },
	{ "gunfighttest", false },
	{ "hairdo_shop_mp", false },
	{ "hairdo_shop_sp", false },
	{ "hao1", false },
	{ "headertest", false },
	{ "heatmap_test", false },
	{ "heatmap_test_flow", false },
	{ "heist_ctrl_agency", false },
	{ "heist_ctrl_docks", false },
	{ "heist_ctrl_finale", false },
	{ "heist_ctrl_jewel", false },
	{ "heist_ctrl_rural", false },
	{ "heli_gun", false },
	{ "heli_streaming", true },
	{ "hud_creator", true },
	{ "hunting1", false },
	{ "hunting2", false },
	{ "hunting_ambient", false },
	{ "idlewarper", false },
	{ "ingamehud", true },
	{ "initial", false },
	{ "jewelry_heist", false },
	{ "jewelry_prep1a", false },
	{ "jewelry_prep1b", false },
	{ "jewelry_prep2a", false },
	{ "jewelry_setup1", false },
	{ "josh1", false },
	{ "josh2", false },
	{ "josh3", false },
	{ "josh4", false },
	{ "lamar1", false },
	{ "laptop_trigger", false },
	{ "launcher_abigail", false },
	{ "launcher_barry", false },
	{ "launcher_basejumpheli", false },
	{ "launcher_basejumppack", false },
	{ "launcher_carwash", false },
	{ "launcher_darts", false },
	{ "launcher_dreyfuss", false },
	{ "launcher_epsilon", false },
	{ "launcher_extreme", false },
	{ "launcher_fanatic", false },
	{ "launcher_golf", false },
	{ "launcher_hao", false },
	{ "launcher_hunting", false },
	{ "launcher_hunting_ambient", false },
	{ "launcher_josh", false },
	{ "launcher_maude", false },
	{ "launcher_minute", false },
	{ "launcher_mrsphilips", false },
	{ "launcher_nigel", false },
	{ "launcher_offroadracing", false },
	{ "launcher_omega", false },
	{ "launcher_paparazzo", false },
	{ "launcher_pilotschool", false },
	{ "launcher_racing", false },
	{ "launcher_rampage", false },
	{ "launcher_range", false },
	{ "launcher_stunts", false },
	{ "launcher_tennis", false },
	{ "launcher_thelastone", false },
	{ "launcher_tonya", false },
	{ "launcher_triathlon", false },
	{ "launcher_yoga", false },
	{ "lester1", false },
	{ "lesterhandler", false },
	{ "letterscraps", false },
	{ "line_activation_test", false },
	{ "liverecorder", false },
	{ "locates_tester", false },
	{ "luxe_veh_activity", false },
	{ "magdemo", false },
	{ "magdemo2", false },
	{ "main", false },
	{ "maintransition", false },
	{ "main_install", false },
	{ "main_persistent", false },
	{ "martin1", false },
	{ "maude1", false },
	{ "maude_postbailbond", false },
	{ "me_amanda1", false },
	{ "me_jimmy1", false },
	{ "me_tracey1", false },
	{ "mg_race_to_point", false },
	{ "michael1", false },
	{ "michael2", false },
	{ "michael3", false },
	{ "michael4", false },
	{ "michael4leadout", false },
	{ "minigame_ending_stinger", false },
	{ "minigame_stats_tracker", false },
	{ "minute1", false },
	{ "minute2", false },
	{ "minute3", false },
	{ "mission_race", false },
	{ "mission_repeat_controller", false },
	{ "mission_stat_alerter", false },
	{ "mission_stat_watcher", false },
	{ "mission_triggerer_a", false },
	{ "mission_triggerer_b", false },
	{ "mission_triggerer_c", false },
	{ "mission_triggerer_d", false },
	{ "mpstatsinit", false },
	{ "mptestbed", false },
	{ "mp_awards", false },
	{ "mp_fm_registration", false },
	{ "mp_menuped", false },
	{ "mp_prop_global_block", false },
	{ "mp_prop_special_global_block", false },
	{ "mp_registration", false },
	{ "mp_save_game_global_block", false },
	{ "mp_unlocks", false },
	{ "mp_weapons", false },
	{ "mrsphilips1", false },
	{ "mrsphilips2", false },
	{ "murdermystery", false },
	{ "navmeshtest", false },
	{ "net_bot_brain", false },
	{ "net_bot_simplebrain", false },
	{ "net_cloud_mission_loader", false },
	{ "net_combat_soaktest", false },
	{ "net_jacking_soaktest", false },
	{ "net_rank_tunable_loader", false },
	{ "net_session_soaktest", false },
	{ "net_tunable_check", false },
	{ "nigel1", false },
	{ "nigel1a", false },
	{ "nigel1b", false },
	{ "nigel1c", false },
	{ "nigel1d", false },
	{ "nigel2", false },
	{ "nigel3", false },
	{ "nodeviewer", false },
	{ "ob_abatdoor", false },
	{ "ob_abattoircut", false },
	{ "ob_airdancer", false },
	{ "ob_bong", false },
	{ "ob_cashregister", false },
	{ "ob_drinking_shots", false },
	{ "ob_foundry_cauldron", false },
	{ "ob_franklin_beer", false },
	{ "ob_franklin_tv", false },
	{ "ob_franklin_wine", false },
	{ "ob_huffing_gas", false },
	{ "ob_mp_bed_high", false },
	{ "ob_mp_bed_low", false },
	{ "ob_mp_bed_med", false },
	{ "ob_mp_shower_med", false },
	{ "ob_mp_stripper", false },
	{ "ob_mr_raspberry_jam", false },
	{ "ob_poledancer", false },
	{ "ob_sofa_franklin", false },
	{ "ob_sofa_michael", false },
	{ "ob_telescope", false },
	{ "ob_tv", false },
	{ "ob_vend1", false },
	{ "ob_vend2", false },
	{ "ob_wheatgrass", false },
	{ "offroad_races", false },
	{ "omega1", false },
	{ "omega2", false },
	{ "paparazzo1", false },
	{ "paparazzo2", false },
	{ "paparazzo3", false },
	{ "paparazzo3a", false },
	{ "paparazzo3b", false },
	{ "paparazzo4", false },
	{ "paradise", false },
	{ "paradise2", false },
	{ "pausemenu", true },
	{ "pausemenu_example", true },
	{ "pausemenu_map", true },
	{ "pausemenu_multiplayer", true },
	{ "pausemenu_sp_repeat", true },
	{ "pb_busker", false },
	{ "pb_homeless", false },
	{ "pb_preacher", false },
	{ "pb_prostitute", false },
	{ "photographymonkey", false },
	{ "photographywildlife", false },
	{ "physics_perf_test", false },
	{ "physics_perf_test_launcher", false },
	{ "pickuptest", false },
	{ "pickupvehicles", true },
	{ "pickup_controller", false },
	{ "pilot_school", false },
	{ "pilot_school_mp", false },
	{ "pi_menu", false },
	{ "placeholdermission", false },
	{ "placementtest", false },
	{ "planewarptest", false },
	{ "player_controller", false },
	{ "player_controller_b", false },
	{ "player_scene_ft_franklin1", false },
	{ "player_scene_f_lamgraff", false },
	{ "player_scene_f_lamtaunt", false },
	{ "player_scene_f_taxi", false },
	{ "player_scene_mf_traffic", false },
	{ "player_scene_m_cinema", false },
	{ "player_scene_m_fbi2", false },
	{ "player_scene_m_kids", false },
	{ "player_scene_m_shopping", false },
	{ "player_scene_t_bbfight", false },
	{ "player_scene_t_chasecar", false },
	{ "player_scene_t_insult", false },
	{ "player_scene_t_park", false },
	{ "player_scene_t_tie", false },
	{ "player_timetable_scene", false },
	{ "playthrough_builder", false },
	{ "pm_defend", false },
	{ "pm_delivery", false },
	{ "pm_gang_attack", false },
	{ "pm_plane_promotion", false },
	{ "pm_recover_stolen", false },
	{ "postkilled_bailbond2", false },
	{ "postrc_barry1and2", false },
	{ "postrc_barry4", false },
	{ "postrc_epsilon4", false },
	{ "postrc_nigel3", false },
	{ "profiler_registration", false },
	{ "prologue1", false },
	{ "prop_drop", false },
	{ "racetest", false },
	{ "rampage1", false },
	{ "rampage2", false },
	{ "rampage3", false },
	{ "rampage4", false },
	{ "rampage5", false },
	{ "rampage_controller", false },
	{ "randomchar_controller", false },
	{ "range_modern", false },
	{ "range_modern_mp", false },
	{ "replay_controller", false },
	{ "rerecord_recording", false },
	{ "respawn_controller", false },
	{ "restrictedareas", false },
	{ "re_abandonedcar", false },
	{ "re_accident", false },
	{ "re_armybase", false },
	{ "re_arrests", false },
	{ "re_atmrobbery", false },
	{ "re_bikethief", false },
	{ "re_border", false },
	{ "re_burials", false },
	{ "re_bus_tours", false },
	{ "re_cartheft", false },
	{ "re_chasethieves", false },
	{ "re_crashrescue", false },
	{ "re_cultshootout", false },
	{ "re_dealgonewrong", false },
	{ "re_domestic", false },
	{ "re_drunkdriver", false },
	{ "re_duel", false },
	{ "re_gangfight", false },
	{ "re_gang_intimidation", false },
	{ "re_getaway_driver", false },
	{ "re_hitch_lift", false },
	{ "re_homeland_security", false },
	{ "re_lossantosintl", false },
	{ "re_lured", false },
	{ "re_monkey", false },
	{ "re_mountdance", false },
	{ "re_muggings", false },
	{ "re_paparazzi", false },
	{ "re_prison", false },
	{ "re_prisonerlift", false },
	{ "re_prisonvanbreak", false },
	{ "re_rescuehostage", false },
	{ "re_seaplane", false },
	{ "re_securityvan", false },
	{ "re_shoprobbery", false },
	{ "re_snatched", false },
	{ "re_stag_do", false },
	{ "re_yetarian", false },
	{ "rollercoaster", false },
	{ "rural_bank_heist", false },
	{ "rural_bank_prep1", false },
	{ "rural_bank_setup", false },
	{ "savegame_bed", false },
	{ "save_anywhere", false },
	{ "scaleformgraphictest", false },
	{ "scaleformminigametest", false },
	{ "scaleformprofiling", false },
	{ "scaleformtest", false },
	{ "scene_builder", false },
	{ "sclub_front_bouncer", false },
	{ "scripted_cam_editor", false },
	{ "scriptplayground", false },
	{ "scripttest1", false },
	{ "scripttest2", false },
	{ "scripttest3", false },
	{ "scripttest4", false },
	{ "script_metrics", false },
	{ "sctv", false },
	{ "sc_lb_global_block", false },
	{ "selector", false },
	{ "selector_example", false },
	{ "selling_short_1", false },
	{ "selling_short_2", false },
	{ "shooting_camera", false },
	{ "shoprobberies", false },
	{ "shop_controller", false },
	{ "shot_bikejump", false },
	{ "shrinkletter", false },
	{ "sh_intro_f_hills", false },
	{ "sh_intro_m_home", false },
	{ "smoketest", false },
	{ "social_controller", false },
	{ "solomon1", false },
	{ "solomon2", false },
	{ "solomon3", false },
	{ "spaceshipparts", false },
	{ "spawn_activities", false },
	{ "speech_reverb_tracker", false },
	{ "spmc_instancer", false },
	{ "spmc_preloader", false },
	{ "sp_dlc_registration", false },
	{ "sp_editor_mission_instance", false },
	{ "sp_menuped", false },
	{ "sp_pilotschool_reg", false },
	{ "standard_global_init", false },
	{ "standard_global_reg", false },
	{ "startup", false },
	{ "startup_install", false },
	{ "startup_locationtest", false },
	{ "startup_positioning", false },
	{ "startup_smoketest", false },
	{ "stats_controller", false },
	{ "stock_controller", false },
	{ "streaming", false },
	{ "stripclub", false },
	{ "stripclub_drinking", false },
	{ "stripclub_mp", false },
	{ "stripperhome", false },
	{ "stunt_plane_races", false },
	{ "tasklist_1", false },
	{ "tattoo_shop", false },
	{ "taxilauncher", false },
	{ "taxiservice", false },
	{ "taxitutorial", false },
	{ "taxi_clowncar", false },
	{ "taxi_cutyouin", false },
	{ "taxi_deadline", false },
	{ "taxi_followcar", false },
	{ "taxi_gotyounow", false },
	{ "taxi_gotyourback", false },
	{ "taxi_needexcitement", false },
	{ "taxi_procedural", false },
	{ "taxi_takeiteasy", false },
	{ "taxi_taketobest", false },
	{ "tempalpha", false },
	{ "temptest", false },
	{ "tennis", false },
	{ "tennis_ambient", false },
	{ "tennis_family", false },
	{ "tennis_network_mp", false },
	{ "test_startup", false },
	{ "thelastone", false },
	{ "timershud", true },
	{ "title_update_registration", false },
	{ "tonya1", false },
	{ "tonya2", false },
	{ "tonya3", false },
	{ "tonya4", false },
	{ "tonya5", false },
	{ "towing", false },
	{ "traffickingsettings", false },
	{ "traffickingteleport", false },
	{ "traffick_air", false },
	{ "traffick_ground", false },
	{ "train_create_widget", false },
	{ "train_tester", false },
	{ "trevor1", false },
	{ "trevor2", false },
	{ "trevor3", false },
	{ "trevor4", false },
	{ "triathlonsp", false },
	{ "tunables_registration", false },
	{ "tuneables_processing", false },
	{ "ufo", false },
	{ "ugc_global_registration", false },
	{ "underwaterpickups", false },
	{ "utvc", false },
	{ "vehicle_ai_test", false },
	{ "vehicle_force_widget", false },
	{ "vehicle_gen_controller", false },
	{ "vehicle_plate", false },
	{ "veh_play_widget", false },
	{ "walking_ped", false },
	{ "wardrobe_mp", false },
	{ "wardrobe_sp", false },
	{ "weapon_audio_widget", false },
	{ "wp_partyboombox", false },
	{ "xml_menus", false },
	{ "yoga", false }
};

typedef void(*g_origFrontend_)(void*, void*, void*);
static g_origFrontend_ g_origFrontend;

void Initialize()
{
#ifdef _DEBUG
	AllocConsole();
	SetConsoleTitle("Grand Theft Auto: Orange");
	FILE * unused = NULL;
	freopen_s(&unused, "CONOUT$", "w", stdout);
	freopen_s(&unused, "CONOUT$", "w", stderr);
#endif
}

static bool scriptsDisabled = false;

bool IsAnyScriptLoaded()
{
	for (int i = 0; i < 748; i++) 
		if (CGlobals::Get().HasScriptLoaded(scriptnames[i].name))
			return true;
	return false;
}

void DisableScripts()
{
	for (int i = 0; i < 748; i++) {
		if (!scriptnames[i].enable) {
			CGlobals::Get().ForceCleanupForAllThreadsWithThisName(scriptnames[i].name, 8);
			CGlobals::Get().TerminateAllScriptsWithThisName(scriptnames[i].name);
		}
	}
}

LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	ScriptManager::WndProc(hwnd, uMsg, wParam, lParam);
	ImGui_ImplDX11_WndProcHandler(hwnd, uMsg, wParam, lParam);
	//log_debug << "WndProc: " << hwnd << " " << uMsg << " " << wParam << " " << lParam << std::endl;
	return CallWindowProc(CGlobals::Get().gtaWndProc, hwnd, uMsg, wParam, lParam);
}

void OnGameStateChange(int gameState)
{
	switch (gameState)
	{
	case GameStateIntro:
		break;
	case GameStateLicenseShit:
		break;
	case GameStatePlaying:
	{
		if (!ScriptEngine::Initialize())
			log_error << "Failed to initialize ScriptEngine" << std::endl;
		if (CGlobals::Get().d3dloaded)
			D3DHook::HookD3D11();
		CChat::Get()->RegisterCommandProcessor(CommandProcessor);

		log_info << "Game ready" << std::endl;
		CGlobals::Get().gtaWndProc = (WNDPROC)SetWindowLongPtr(CGlobals::Get().gtaHwnd, GWLP_WNDPROC, (LONG_PTR)WndProc);
		if (CGlobals::Get().gtaWndProc == NULL)
			log_error << "Failed to attach input hook" << std::endl;
		else
			log_info << "Input hook attached: WndProc 0x" << std::hex << (DWORD_PTR)CGlobals::Get().gtaWndProc << std::endl;
		ScriptEngine::CreateThread(&g_ScriptManagerThread);
		CScript::RunAll();

		SyncTree::Init();
		log_debug << "CPlayerSyncTree: 0x" << std::hex << SyncTree::GetPlayerSyncTree() << std::endl;

		//typedef void(*InitNetStuff_t)();
		//InitNetStuff_t InitNetStuff = (InitNetStuff_t)(0x140F891E0);// CMemory::Find("48 89 5C 24 08 57 48 83 EC 40 33 FF 40 38 3D ? ? ? ?")();
		//InitNetStuff();

		(CMemory::Find("48 89 45 D7 48 8D 45 B7 48 89 5D B7 48 89 45 DF 4C 8D 45 D7 EB ?") + 35).nop(9);
		break;
	}
	case GameStateMainMenu:
		if (!initialized)
		{
			Initialize();
			initialized = true;
		}
		break;
	}
}

static bool gameStateChange_(int gameState)
{
	OnGameStateChange(gameState);
	CGlobals::Get().currentGameState = gameState;
	return g_gameStateChange();
}

static bool OnLookAlive()
{
	static bool HUDInited = false;
	if (!HUDInited)
	{
		HUDInit();
		HUDInited = true;
	}
	if (!scriptsDisabled && IsAnyScriptLoaded())
	{
		DisableScripts();
		CGlobals::Get().ShutdownLoadingScreen();
		CGlobals::Get().DoScreenFadeIn(0);
		scriptsDisabled = true;
	}
	CEvent::Trigger("onGameFrame");
	return g_origLookAlive();
}

class CEventBeforeLoaded :
	public CEvent
{
	std::string Type()
	{
		return "onBeforeLoaded";
	}
	bool Action()
	{
		UpdateSplash("Hooking launcher", 0.21);
		// ignore launcher requirement
		auto mem = CMemory::Find("E8 ? ? ? ? 84 C0 75 ? B2 01 B9 2F A9 C2 F4");
		mem.put(0xEB90909090909090);
		if (CGlobals::Get().isSteam)
		{
			mem = CMemory::Find("FF 15 ? ? ? ? 84 C0 74 0C B2 01 B9 91 32 25 31 E8");
			mem.nop(6);
			(mem + 2).put(0xEBi8);
		}
		/**((DWORD*)0x142BC84A0) = 0;
		CMemory::Find("83 3D 21 FC 8C 01 00").nop(19);*/
		UpdateSplash("Searching patterns.", 0.22);

		mem = CMemory::Find("48 85 C9 0F 84 ? 00 00 00 48 8D 55 A7 E8");
		auto mem2 = mem + 13;
		mem2.put(0x01B0i16);
		mem2.nop(3);

		UpdateSplash("Searching patterns..", 0.23);
		mem = CMemory::Find("8D 4A 03 E8 ? ? ? ? E8 ? ? ? ? 84 C0 75 1E");
		(mem + 2).put(0x08i8);

		UpdateSplash("Searching patterns...", 0.24);
		mem = CMemory::Find("A8 FC 75 06 80 7F 36 04");
		(mem - 74).retn();

		UpdateSplash("Searching patterns", 0.25);
		mem = CMemory::Find("E8 ? ? ? ? 8B CB 40 88 2D ? ? ? ?");
		mem.nop(5);

		UpdateSplash("Searching patterns.", 0.26);
		mem = CMemory::Find("48 83 EC 28 85 D2 78 71 75 0F");
		UpdateSplash("Searching patterns..", 0.27);
		mem2 = CMemory::Find("48 83 EC 28 B9 ? ? ? ? E8 ? ? ? ? B9 ? ? ? ? E8 ? ? ? ? B1 01");
		(mem + 0x3B).put(DWORD(mem2.getFunc() - mem.getFunc() - 0x3F));

		UpdateSplash("Searching patterns...", 0.28);
		mem = CMemory::Find("48 89 5C 24 ? 57 48 83 EC 20 8B F9 8B DA");
		mem.retn();

		UpdateSplash("Searching patterns", 0.29);
		auto unusedMem = CMemory::Find("48 89 5C 24 08 57 48 83 EC 20 48 8B 05 ? ? ? ? 33 DB 48 85 C0 74 39");
		auto callToMem = unusedMem();
		unusedMem.farJmp(OnLookAlive);
		UpdateSplash("Searching patterns.", 0.30);
		auto lookFrame = (CMemory::Find("48 81 EC 60 01 00 00 E8 ? ? ? ? 33 F6 48 8D") + 7);
		auto lookMem = lookFrame();
		g_origLookAlive = lookFrame.get_call<LookAlive>();
		(lookFrame + 1).put(DWORD(callToMem - lookMem - 5));

		UpdateSplash("Searching patterns..", 0.31);
		mem = CMemory::Find("45 33 F6 41 8D 56 27 44 89") - 0x23;
		HUDInit = InitHUD(mem.get<void>(0));

		UpdateSplash("Searching patterns...", 0.32);
		mem = CMemory::Find("E8 ? ? ? ? C6 05 ? ? ? ? ? EB 24"); //Esc freeze
		mem.nop(5);

		UpdateSplash("Searching patterns", 0.33);
		mem = CMemory::Find("75 05 0F 28 E3 EB 03"); //UI Wheel slowmo
		mem.nop(2);
		UpdateSplash("Searching patterns.", 0.34);
		mem = CMemory::Find("75 0A F3 0F 10 0D ? ? ? ? EB 08 F3 0F 10 0D ? ? ? ? E8 ? ? ? ?"); //UI Wheel slowmo 2
		mem.nop(2);

		UpdateSplash("Searching patterns..", 0.35);
		mem = CMemory::Find("85 C0 78 F1 EB 10"); //Show cursor
		mem.nop(4);
		UpdateSplash("Searching patterns...", 0.36);
		mem = CMemory::Find("85 C0 79 F4"); //Show cursor
		mem.nop(4);

		UpdateSplash("Searching patterns", 0.37);
		mem = CMemory::Find("40 53 48 83 EC 20 48 83 3D ? ? ? ? ? 0F 85 ? ? ? ? 8B 05 ? ? ? ? 4C 8D 44 24 ? 48 8D 54 24 ? 48 8D 0D ? ? ? ? 89 44 "
			"24 30 E8 ? ? ? ? 48 63 18 83 FB FF 0F 84 ? ? ? ?"); //Rockstar loading logo
		mem.retn();

		UpdateSplash("Searching patterns.", 0.38);
		mem = CMemory::Find("48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 45 8B E0"); //Tooltips
		mem.retn();

		UpdateSplash("Searching patterns..", 0.39);
		mem = CMemory::Find("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 33 ED 48 8B D9 40 38 69 1C"); //Social club news
		mem.retn();

		UpdateSplash("Searching patterns...", 0.40);
		mem = CMemory::Find("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 30 8B 05 ? ? ? ? 8B B9 ? ? ? ?"); //Disable wanted generation
		mem.retn();
		
		UpdateSplash("Searching patterns.", 0.41);
		mem = CMemory::Find("0F 84 ? ? ? ? 44 39 87 ? ? ? ? 0F 8E ? ? ? ?"); //Disable wanted generation 2
		mem.put(0xE990i16);

		UpdateSplash("Searching patterns..", 0.42);
		mem = CMemory::Find("E8 ? ? ? ? 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 85 C9"); //Intentional crash
		mem.nop(5);

		UpdateSplash("Searching patterns...", 0.43);
		mem = CMemory::Find("E8 ? ? ? ? 4C 8B 08 4C 8D 45 ? 48 8D 55 ? 48 8B C8 41 FF 51 60"); //RASH_LOAD_MODELS_TOO_QUICKLY
		mem.nop(23);

		UpdateSplash("Searching patterns", 0.44);
		mem = CMemory::Find("48 83 EC 28 E8 ? ? ? ? 48 8B ? ? ? ? ? 4C 8D ? ? ? ? ? 4C 8D ? ? ? ? ? BA 03 00 00 00 E8 ? ? ? ?"); //REATE_NETWORK_EVENT_BINDINGS
		mem.retn();

		UpdateSplash("Searching patterns.", 0.45);
		mem = CMemory::Find("40 53 48 83 EC 20 33 DB 8B CB E8 ? ? ? ? 84 C0 75 2C"); //OAD_NEW_GAME
		mem.retn();

		UpdateSplash("Searching patterns..", 0.46);
		mem = CMemory::Find("33 C0 0F 57 C0 C7 05 ? ? ? ? ? ? ? ?"); //ESET_VEHICLE_DENSITY_LAST_FRAME
		mem.retn();

		UpdateSplash("Searching patterns...", 0.47);
		auto varVehicleDensity = CMemory::Find("C7 05 ? ? ? ? ? ? ? ? C7 05 ? ? ? ? ? ? ? ? 88 05 ? ? ? ? F3 0F 11 05 ? ? ? ?").getOffset(2); //AR_VEHICLE_DENSITY
		*(uint64_t*)varVehicleDensity = 0;

		UpdateSplash("Searching patterns", 0.48);
		mem = CMemory::Find("40 53 48 83 EC 20 48 8B D9 48 83 C1 10 E8 ? ? ? ? 48 8B CB 8B D0"); //ET_CLOCK_FORWARD_AFTER_DEATH
		mem.retn();

		UpdateSplash("Searching patterns.", 0.49);
		mem = CMemory::Find("E8 ? ? ? ? 41 B8 ? ? ? ? 8B D0 89 05 ? ? ? ? 41 8D 48 FC"); //ISABLE_NORTH_BLIP
		mem.nop(46);

		//mem = CMemory::Find("83 B9 ? ? ? ? ? 74 24 84 D2"); //ISABLE_AUTOMATIC_ENGINE_STOP
		//mem.retn();

		UpdateSplash("Searching patterns..", 0.50);
		mem = CMemory::Find("48 8B C4 48 89 58 08 57 48 83 EC 60 0F 29 70 E8 0F 29 78 D8 44 0F 29 40 ? 48 8B D9 44 0F 29 48 ?"); //ISABLE_VEHICLE_RESET_AT_SET_POSITION
		mem.retn();
		
		UpdateSplash("Searching patterns...", 0.51);
		mem = CMemory::Find("48 89 5C 24 ? 57 48 83 EC 20 8A 81 ? ? ? ? 8B FA"); //ISABLE_LOADING_MP_DLC_CONTENT
		mem.retn();
		
		UpdateSplash("Searching patterns", 0.52);
		mem = CMemory::Find("80 3D ? ? ? ? ? 0F 85 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 08"); //UNTIME_EXECUTABLE_IMPORTS_CHECK
		mem.retn();

		UpdateSplash("Searching patterns.", 0.53);
		mem = CMemory::Find("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 20 E8 ? ? ? ? 45 33 E4"); //ISABLE_POPULATION_VEHICLES_10
		mem.retn();
		
		UpdateSplash("Searching patterns..", 0.54);
		mem = CMemory::Find("48 8B C4 48 89 58 08 F3 0F 11 50 ?"); //ISABLE_POPULATION_VEHICLES_8
		mem.retn();

		UpdateSplash("Searching patterns...", 0.55);
		mem = CMemory::Find("41 FF C0 B8 ? ? ? ? 41 F7 E0"); //ISABLE_POPULATION_VEHICLES_11
		mem.nop(3);

		UpdateSplash("Searching patterns", 0.56);
		mem = CMemory::Find("E8 ? ? ? ? 39 05 ? ? ? ? 7D C5"); //ISABLE_POPULATION_VEHICLES_11
		mem.nop(5);
		
		UpdateSplash("Searching patterns.", 0.57);
		mem = CMemory::Find("48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18 55 41 54 41 55 41 56 41 57 48 8D 68 C8 48 81 EC ? ? ? ? 45 33 F6"); //ISABLE_POPULATION_PEDS_1
		mem.retn();

		UpdateSplash("Searching patterns..", 0.58);
		mem = CMemory::Find("48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 0F 29 70 B8 0F 29 78 A8 44 0F 29 40 ? 44 0F 29 48 ?"); //ISABLE_POPULATION_PEDS_2
		mem.retn();
		
		UpdateSplash("Searching patterns...", 0.59);
		mem = CMemory::Find("C7 05 ? ? ? ? ? ? ? ? C7 05 ? ? ? ? ? ? ? ? 74 05"); //ISABLE_POPULATION_AMBIENT_PEDS
		(mem + 6).put(0x0i32);
		(mem + 16).put(0x0i32);

		UpdateSplash("Searching patterns", 0.60);
		mem = CMemory::Find("F3 0F 10 05 ? ? ? ? 0F 2F C1 72 08"); //ISABLE_POPULATION_PEDS_4
		mem.nop(20);

		UpdateSplash("Searching patterns.", 0.61);
		mem = CMemory::Find("48 89 5C 24 ? 57 48 83 EC 20 48 8B D9 E8 ? ? ? ? 80 A3 ? ? ? ? ? 48 8B BB ? ? ? ?"); //ISABLE_COPS_AND_FIRE_TRUCKS_1
		mem.retn();

		UpdateSplash("Searching patterns..", 0.62);
		mem = CMemory::Find("48 83 EC 28 B8 ? ? ? ? 3B C8"); //ISABLE_COPS_AND_FIRE_TRUCKS_2
		mem.retn();
		
		UpdateSplash("Searching patterns...", 0.63);
		mem = CMemory::Find("40 53 48 83 EC 20 8B 81 ? ? ? ? 48 8B D9 39 81 ? ? ? ?"); //ISABLE_COPS_AND_FIRE_TRUCKS_3
		mem.retn();

		callToMem = unusedMem();
		unusedMem.farJmp(gameStateChange_);
		UpdateSplash("Searching patterns", 0.64);
		auto gameStateChange = CMemory::Find("E8 ? ? ? ? 84 C0 74 1D E8 ? ? ? ? 0F B6 0D ? ? ? ? BA 01 00 00 00 80 38 00"); // GameStateChange
		auto gameStateMem = gameStateChange();
		g_gameStateChange = gameStateChange.get_call<GameStateChange_>();
		(gameStateChange + 1).put(long(callToMem - gameStateMem - 5));

		UpdateSplash("Searching patterns.", 0.65);
		CGlobals::Get().ForceCleanupForAllThreadsWithThisName = (ForceCleanupForAllThreadsWithThisName_)
			CMemory::Find("48 89 5C 24 08 57 48 83 EC 20 8B FA 48 8B D9 E8 ? ? ? ? 41 83 C9 FF")(); //FORCE_CLEANUP_FOR_ALL_THREADS_WITH_THIS_NAME
		UpdateSplash("Searching patterns..", 0.66);
		CGlobals::Get().TerminateAllScriptsWithThisName = (TerminateAllScriptsWithThisName_)
			CMemory::Find("40 53 48 83 EC 20 48 8B D9 E8 ? ? ? ? 48 8B D3 48 8B C8 E8 ? ? ? ? 85 C0 74 08")(); //TerminateAllScriptsWithThisName
		UpdateSplash("Searching patterns...", 0.67);
		CGlobals::Get().ShutdownLoadingScreen = (ShutdownLoadingScreen_)
			CMemory::Find("40 57 48 83 EC 20 8B 05 ? ? ? ? 85 C0 0F 84 ? ? ? ?")(); //ShutdownLoadingScreen
		UpdateSplash("Searching patterns", 0.68);
		CGlobals::Get().DoScreenFadeIn = (DoScreenFadeIn_)
			CMemory::Find("48 83 EC 28 48 8D 54 24 38 C7 44 24 38 00 00 00 FF")(); //DoScreenFadeIn
		UpdateSplash("Searching patterns.", 0.69);
		CGlobals::Get().HasScriptLoaded = (HasScriptLoaded_)
			CMemory::Find("48 83 EC 28 4C 8B C1 48 8D 54 24 38 48 8D 0D ? ? ? ? E8 ? ? ? ? 8B 44 24 38")(); //HasScriptLoaded

		UpdateSplash("Searching patterns..", 0.70);
		CGlobals::Get().canLangChange = (bool*)((uintptr_t)CMemory::Find("C6 05 ? ? ? ? 01 8B 8F A0 04 00 00").getOffset(2) + 1);

		UpdateSplash("Searching patterns...", 0.71);
		CGlobals::Get().InitializeOnline = (InitializeOnline_)CMemory::Find("40 53 48 83 EC 50 80 3D ? ? ? ? ? C6 05 ? ? ? ? ?")();

		UpdateSplash("Searching patterns", 0.72);
		CGlobals::Get().SetMenuState = (SetMenuState_)CMemory::Find("48 83 EC 28 48 8B D1 33 C9 E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8D 54 24 ? 41 B8 ? ? ? ?")();

		UpdateSplash("Searching patterns.", 0.73);
		CMemory::Find("48 83 EC 28 33 D2 E8 ? ? ? ? CC").retn();
		UpdateSplash("Searching patterns..", 0.74);
		CMemory::Find("48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18 4C 89 60 20 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F B7 05 ? ? ? ?").retn();
		//CMemory::Find("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 0F B6 81 ? ? ? ? 48 8D 79 18").retn();
		UpdateSplash("Searching patterns...", 0.75);
		CMemory::Find("80 3D ? ? ? ? ? 74 1B 84 DB 74 10 ? ? ? ? ? ? ? ? ? ? ? ? ? ? EB 39").nop(9);
		UpdateSplash("Searching patterns", 0.76);
		CMemory::Find("48 89 5C 24 ? 57 48 83 EC 40 33 FF 40 38 3D ? ? ? ?").retn();
		UpdateSplash("Searching patterns.", 0.77);
		(CMemory::Find("48 83 64 24 30 00 83 4C 24 28 FF 33 D2 48") - 4).retn();

		UpdateSplash("Searching patterns..", 0.78);
		mem = CMemory::Find("40 8A 35 ? ? ? ? 84 C0 74 05 45 84 FF"); //HECK_MULTIPLAYER_BYTE_DRAW_MAP_FRAME
		mem2 = CMemory(mem);
		mem.nop(7);
		mem2.put(0xB640i16);
		mem2.put(0x01i8);

		UpdateSplash("Searching patterns...", 0.79);
		CGlobals::Get().hudDisabled = (bool*)CMemory::Find("44 88 25 ? ? ? ? 40 88 3D ? ? ? ? 48 8D 05 ? ? ? ? BB ? ? ? ?").getOffset();
		UpdateSplash("Loaded", 1);

		//CMemory::Find("83 3D ? ? ? ? 01 75 5B 48 8D 15 ? ? ? ?").nop(100);
		return true;
	}
} _ev;

