#pragma once
#include "FS.h"
#include <LittleFS.h>


extern bool setupFS();

extern void fs_append(const char* filename, uint8_t* buffer, size_t bufferSize);

extern void fs_write(const char* filename, uint8_t* buffer, size_t bufferSize);