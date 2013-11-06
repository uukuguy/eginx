#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "yrx_logmodule.h"
int main(int argc, const char *argv[])
{
    yrx_logInitLog4cplus( "log4cplus.Client_properties" ); 
    yrx_logDebug(__FILE__,__LINE__,"a=%d,b=%s",1,"bb");
    yrx_logDebug(__FILE__,__LINE__,"xxxx");
    yrx_logInfo(__FILE__,__LINE__,"abcdss=%s","==============");
    
    //yrx_logInfo(__FILE__,__LINE__,"yyyy");
    printf("hello");
    return 0;
}
