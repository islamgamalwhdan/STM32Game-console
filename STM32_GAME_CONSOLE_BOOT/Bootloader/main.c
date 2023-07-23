/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************

  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/

#include "STMGame.h"
#include "Bootloader.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//File system
#include "fatfs.h"
#include "fatfs_sd.h"

#include "string.h"
#include "main.h"
#include <stdio.h>
#include "AllSprites.h"

#define  MAX_FILES                10
#define  MAX_FILE_NAME            13
#define  DIR_NAME                 "Games"
#define  DIR_PATH                 "Games/"
#define  TIMEOUT                  5000


typedef struct
{
	char file_name[MAX_FILE_NAME] ;
	u32 file_size ;
}FILES_INFO;


Sprite BackGround ;
Sprite arrow  ;
GAMEPAD_BUTTON GamePad;
TC_Panel tc ;

FATFS fs;
FILES_INFO content[MAX_FILES] ;
int i=0 ;
char* Bin_File ;
void Display_SD_Dir_content(const char *DR_path);
void Choose_BinToload(char** BinFile);

/* Main function ----------------------------------------------------------------------*/
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/

  MCU_Init() ;
  InitDisplay(0,BLUE);
  GamePad_Init();
  touchpad_init();

  MX_FATFS_Init();

  /* Wait for SD module reset */
  HAL_Delay(1);

  char *BinFile = NULL  ;
  Display_SD_Dir_content(DIR_NAME) ;
  Choose_BinToload(&BinFile);

  // If there is a new game just replace it with the old one Or jump to the old one
  if(BinFile != NULL)
  {
           BL_CopyBinFile(BinFile ,APPLICATION_FLASH_ADD);
  }
  BL_Go2App();

 //Should not reach here!!
  while (1) ;

}//main


/* Functions ----------------------------------------------------------------------*/
void Init_backGround(Sprite *spr)
{
   spr->x = 0 ;
   spr->y = 0 ;
   spr->Width =  SCREEN_W ;
   spr->Height = SCREEN_H;
   spr->ImageData =0; //(uint16_t*) image_background ;
   spr->color = BLUE ;
   spr->LayerId   = BACKGROUND ;
   spr->active =1 ;
}


void Init_Arrow(Sprite *spr)
{
	spr->x = 5 ;
	spr->y = 90 ;
	spr->Width =  10 ;
	spr->Height = 8;
	spr->ImageData =(uint16_t*) image_arrow ;
	spr->LayerId   = SPRITE ;
	spr->active =1 ;
}


void Display_SD_Dir_content(const char *DR_path)
{
	DIR dir_files ;
	FRESULT rc ;
	FILINFO fno;



	/* Mount SD Card */
	  if(f_mount(&fs, "", 0) != FR_OK)
	   		FileError_Handler(__FILE__, __LINE__);

	   	// open directory .
	   if(f_opendir(&dir_files , DR_path) == FR_OK)
	   	 {

	   for(;;)
	   		{//loop to read files or directory inside  directory .

	   			rc = f_readdir(&dir_files, &fno);	/* Read a directory item */
	   			if (rc || !fno.fname[0]) break;	/* Error or end of dir */

	   			if (! (fno.fattrib & AM_DIR) )  // if it is not directory So it should be files .
	   			{
	   			    strncpy(content[i].file_name , fno.fname , strlen(fno.fname)) ;
	   				content[i++].file_size = fno.fsize ;
	   			 }//iner_if

	   		} //for

	   	 }//if

	   	BufferConfig(NON_ANIMATED) ;
	   	Init_backGround(&BackGround);
	   	DrawSprite(&BackGround);

	   	//Draw_String_fast(50, 50, "Folder Contents :");
	   	renderStr(0, 50, BLACK, "Folder Contents :");

	   	for(int k = 0 , r = 90 ; k< i ;k++ , r+=20)
	   	   	    //Draw_String_fast(100,r , content[k].file_name);
	   		renderStr(20,r ,WHITE, content[k].file_name);

	   	Init_Arrow(&arrow);
	   	DrawSprite(&arrow);
}
/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */

void Choose_BinToload(char **BinFile)
{
	u32 pressCount = 0 ;
	u32 entryTime = HAL_GetTick() ;
	GamePAD_BTNState Bustate = RELEASED ;
	static char bin[30] = DIR_PATH ;

	   	while ( (HAL_GetTick() - entryTime) < TIMEOUT )
	   	{
	   		GamePad = GamePad_Read() ;
	   		if( GamePad.button.down == PRESSED && Bustate ==RELEASED )
	   		{
	   			Erase_Sprite(&arrow , &BackGround);
	   			if(++pressCount >= i)
	   			   	{
	   				    pressCount = 0;
	   			   		arrow.y = 90 ;
	   			   	}
	   			else    arrow.y += 20 ;

	   			DrawSprite(&arrow) ;
	   			Bustate =PRESSED;

	   			entryTime = HAL_GetTick() ;
	   		}
	   		if(GamePad.button.down == RELEASED && Bustate ==PRESSED )
	   		{
	   			Bustate =RELEASED;
	   		}

	   		if(GamePad.button.select == PRESSED)
	   		{
	   			strcat(bin, content[pressCount].file_name);
	   			*BinFile = bin ;
	   			break;
	   		}
	   	}
}



int _write(int file, char *ptr, int len)
{
	int DataIdx;

	for(DataIdx=0; DataIdx<len; DataIdx++)
	{
		HAL_UART_Transmit(&huart1, (uint8_t *)ptr++, 1, 100);
	}
	return len;
}



void FileError_Handler(char *file, int line)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	while(1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
