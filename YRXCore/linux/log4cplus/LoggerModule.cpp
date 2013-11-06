
#include "LoggerModule.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <log4cplus/config.hxx>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>
#include <log4cplus/helpers/socket.h>
//#include <log4cplus/helpers/threads.h>
#include <log4cplus/spi/loggerimpl.h>
#include <log4cplus/spi/loggingevent.h>
#include <stdarg.h>
#include <log4cplus/loggingmacros.h>
LoggerModule::LoggerModule()
{

}

LoggerModule::~LoggerModule()
{
	log4cplus::Logger _logger = log4cplus::Logger::getRoot();
	LOG4CPLUS_INFO(_logger, "Logger System Stop Finish.");
}


#define DO_LOGGER(logLevel, filename, fileline, pFormat, bufSize)\
	log4cplus::Logger _logger = log4cplus::Logger::getRoot();\
	\
	if(_logger.isEnabledFor(logLevel))\
{                \
	va_list args;            \
	va_start(args, pFormat);        \
	TCHAR buf[bufSize] = {0};        \
	vsnprintf(buf, sizeof(buf), pFormat, args);    \
	va_end(args);           \
	_logger.forcedLog(logLevel, buf, filename, fileline); \
}



	void LoggerModule::Debug(const char* filename, const int fileline, const char* pFormat,... )
{
	DO_LOGGER(log4cplus::DEBUG_LOG_LEVEL, filename, fileline, pFormat, 1024);
}
	
	//void DebugW(const char* filename, const int fileline,const wchar_t* pFormat,...  );

	void LoggerModule::Error(const char* filename, const int fileline, const char* pFormat,... )
{

	DO_LOGGER(log4cplus::ERROR_LOG_LEVEL, filename, fileline, pFormat, 256);
}

    void LoggerModule::Fatal(const char* filename, const int fileline, const char* pFormat,... )
{
	DO_LOGGER(log4cplus::FATAL_LOG_LEVEL, filename, fileline, pFormat, 256);
}

	void LoggerModule::Info(const char* filename, const int fileline, const char* pFormat,... )
{
	DO_LOGGER(log4cplus::INFO_LOG_LEVEL, filename, fileline, pFormat, 512);
}

	void LoggerModule::Warn(const char* filename, const int fileline, const char* pFormat,... )
{
	DO_LOGGER(log4cplus::WARN_LOG_LEVEL, filename, fileline, pFormat, 256);
}

	void LoggerModule::Trace(const char* filename, const int fileline, const char* pFormat,... )
{
	DO_LOGGER(log4cplus::TRACE_LOG_LEVEL, filename, fileline, pFormat, 1024);
}





void LoggerModule::StartSystem( const TCHAR* properties_filename )
{
	if (properties_filename==NULL) return;

 	log4cplus::helpers::LogLog::getLogLog()->setInternalDebugging(false);
 	log4cplus::PropertyConfigurator::doConfigure(properties_filename);
 	log4cplus::Logger _logger = log4cplus::Logger::getRoot();
 	LOG4CPLUS_INFO(_logger, "Logger System Start Finish.");
}

void LoggerModule::StopSystem()
{

}
