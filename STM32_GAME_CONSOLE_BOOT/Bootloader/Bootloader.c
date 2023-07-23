/*
 * Bootloader.c
 *
 *  Created on: Dec 4, 2022
 *      Author: Islam
 */

//Includes

#include "STMGame.h"
#include "Bootloader.h"
#include "fatfs.h"
#include "fatfs_sd.h"
#include "string.h"
#include <stdio.h>

#define  PACKET_MAX_SIZE            256U




//Private prototypes
static BL_StatusType App_section_erase(void);
static BL_StatusType write_data_to_flash_app( u8 *data, u32 from ,u32 data_len );



BL_StatusType BL_CopyBinFile(const char *filePath  ,u32 Sec_loc)
{
	    FIL fil ;
	    UINT rb = PACKET_MAX_SIZE ;
	    u8 buf[PACKET_MAX_SIZE] ;// todo : fix static to be at stack
	    BL_StatusType ret  ;


	   	//Erase APP section
	   	if( App_section_erase()!= BL_OK)
	   	{
	   		return BL_ERROR ;
	    }

	   	if(f_open(&fil, filePath, FA_WRITE | FA_READ | FA_OPEN_EXISTING) != FR_OK)
	   	 {
	   		return BL_ERROR ;
	   	 }

	   	  while(rb== PACKET_MAX_SIZE) // read while until reach rb != PACKET_MAX_SIZE (end of file) .
	   	  {
	   		 f_read(&fil,buf , PACKET_MAX_SIZE , &rb) ;
	   		 if(rb)
	   		 {
	   			 if(rb < PACKET_MAX_SIZE)
	   			 {
	   				memset(buf + rb , 0xFF , PACKET_MAX_SIZE -rb) ; // fill remain buffer
	   			 }
	   			ret= write_data_to_flash_app(buf, Sec_loc  ,PACKET_MAX_SIZE);
	   			if(ret != BL_OK)
	   			{
	   				return BL_ERROR ;
	   			}
	   			 Sec_loc += PACKET_MAX_SIZE ;
	   		 }
	   	  } // while

	   	/* Close file */
	   	f_close(&fil);

	   	/* Unmount SDCARD */
	   	if(f_mount(NULL, "", 1) != FR_OK)
	   		FileError_Handler(__FILE__, __LINE__);

	   	return BL_OK ;
}




void BL_Go2App(void)
{

	if( *((u32 *)APPLICATION_FLASH_ADD) == SRAM_END  )
	{

		HAL_RCC_DeInit();// to turn off the PLL and set the clock to it's default state
#if 0
		f_mount(NULL, "", 1) ;
		MX_SPI_DeInit();
		MX_UART_DeInit();


		HAL_GPIO_DeInit(GPIOE, GPIO_PIN_3);

		__HAL_RCC_GPIOA_CLK_DISABLE();
		__HAL_RCC_GPIOB_CLK_DISABLE();
		__HAL_RCC_GPIOC_CLK_DISABLE();
		__HAL_RCC_GPIOD_CLK_DISABLE();
		__HAL_RCC_GPIOE_CLK_DISABLE();
		__HAL_RCC_GPIOF_CLK_DISABLE();
		__HAL_RCC_GPIOG_CLK_DISABLE();

		//HAL_DeInit();
		// Disabling SysTick interrupt
		SysTick->CTRL = 0;
		//SysTick->LOAD = 0;
		//SysTick->VAL =0 ;
#endif
		__DMB(); //ARM says to use a DMB instruction before relocating VTOR */
		SCB->VTOR = APPLICATION_FLASH_ADD; //We relocate vector table to the sector 1
		__DSB(); //ARM says to use a DSB instruction just after relocating VTOR */

		u32 jump_addr = *((volatile u32* )(APPLICATION_FLASH_ADD+4)) ; // reset handler of app

		void (*App_RestHandler)(void) = (void*)jump_addr;
		__set_MSP(*(volatile u32*)APPLICATION_FLASH_ADD ); //Set the MSP

		//Now Jump to The App
		App_RestHandler();

	}
	else
	{
		HAL_Delay(50) ;
		//printf("No App!!\r\n") ;
	}
}


/*************************** Static functions */

static BL_StatusType App_section_erase(void)
{
	    HAL_StatusTypeDef ret ;
	    FLASH_EraseInitTypeDef EraseInitStruct;
	    uint32_t SectorError;

	    EraseInitStruct.Banks         = FLASH_BANK_1 ;
	    EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
	    EraseInitStruct.Sector        = FLASH_SECTOR_6; // Sectors 6 ,7 [first sectors to store app bin]
	    EraseInitStruct.NbSectors     = 4;//2;
	    EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;

	    if( HAL_FLASH_Unlock() != HAL_OK )
	    {
	    	      return BL_ERROR ;
	    }

	    //Erase the Flash
	    if( HAL_FLASHEx_Erase( &EraseInitStruct, &SectorError ) != HAL_OK )
	    {
	    	      return BL_ERROR ;
	     }
	    ret = HAL_FLASH_Lock();
	    return ret ;
}

static BL_StatusType write_data_to_flash_app( u8 *data, u32 from ,u32 data_len )
{
	HAL_StatusTypeDef ret ;

    if( HAL_FLASH_Unlock() != HAL_OK )
    {
      return BL_ERROR;
    }

    data_len >>=2; // divide by 4 [ 32 bit]

   for( u32 i = 0; i < data_len; i++ )
    {
      ret = HAL_FLASH_Program( FLASH_TYPEPROGRAM_WORD, from, *((u32*)data) );
      data += 4 ;
      from += 4 ;
      if( ret != HAL_OK )
      {
        break;
      }
    } // for

    if( ret != HAL_OK )
    {
      return BL_ERROR;
    }

    if( HAL_FLASH_Unlock() != HAL_OK )
    {
    	return BL_ERROR;
    }

  return BL_OK;
}
