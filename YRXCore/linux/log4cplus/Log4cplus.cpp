#include "yrx_logmodule.h"
#include "LoggerModule.h"
void yrx_logInitLog4cplus( const char* logConfig )
{
    g_Logger.StartSystem( logConfig );
    //g_Logger.StartSystem("log4cplus.Client_properties");
}


void yrx_logDebug(const char* filename, const int fileline, const char* pFormat,... )
{
    g_Logger.Debug(filename,fileline,pFormat);
}	

void yrx_logError(const char* filename, const int fileline, const char* pFormat,... )
{
    g_Logger.Error(filename,fileline,pFormat);
}

void yrx_logFatal(const char* filename, const int fileline, const char* pFormat,... )
{
    g_Logger.Fatal(filename,fileline,pFormat);
}

void yrx_logInfo(const char* filename, const int fileline, const char* pFormat,... )
{
    g_Logger.Info(filename,fileline,pFormat);
}

void yrx_logWarn(const char* filename, const int fileline, const char* pFormat,... )
{
    g_Logger.Warn(filename,fileline,pFormat);
}

void yrx_logTrace(const char* filename, const int fileline, const char* pFormat,... )
{
    g_Logger.Trace(filename,fileline,pFormat);
}
