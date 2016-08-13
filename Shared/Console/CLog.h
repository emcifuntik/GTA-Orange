#pragma once
#ifndef _IOLOG_
#define _IOLOG_

#ifdef _SERVER
#define LOG_FILE "hs_server.log"
#else
#define LOG_FILE "hs_client.log"
#endif

#define LOG_DEBUG "[Debug] "
#define LOG_ERROR "[Error] "
#define LOG_INFO "[Info] "

class my_ostream
{
public:

	my_ostream() {
		my_fstream = std::ofstream(LOG_FILE, std::ios_base::app);
		my_fstream << std::endl;
	};

	my_ostream& info()
	{
		std::cout << color::lblue << LOG_INFO;
		my_fstream << LOG_INFO;
		return *this;
	}
	my_ostream& debug()
	{
		std::cout << color::lyellow << LOG_DEBUG;
		my_fstream << LOG_DEBUG;
		return *this;
	}
	my_ostream& error()
	{
		std::cout << color::lred << LOG_ERROR;
		my_fstream << LOG_ERROR;
		return *this;
	}
	template<typename T> my_ostream& operator<<(const T& something)
	{
		std::cout << something;
		my_fstream << something;
		return *this;
	}
	typedef std::ostream& (*stream_function)(std::ostream&);
	my_ostream& operator<<(stream_function func)
	{
		func(std::cout);
		func(my_fstream);
		return *this;
	}
private:
	std::ofstream my_fstream;
};

#define log _log()
#define log_info _log().info()
#define log_debug _log().debug()
#define log_error _log().error()
my_ostream& _log();

#endif
