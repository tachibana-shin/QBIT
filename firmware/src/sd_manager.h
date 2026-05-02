#ifndef SD_MANAGER_H
#define SD_MANAGER_H

#include <Arduino.h>
#include <FS.h>

// Initialize SD card with configured pins.
// Returns true if SD is mounted and /QBit folder exists.
bool sdManagerInit();

// Returns true if SD card is mounted and ready.
bool sdManagerIsReady();

// Get the SD filesystem object for file operations.
fs::FS& sdManagerFS();

// Get storage info
uint64_t sdManagerTotalBytes();
uint64_t sdManagerUsedBytes();

#endif // SD_MANAGER_H
