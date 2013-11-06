
#ifndef __LoggerModule_H__
#define __LoggerModule_H__
#ifdef __cplusplus
extern "C" {
#endif
//#include <tchar.h>
#ifdef _UNICODE_
#define TCHAR wchar_t
#else
#define TCHAR char
#endif

#ifndef LOGGER_MODULE_CLASS
	#ifdef  LOGGER_MODULE_DLL
		#define LOGGER_MODULE_CLASS 
	#else
		#define LOGGER_MODULE_CLASS
	#endif
#endif

#ifdef _DEBUG
	#define LOGGER_MODULE_DLL_NAME    TEXT("LoggerModuleD.dll")            //组件 DLL 名字
#else
	#define LOGGER_MODULE_DLL_NAME    TEXT("LoggerModule.dll")            //组件 DLL 名字
#endif

/// 包裹类
/// @note 在程序启动的时候调用Logger::Start方法，例如：
///       g_Logger.StartSystem("logModule.properties");
///       打日志的示例如下：
///       g_Logger.Debug(__FILE__, __LINE__, "Debug log[%d]", 100);
///       用法基本上和printf()和CSting::Format()方法差不多。
///       如果是VS2005以及以上的开发环境，可以使用宏打日志，更加方便：
///       LOG_DEBUG("Debug log[%d]", 100);

class LOGGER_MODULE_CLASS LoggerModule
{
public:
	LoggerModule();
	virtual ~LoggerModule();

	/// 启动日志系统
	/// @param[in] properties_filename 日志系统配置文件文件名
	void StartSystem(const TCHAR* properties_filename);

	/// 关闭日志系统
	void StopSystem();

public:
	void Debug(const char* filename, const int fileline, const char* pFormat,... );
	
	void Error(const char* filename, const int fileline, const char* pFormat,... );

    void Fatal(const char* filename, const int fileline, const char* pFormat,... );

	void Info(const char* filename, const int fileline, const char* pFormat,... );

	void Warn(const char* filename, const int fileline, const char* pFormat,... );

	void Trace(const char* filename, const int fileline, const char* pFormat,... );


public:
	static inline LoggerModule* getSingletonPtr()
	{
		return &getSingleton();
	}
	static inline LoggerModule& getSingleton()
	{
		static LoggerModule _instance; 
		return _instance;
	}
};
#define g_Logger LoggerModule::getSingleton()
#define g_pLogger LoggerModule::getSingleton()


//////////////////////////////////////////////////////////////////////////
// 断言日志
//////////////////////////////////////////////////////////////////////////
#define ASSERT_LOG(expr)\
	if ( (expr) ) {;} else g_Logger.Error(__FILE__, __LINE__, #expr);


//////////////////////////////////////////////////////////////////////////
// 以下的宏只有VS2005以及之上的版本可以使用！因为VS2005之下的版本不支持可变参数宏
//////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER) && _MSC_VER > 1400 
 #define LOG_DEBUG()    g_Logger.Debug(__FILE__, __LINE__, __VA_ARGS__);
 #define LOG_ERROR()    g_Logger.Error(__FILE__, __LINE__, __VA_ARGS__);
 #define LOG_FATAL()    g_Logger.Fatal(__FILE__, __LINE__, __VA_ARGS__);
 #define LOG_INFO()    g_Logger.Info(__FILE__, __LINE__, __VA_ARGS__);
 #define LOG_WARN()    g_Logger.Warn(__FILE__, __LINE__, __VA_ARGS__);
 #define LOG_TRACE()    g_Logger.Trace(__FILE__, __LINE__, __VA_ARGS__);
#endif
//#include <tchar.h>

#ifdef __cplusplus
} // extern "C"
#endif
#endif

