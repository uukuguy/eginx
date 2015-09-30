 #ifdef NGX_WIN32
 #include   <windows.h>
 long __stdcall callback(PEXCEPTION_POINTERS excp)
 {
     ngx_log_error(NGX_LOG_ERR, ngx_cycle->log, NGX_EACCES, "Nginx Crash!!" );

     return EXCEPTION_EXECUTE_HANDLER;
 }
 #endif


