
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
	#define LOGGER_MODULE_DLL_NAME    TEXT("LoggerModuleD.dll")            //��� DLL ����
#else
	#define LOGGER_MODULE_DLL_NAME    TEXT("LoggerModule.dll")            //��� DLL ����
#endif

/// ������
/// @note �ڳ���������ʱ�����Logger::Start���������磺
///       g_Logger.StartSystem("logModule.properties");
///       ����־��ʾ�����£�
///       g_Logger.Debug(__FILE__, __LINE__, "Debug log[%d]", 100);
///       �÷������Ϻ�printf()��CSting::Format()������ࡣ
///       �����VS2005�Լ����ϵĿ�������������ʹ�ú����־�����ӷ��㣺
///       LOG_DEBUG("Debug log[%d]", 100);

class LOGGER_MODULE_CLASS LoggerModule
{
public:
	LoggerModule();
	virtual ~LoggerModule();

	/// ������־ϵͳ
	/// @param[in] properties_filename ��־ϵͳ�����ļ��ļ���
	void StartSystem(const TCHAR* properties_filename);

	/// �ر���־ϵͳ
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
// ������־
//////////////////////////////////////////////////////////////////////////
#define ASSERT_LOG(expr)\
	if ( (expr) ) {;} else g_Logger.Error(__FILE__, __LINE__, #expr);


//////////////////////////////////////////////////////////////////////////
// ���µĺ�ֻ��VS2005�Լ�֮�ϵİ汾����ʹ�ã���ΪVS2005֮�µİ汾��֧�ֿɱ������
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

