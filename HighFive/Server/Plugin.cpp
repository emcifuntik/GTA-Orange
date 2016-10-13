#include "stdafx.h"

//just for 3d3 cuz its uniplattform!
#include <sys/types.h>
#include <sys/stat.h>

struct stat info;
std::map<std::string, OnResourceLoad_> Plugin::resourceTypes;
std::vector<OnPlayerConnect_> Plugin::playerConnects;
std::vector<OnServerCommand_> Plugin::serverCommands;
std::vector<OnPlayerDisconnect_> Plugin::playerDisconnects;
std::vector<OnPlayerUpdate_> Plugin::playerUpdates;
std::vector<OnPlayerCommand_> Plugin::playerCommands;
std::vector<OnPlayerText_> Plugin::playerTexts;

const std::string GetRunningExecutableFolder() {

	char fileName[MAX_PATH];
	GetModuleFileNameA(NULL, fileName, MAX_PATH);

	std::string currentPath = fileName;
	return currentPath.substr(0, currentPath.find_last_of("\\"));
}

void Plugin::LoadPlugins()
{
	const std::string currentFolder = GetRunningExecutableFolder();
	const std::string pfolder = currentFolder + "\\modules";
	const std::string searchfolder = pfolder + "\\*.dll";

	WIN32_FIND_DATAA filedat;
	HANDLE fileh = FindFirstFileA(searchfolder.c_str(), &filedat);

	if (stat(pfolder.c_str(), &info) != 0)
	{
		std::stringstream ss;
		ss << "No Modules folder found ( " << pfolder << " )" << std::endl;
		log_info << ss.str()  << std::endl;
	}
	if (fileh != INVALID_HANDLE_VALUE)
	{
		do {
			const std::string ppath = pfolder + "\\" + filedat.cFileName;
			HMODULE module = LoadLibraryA(ppath.c_str());
			if (!module)
			{
				std::stringstream ss;
				ss << "Failed to load \"" << filedat.cFileName << "\" => 0x" << std::hex << module << std::dec << std::endl;
				log_error << ss.str() << std::endl;
			}
			else
			{
				typedef bool(*Validate_)(API * api);
				Validate_ validate = (Validate_)GetProcAddress(module, "Validate");
				if (!validate)
				{
					std::stringstream ss;
					ss << "Failed to load \"" << filedat.cFileName << "\" => 0x" << std::hex << module << std::dec << ". Didn\'t pass validation" << std::endl;
					log_error << ss.str() << std::endl;
				}
				else
				{
					bool moduleLoaded = validate(API::Get());
					if (moduleLoaded)
					{
						typedef void(*onModuleInit_)();
						onModuleInit_ OnModuleInit = (onModuleInit_)GetProcAddress(module, "OnModuleInit");
						OnModuleInit();

						OnPlayerConnect_ onPlayerConnect = (OnPlayerConnect_)			GetProcAddress(module, "OnPlayerConnect");
						OnServerCommand_ onServerCommand = (OnServerCommand_)			GetProcAddress(module, "OnServerCommand");
						OnPlayerDisconnect_ onPlayerDisconnect = (OnPlayerDisconnect_)	GetProcAddress(module, "OnPlayerDisconnect");
						OnPlayerUpdate_ onPlayerUpdate = (OnPlayerUpdate_)				GetProcAddress(module, "OnPlayerUpdate");
						OnPlayerCommand_ onPlayerCommand = (OnPlayerCommand_)			GetProcAddress(module, "OnPlayerCommand");
						OnPlayerText_ onPlayerText = (OnPlayerText_)					GetProcAddress(module, "OnPlayerText");

						if (onPlayerConnect) playerConnects.push_back(onPlayerConnect);
						if (onServerCommand) serverCommands.push_back(onServerCommand);
						if (onPlayerDisconnect) playerDisconnects.push_back(onPlayerDisconnect);
						if (onPlayerUpdate) playerUpdates.push_back(onPlayerUpdate);
						if (onPlayerCommand) playerCommands.push_back(onPlayerCommand);
						if (onPlayerText) playerTexts.push_back(onPlayerText);

						OnResourceTypeRegister_ onResourceTypeRegister = (OnResourceTypeRegister_)GetProcAddress(module, "OnResourceTypeRegister");
						OnResourceLoad_ loadResource = (OnResourceLoad_)GetProcAddress(module, "OnResourceLoad");

						if (onResourceTypeRegister&&loadResource) resourceTypes[std::string(onResourceTypeRegister())] = loadResource;
					}
				}
			}
		} while (FindNextFileA(fileh, &filedat));
		FindClose(fileh);
		
		for each(auto resource in CConfig::Get()->Resources)
		{
			tinyxml2::XMLDocument doc;
			char path[128];
			sprintf_s(path, 128, "resources\\%s\\resource.xml", resource.c_str());
			if (doc.LoadFile(path) != tinyxml2::XML_SUCCESS) log << "Error loading resource.xml for resource " << resource << std::endl;
			else {
				tinyxml2::XMLElement * root = doc.FirstChildElement("resource");
				tinyxml2::XMLElement * typeNode = root->FirstChildElement("type");

				if (resourceTypes[typeNode->GetText()]) {
					resourceTypes[typeNode->GetText()](resource.c_str());
				}
				else log << "Unknown resource type: " << typeNode->GetText() << std::endl;
			}
		}
	}
}

bool Plugin::PlayerConnect(long playerid)
{
	for each (auto func in playerConnects)
		if (!func(playerid))
			return false;
	return true;
}

bool Plugin::ServerCommand(std::string command)
{
	for each (auto func in serverCommands)
		if (!func(command))
			return false;
	return true;
}

bool Plugin::PlayerDisconnect(long playerid, int reason)
{
	for each (auto func in playerDisconnects)
		if (!func(playerid, reason))
			return false;
	return true;
}

bool Plugin::PlayerUpdate(long playerid)
{
	for each (auto func in playerUpdates)
		if (!func(playerid))
			return false;
	return true;
}

bool Plugin::PlayerCommand(long playerid, const char * command)
{
	for each (auto func in playerCommands)
		if (!func(playerid, command))
			return false;
	return true;
}

bool Plugin::PlayerText(long playerid, const char * text)
{
	for each (auto func in playerTexts)
		if (!func(playerid, text))
			return false;
	return true;
}
