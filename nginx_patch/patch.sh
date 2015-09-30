#!/bin/bash 
CORE_NGINX_C=../../eginx/src/nginx_win-1.6.2/src/core/nginx.c
INSERTLINE=`grep -rin "ngx_debug_init" ${CORE_NGINX_C} |awk  -F: '{print $1}'`
echo $INSERTLINE


#cat ./crash_.cpp >> ../src/nginx_win-1.6.2/src/core/nginx.c 
CONTEXT=`cat ./crash_exception.c`
echo ${CONTEXT}
MAINLINE=`grep -rin '\*\*ngx_os_environ' ${CORE_NGINX_C} |awk -F: '{print $1}'`

sed -i "${MAINLINE}a ${CONTEXT}" ${CORE_NGINX_C}

exit
echo ${MAINLINE}
EXCEPTION_="#ifdef NGX_WIN32\n \
    SetUnhandledExceptionFilter(callback);\n \
#endif\n"

#sed -i "${INSERTLINE}a ${EXCEPTION_}" ${CORE_NGINX_C} 

