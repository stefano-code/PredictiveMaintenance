#include "os/CriticalSectionLock.hpp"
#include "debug/Logger.hpp"

#include "log_config.h"
#include <jni.h>


const int MAX_SIZE_DEBUG_MESSAGE = 5000;
const int ELAPSED_TIME_SIZE = 25;


Logger& Log = Logger::GetInstance();

Logger::Logger()
{
	enable = true;
}


Logger& Logger::GetInstance()
{
	static Logger instance;
	return instance;
}


Logger& Logger::Append(const char* str)
{
	CriticalSectionLock l( &lock ) ;

	if (enable)
		msg.append(str);

	return *this;
}

Logger& Logger::Append(const char* s, int n)
{
	CriticalSectionLock l( &lock ) ;

	if (enable) {
		std::string ss = Format(s, n);
		msg.append(ss);
	}

	return *this;
}

Logger& Logger::Append(const char* s, float v)
{
	CriticalSectionLock l( &lock ) ;

	if (enable) {
		std::string ss = Format(s, v);
		msg.append(ss);
	}

	return *this;
}

void Logger::EndLine()
{
	CriticalSectionLock l( &lock ) ;

	if (!enable)
		return;

	LOGE( "%s", msg.c_str() );

	msg.clear();
}

template <typename T>
std::string Logger::Format(const char* format, T p)
{
	char tmp[MAX_SIZE_DEBUG_MESSAGE];
	snprintf(tmp, MAX_SIZE_DEBUG_MESSAGE, format, p);
	std::string ret(tmp);
	return ret;
}
