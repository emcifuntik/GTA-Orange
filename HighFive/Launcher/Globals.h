#pragma once

typedef void(*ForceCleanupForAllThreadsWithThisName_)(const char * name, int mask);
typedef void(*TerminateAllScriptsWithThisName_)(const char * name);
typedef void(*ShutdownLoadingScreen_)();
typedef void(*DoScreenFadeIn_)(int64_t delay);
typedef bool(*HasScriptLoaded_)(const char * name);
typedef int(*CreateCam_)(const char * name, bool p1);
typedef void(*SetCamCoord_)(int, CVector3 pos);
typedef char(*PointCamAtCoord_)(int, CVector3 pos);
typedef bool(*SetCamActive_)(int cam, bool active);
typedef void(*RenderScriptCams_)(bool render, bool ease, int easeTime, bool p3, bool p4, int a6);
typedef bool(*SetEntityCoords_)(int entity, CVector3 pos, BOOL xAxis, BOOL yAxis, BOOL zAxis, BOOL clearArea);
typedef int(*GetPlayerPed_)();

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
	CreateCam_ CreateCam;
	SetCamCoord_ SetCamCoord;
	PointCamAtCoord_ PointCamAtCoord;
	RenderScriptCams_ RenderScriptCams;
	SetCamActive_ SetCamActive;
	SetEntityCoords_ SetEntityCoords;
	GetPlayerPed_ GetPlayerPed;
};

