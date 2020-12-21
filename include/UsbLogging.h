// Author: Andrew Combs (ajcomb01@louisville.edu)

#ifndef USBLOGGING_H
#define USBLOGGING_H

#include <stdbool.h>
#include <stdio.h>

// Utility macro for creating a string buffer
#define STRING_BUFFER(name, length) \
	char (name ## _buf)[(length) + 1]; \
    char *(name) = &(name ## _buf)[0];

enum {
    
    UsbLogging_FilePathMaxLength = 40,
    UsbLogging_DebugPrintEnabled = true,
    UsbLogging_DebugPrintDisabled = false,
};

typedef struct {
	bool printDebug;
	bool active;
	FILE *logFile;
} UsbLogging_t;

/* Initialize USB Logging
 * You must initialize before using!
 * You must close after initializing, before ending program!
 * You may have multiple USB Logs running at once
 * Mounts USB drive and opens/creates file
 * logFileName should be UsbLogging_FilePathMaxLength characters or fewer, null terminated
 */
void UsbLogging_Init(UsbLogging_t *instance, const char *logFileName, bool enableDebugPrinting);

// Enable debug printing
void UsbLogging_Debug(UsbLogging_t *instance);

// Disable debug printing
void UsbLogging_NoDebug(UsbLogging_t *instance);

// Print a string to the log
void UsbLogging_Log(UsbLogging_t *instance, char *string);

// Print a string to the log, followed by a newline
void UsbLogging_LogLn(UsbLogging_t *instance, char *string);

/* Close the USB Log
 * You MUST close all open logs to safely remove the USB drive!
 */
void UsbLogging_Close(UsbLogging_t *instance);

#endif