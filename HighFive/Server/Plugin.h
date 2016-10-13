#pragma once

typedef bool(*OnPlayerConnect_)(long playerid);
typedef bool(*OnServerCommand_)(std::string command);
typedef bool(*OnPlayerDisconnect_)(long playerid, int reason);
typedef bool(*OnPlayerUpdate_)(long playerid);
typedef bool(*OnPlayerCommand_)(long playerid, const char * command);
typedef bool(*OnPlayerText_)(long playerid, const char * text);
typedef const char*(*OnResourceTypeRegister_)();
typedef bool(*OnResourceLoad_)(const char*);

class Plugin {
	static std::map<std::string, OnResourceLoad_> resourceTypes;
	static std::vector<OnPlayerConnect_> playerConnects;
	static std::vector<OnServerCommand_> serverCommands;
	static std::vector<OnPlayerDisconnect_> playerDisconnects;
	static std::vector<OnPlayerUpdate_> playerUpdates;
	static std::vector<OnPlayerCommand_> playerCommands;
	static std::vector<OnPlayerText_> playerTexts;
public:
	static void LoadPlugins();
	static bool PlayerConnect(long playerid);
	static bool ServerCommand(std::string command);
	static bool PlayerDisconnect(long playerid, int reason);
	static bool PlayerUpdate(long playerid);
	static bool PlayerCommand(long playerid, const char * command);
	static bool PlayerText(long playerid, const char * text);
};
