#pragma once

typedef void(*ForceCleanupForAllThreadsWithThisName_)(const char * name, int mask);
typedef void(*TerminateAllScriptsWithThisName_)(const char * name);
typedef void(*ShutdownLoadingScreen_)();
typedef void(*DoScreenFadeIn_)(int64_t delay);
typedef bool(*HasScriptLoaded_)(const char * name);

class CGlobals
{
	CGlobals() {}
	static CGlobals * singleInstance;
public:
	static CGlobals& Get()
	{
		if (!singleInstance)
			singleInstance = new CGlobals();
		return *singleInstance;
	}
	LPVOID baseAddr = nullptr;
	std::string highFivePath;
	bool alreadyRunned = false;
	ForceCleanupForAllThreadsWithThisName_ ForceCleanupForAllThreadsWithThisName;
	TerminateAllScriptsWithThisName_ TerminateAllScriptsWithThisName;
	ShutdownLoadingScreen_ ShutdownLoadingScreen;
	DoScreenFadeIn_ DoScreenFadeIn;
	HasScriptLoaded_ HasScriptLoaded;
};

