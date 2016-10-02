#pragma once

#include "stdafx.h"
#include "PeIMG.h"

using namespace Utility;

const std::string GetRunningExecutableFolder() {

	char fileName[MAX_PATH];
	GetModuleFileNameA(NULL, fileName, MAX_PATH);

	std::string currentPath = fileName;
	return currentPath.substr(0, currentPath.find_last_of("\\"));
}

void LoadPlugins()
{
	const std::string currentFolder = GetRunningExecutableFolder();
	const std::string pfolder = currentFolder + "\\plugins";
	const std::string searchfolder = pfolder + "\\*.dll";

	WIN32_FIND_DATAA filedat;
	HANDLE fileh = FindFirstFileA(searchfolder.c_str(), &filedat);
	if (fileh != INVALID_HANDLE_VALUE)
	{
		do {
			const std::string ppath = pfolder + "\\" + filedat.cFileName;
			HMODULE module = LoadLibraryA(ppath.c_str());
			if (!module)
			{
				char buf[30];
				snprintf(buf, sizeof(buf), "\t Failed to Load \"%s\" => 0x%p", filedat.cFileName, module);
				MessageBoxA(NULL, buf, "Orange MP server", MB_OK | MB_ICONWARNING);
			}
		} while (FindNextFileA(fileh, &filedat));

		FindClose(fileh);
		//loaded image

	}


}