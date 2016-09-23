#include "stdafx.h"

bool CRegistry::Read(HKEY hKeyLocation, const char * szLocation, const char * szRow, const char *szBuffer, DWORD dwSize)
{
	HKEY hKey = NULL;

	if (RegOpenKeyEx(hKeyLocation, szLocation, NULL, KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		DWORD dwType = REG_SZ;
		LONG getStatus = RegQueryValueEx(hKey, szRow, NULL, &dwType, (BYTE *)szBuffer, &dwSize);
		RegCloseKey(hKey);
		return (getStatus == ERROR_SUCCESS);
	}
	return false;
}

bool CRegistry::Write(HKEY hKeyLocation, const char * szSubKey, const char * szKey, const char * szData, DWORD dwSize)
{
	HKEY hKey = NULL;
	RegOpenKeyEx(hKeyLocation, szSubKey, NULL, KEY_ALL_ACCESS, &hKey);

	if (!hKey)
	{
		RegCreateKeyEx(hKeyLocation, szSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	}

	if (hKey)
	{
		RegSetValueEx(hKey, szKey, NULL, REG_SZ, (BYTE *)szData, dwSize);
		RegCloseKey(hKey);
		return true;
	}
	return false;
}
