/*
 * bootloader.h
 *
 *  Created on: Dec 4, 2022
 *      Author: Islam
 */

#ifndef SRC_BOOTLOADER_H_
#define SRC_BOOTLOADER_H_

#include "STMGame_types.h"

#define  APPLICATION_FLASH_ADD     0x8040000 // from sector 6
#define  SD_CARD_BIN_PATH          "files/app.bin"    //Firmware name present in SD card
#define  SRAM_SIZE                 192*1024
#define  SRAM_END                  (SRAM_BASE + SRAM_SIZE)

typedef enum
{
  BL_OK       = 0U,
  BL_ERROR    = 1U,
  BL_BUSY     = 2U,
  BL_TIMEOUT  = 3U
} BL_StatusType;

BL_StatusType BL_CopyBinFile(const char *filePath  ,u32 Sec_loc);
void BL_Go2App(void);

#endif /* SRC_BOOTLOADER_H_ */
