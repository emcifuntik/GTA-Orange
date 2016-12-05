#pragma once
#include <string>

enum GameVersion {
	GAME_VERSION_STEAM = 1,
	GAME_VERSION_SOCIAL = 2,
	GAME_VERSION_RELOADED = 3
};

class Injector
{
public:
	static void Run();
private:
	Injector();
	int FindProcess(std::string procName);
	GameVersion GetGameVersion();
	void WaitUntilGameStarts();
	bool InjectDLL(int processId, std::string dllName);
	std::string GetExecutablePath();
	void WaitForUnpackFinished(int pid);
	~Injector();
};

