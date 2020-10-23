// Author: Andrew Combs (ajcomb01@louisville.edu)

#include <kipr/botball.h>

#include "UsbLogging.h"

int main()
{
    printf("Hello World\n");
    
    UsbLogging_t logger;
    UsbLogging_Init(&logger, "MyLogFile", UsbLogging_DebugPrintEnabled);
    
    UsbLogging_LogLn(&logger, "Hello world!");
    UsbLogging_LogLn(&logger, "This is my logger.");
    UsbLogging_LogLn(&logger, "I can put stuff in it.");
    UsbLogging_LogLn(&logger, "");
    UsbLogging_LogLn(&logger, "");
    UsbLogging_LogLn(&logger, "Bye now");
    
    UsbLogging_Close(&logger);

    return 0;
}
