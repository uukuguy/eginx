#include "yrx_logmodule.h"
#include "LoggerModule.h"
#include <stdarg.h>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#define BUF_SIZE 260
void yrx_logInitLog4cplus( const char* logConfig )
{
    g_Logger.StartSystem( logConfig );
    //g_Logger.StartSystem("log4cplus.Client_properties");
}

#define DO_LOGGERWrapper(buf,filename, fileline, pFormat, bufSize){\
	va_list args;            \
	va_start(args, pFormat);        \
	vsnprintf(buf, bufSize, pFormat, args);    \
	va_end(args);           \
}

void yrx_logDebug(const char* filename, const int fileline, const char* pFormat,... )
{
    char szbuf[BUF_SIZE]={0};
    DO_LOGGERWrapper(szbuf,filename,fileline,pFormat,BUF_SIZE);
    g_Logger.Debug(filename,fileline,szbuf);
}	

void yrx_logError(const char* filename, const int fileline, const char* pFormat,... )
{
    char szbuf[BUF_SIZE]={0};
    DO_LOGGERWrapper(szbuf,filename,fileline,pFormat,BUF_SIZE);
    g_Logger.Error(filename,fileline,szbuf);
}

void yrx_logFatal(const char* filename, const int fileline, const char* pFormat,... )
{
    char szbuf[BUF_SIZE]={0};
    DO_LOGGERWrapper(szbuf,filename,fileline,pFormat,BUF_SIZE);
    g_Logger.Fatal(filename,fileline,szbuf);
}

void yrx_logInfo(const char* filename, const int fileline, const char* pFormat,... )
{
    char szbuf[BUF_SIZE]={0};
    DO_LOGGERWrapper(szbuf,filename,fileline,pFormat,BUF_SIZE);
    g_Logger.Info(filename,fileline,szbuf);
}

void yrx_logWarn(const char* filename, const int fileline, const char* pFormat,... )
{
    char szbuf[BUF_SIZE]={0};
    DO_LOGGERWrapper(szbuf,filename,fileline,pFormat,BUF_SIZE);
    g_Logger.Warn(filename,fileline,szbuf);
}

void yrx_logTrace(const char* filename, const int fileline, const char* pFormat,... )
{
    char szbuf[BUF_SIZE]={0};
    DO_LOGGERWrapper(szbuf,filename,fileline,pFormat,BUF_SIZE);
    g_Logger.Trace(filename,fileline,szbuf);
}
