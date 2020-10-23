# USB Logging for Wallaby/Wombat
This project shows how to save data to a USB drive connected to a Wallaby/Wombat controller. This is intended to aid in collecting data in lab 5.

## Getting Started
To use this in your own project, first upload `UsbLogging.h` and `UsbLogging.c` to your project. Then follow the steps below to create and use a USB Logging object.

### Include the header
``` C
#include "UsbLogging.h"
```

### Create the USB Logging Object
``` C
UsbLogging_t logger;
```

### Initialize the Object
``` C
UsbLogging_Init(&logger, "MyLogFile.txt", UsbLogging_DebugPrintEnabled);
```

Change `MyLogFile.txt` to whatever file name you would like for your log file. The file will be created if it does not exist. If it does already exist, the logger will add to the end of it. The logger will not overwrite or delete the file.

In this example debug print is enabled. This can be useful when troubleshooting issues with the library, but may clutter stdout. To disable debugging, pass `UsbLogging_DebugPrintDisabled` instead.

### Log Data
``` C
UsbLogging_LogLn(&logger, "Hello world!");
```

This will print the string to the log, followed by a new line. This function only accepts a single string as an argument, so to print data you will need to use sprintf or similar.

### Close the Logger
``` C
UsbLogging_Close(&logger);
```

This will safely close the file and dismount the USB drive. It is important to call this function before removing the USB drive to prevent data corruption.

## Troubleshooting
### USB Drives
The USB drive must be properly formatted. Most USB drives will already be formatted correctly for the library, but if you've used the drive to install linux or changed the formatting of the drive you may encounter errors.

The library uses the first partition on the drive and assumes that it is FAT32. To set up a drive to work with the USB Logging library, first format the drive for MBR/DOS compatability, then create a partition and format it as FAT (FAT32).

## Resources
For a full list of available functions and their descriptions, see `UsbLogging.h`.

To report issues or make suggestions please submit an issue or PR to this repo.

For more information about the functions used in this library please consult your man pages. (i.e. `man fopen`, `man 2 mount`)
