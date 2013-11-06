#ifndef _LOGMODULE_H_
#define _LOGMODULE_H_
#ifdef __cplusplus
extern "C" {
#endif

    void yrx_logInitLog4cplus( const char* logConfig );

	void yrx_logDebug(const char* filename, const int fileline, const char* pFormat,... );
	
	void yrx_logError(const char* filename, const int fileline, const char* pFormat,... );

    void yrx_logFatal(const char* filename, const int fileline, const char* pFormat,... );

	void yrx_logInfo(const char* filename, const int fileline, const char* pFormat,... );

	void yrx_logWarn(const char* filename, const int fileline, const char* pFormat,... );

	void yrx_logTrace(const char* filename, const int fileline, const char* pFormat,... );
#ifdef __cplusplus
}
#endif

#endif // _LOGMODULE_H_ 
