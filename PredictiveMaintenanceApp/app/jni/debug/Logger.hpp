#ifndef LOGGER_HPP
#define	LOGGER_HPP

#include <string>
#include "os/Semaphore.hpp"

class Logger
{
public:
	static Logger& GetInstance();
	Logger& Append(const char* str);
	Logger& Append(const char* format, int n);
	Logger& Append(const char* format, float v);
	void EndLine();
	bool enable;

private:
	Logger() ;
	SemaphoreBase lock;
	std::string msg;
	template <typename T>
	std::string Format(const char* format, T p);
};


class Schwarz
{
public:
	Schwarz(){ Logger::GetInstance().EndLine(); }
	~Schwarz(){}
};

extern Logger& Log;
static Schwarz logger_init;



#endif	// LOGGER_HPP

