#include "stdafx.h"

CConsole * CConsole::singleInstance = nullptr;

CConsole::CConsole()
{
	hConsoleHandler = GetStdHandle(STD_OUTPUT_HANDLE);
}


CConsole * CConsole::Get()
{
	if (!singleInstance)
		singleInstance = new CConsole();
	return singleInstance;
}

CConsole::~CConsole()
{
}

char * CConsole::Color(WORD color)
{
	SetConsoleTextAttribute(hConsoleHandler, color);
	return "";
}
