#pragma once
class CRegistry
{
public:
	static bool Read(HKEY hKeyLocation, const char * szLocation, const char * szRow, const char *szBuffer, DWORD dwSize);
	static bool Write(HKEY hKeyLocation, const char * szSubKey, const char * szKey, const char * szData, DWORD dwSize);
};

