#pragma once
class CConsole
{
	static CConsole * singleInstance;
	HANDLE hConsoleHandler;
	CConsole();
public:
	static CConsole * Get();
	~CConsole();
	char * Color(WORD color);
};

