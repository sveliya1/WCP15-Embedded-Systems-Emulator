//Header file for flash.cpp, this program will burn the flash to memory
//WCP15 - Embedded Systems Emulator

#ifndef FLASH_H
#define FLASH_H

#include "macros.h"
#include "memorymap.h"

void burn_flash_to_mem(ROMDevice* flash);
uint32_t init_sp();

#endif