// Author: Andrew Combs (ajcomb01@louisville.edu)

#include <errno.h>
#include <string.h>
#include <sys/mount.h>

#include "UsbLogging.h"

#define DEBUG_PRINT(msg, ...) if(instance->printDebug) { printf("UsbLogging.c - %p - ", instance); printf((msg), ##__VA_ARGS__); }

enum {
    UsbLogging_Failure,
    UsbLogging_Success,
};

static const char *UsbDevicePath = "/dev/sda1";
static const char *UsbMountPath = "/mnt/usb";
static const char *UsbFileSystemType = "vfat";

static const char *LogFileOpenMode = "a";
static const char *NewLine = "\n";

static int activeUsbLoggers = 0;

static bool mountUsb(UsbLogging_t *instance) {
    if (activeUsbLoggers > 0) {
        instance->active = true;
        activeUsbLoggers++;
        return UsbLogging_Success;
    }
    
    if(mount(UsbDevicePath, UsbMountPath, UsbFileSystemType, MS_NOATIME, NULL)) {
        if (errno == EBUSY) {
            DEBUG_PRINT("USB Error: Mountpoint busy.\n");
            return UsbLogging_Failure;
        } else {
            DEBUG_PRINT("USB Error: Mount error: %s\n", strerror(errno));
            return UsbLogging_Failure;
        }
    } else {
        DEBUG_PRINT("USB drive mounted successfully\n");
        instance->active = true;
        activeUsbLoggers++;
        return UsbLogging_Success;
    }
}

static bool unmountUsb(UsbLogging_t *instance) {
    if(instance->active == false) {
        return UsbLogging_Success;
    }
    
    instance->active = false;
    activeUsbLoggers--;
    
    if(umount(UsbMountPath)) {
        DEBUG_PRINT("USB Error: Unmount error: %s\n", strerror(errno));
        return UsbLogging_Failure;
    } else {
        DEBUG_PRINT("USB drive unmounted successfully\n");
        return UsbLogging_Success;
    }
}

static bool openFile(UsbLogging_t *instance, const char *path) {
    instance->logFile = fopen(path, LogFileOpenMode);
    
    if(instance->logFile == NULL) {
        DEBUG_PRINT("File Error while Opening: %s\n", strerror(errno));
        return UsbLogging_Failure;
    } else {
        DEBUG_PRINT("Successfully opened file\n");
        return UsbLogging_Success;
    }
}

static bool writeToFile(UsbLogging_t *instance, const char *string) {
    if(fputs(string, instance->logFile) == EOF) {
        DEBUG_PRINT("Error while writing to file\n");
        return UsbLogging_Failure;
    } else {
        return UsbLogging_Success;
    }
}

static bool closeFile(UsbLogging_t *instance) {
    if(fclose(instance->logFile) == EOF) {
        DEBUG_PRINT("File Error while closing: %s\n", strerror(errno));
        return UsbLogging_Failure;
    } else {
        DEBUG_PRINT("Successfully closed file\n");
        return UsbLogging_Success;
    }
}

void UsbLogging_Init(UsbLogging_t *instance, const char *logFileName, bool enableDebugPrinting) {
    instance->printDebug = enableDebugPrinting;
    instance->active = false;
    instance->logFile = NULL;

    mountUsb(instance);

    // Create a string buffer
    char filePathBuffer[strlen(UsbMountPath) + 1 + UsbLogging_FilePathMaxLength + 1];
    char *filePath = &filePathBuffer[0];
    // Copy UsbMountPath into the buffer memcpy
    memcpy(filePath, UsbMountPath, strlen(UsbMountPath));
    // Concat logFileName onto the buffer strncat
    strncat(filePath, "/", 1);
    strncat(filePath, logFileName, UsbLogging_FilePathMaxLength);
    
    openFile(instance, filePath);
}

void UsbLogging_Debug(UsbLogging_t *instance) {
    instance->printDebug = true;
}

void UsbLogging_NoDebug(UsbLogging_t *instance) {
    instance->printDebug = false;
}

void UsbLogging_Log(UsbLogging_t *instance, char *string) {
    writeToFile(instance, string);
}

void UsbLogging_LogLn(UsbLogging_t *instance, char *string) {
    writeToFile(instance, string);
    writeToFile(instance, NewLine);
}

void UsbLogging_Close(UsbLogging_t *instance) {
    closeFile(instance);

    unmountUsb(instance);
}

#undef DEBUG_PRINT
