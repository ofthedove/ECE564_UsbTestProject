// Author: Andrew Combs (ajcomb01@louisville.edu)

#include <kipr/botball.h>

#include "UsbLogging.h"

int main()
{
    printf("Hello World\n");
    
    // ##### Simple Example #####
    UsbLogging_t logger;
    UsbLogging_Init(&logger, "MyLogFile.txt", UsbLogging_DebugPrintEnabled);
    
    UsbLogging_LogLn(&logger, "Hello world!");
    UsbLogging_LogLn(&logger, "This is my logger.");
    UsbLogging_LogLn(&logger, "I can put stuff in it.");
    UsbLogging_LogLn(&logger, "");
    UsbLogging_LogLn(&logger, "");
    
    // Warning! This may allow buffer overflows.
    // Be sure the result of sprintf won't be longer than the buffer size
    STRING_BUFFER(myString, 20);
    sprintf(myString, "Data: %3d", 42);
    UsbLogging_LogLn(&logger, myString);
    
    UsbLogging_LogLn(&logger, "");
    UsbLogging_LogLn(&logger, "");
    
    UsbLogging_LogLn(&logger, "Bye now");
    
    UsbLogging_Close(&logger);
    
    
    
    // ##### CSV Example #####
    UsbLogging_t csv;
    UsbLogging_Init(&csv, "data.csv", UsbLogging_DebugPrintEnabled);
    
    UsbLogging_LogLn(&csv, "Col1, Col2, Col3");
    
    int data1 = 5, data2 = 62, data3 = 7;
    STRING_BUFFER(csvRow, 20);
    sprintf(csvRow, "%3d, %3d, %3d", data1, data2, data3);
    UsbLogging_LogLn(&csv, csvRow);
    
    UsbLogging_Close(&csv);
    
    
    
    // ##### Multiple Instances #####
    UsbLogging_t log1, log2;
    UsbLogging_Init(&log1, "test1.txt", UsbLogging_DebugPrintEnabled);
    UsbLogging_Init(&log2, "test2.txt", UsbLogging_DebugPrintEnabled);
    
    UsbLogging_LogLn(&log1, "This is log 1");
    
    UsbLogging_LogLn(&log2, "This is log 2");
    
    UsbLogging_LogLn(&log1, "Both of them work");
    
    UsbLogging_LogLn(&log2, "At the same time!");
    
    UsbLogging_Close(&log1);
    UsbLogging_Close(&log2);
    
    return 0;
}
