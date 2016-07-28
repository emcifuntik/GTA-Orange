#pragma once
#ifndef _IOLOG_
#define _IOLOG_
class my_ostream
{
public:
	my_ostream() {
		my_fstream = std::ofstream("hf_server.log", std::ios_base::app);
		my_fstream << std::endl;
	}; // check if opening file succeeded!!
												   // for regular output of variables and stuff
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
my_ostream& _log();
#endif
