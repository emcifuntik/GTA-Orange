#include "stdafx.h"

my_ostream log_stream;

my_ostream& _log()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, CConfig::Get()->LogTimeFormat.c_str(), timeinfo);
	log_stream << color::lwhite << buffer << " " << color::white;
	return log_stream;
}
