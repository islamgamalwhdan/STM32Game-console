
//Includes
#include "gamepad.h"
#include "stm32f4xx_hal.h"
#include <string.h>

static volatile GAMEPAD_BUTTON GamePad  ;

static u8 ReadCurrentState(void);
//Constants

#define GAMEPAD_DATAIN0 GPIO_PIN_7
#define GAMEPAD_SH_LD   GPIO_PIN_3
#define GAMEPAD_CLK     GPIO_PIN_4
#define GAMEPAD_PORT    GPIOB

//Functions definitions 

void GamePad_Init(void) 
{

	*(u8*)(&(GamePad.button)) = 0xFF ;
	GamePad.Prev_rd = 0xFF ;

	memset(GamePad.BtnDebouceCounter , 0 , GAMEPAD_NO_BTN) ;
  GPIO_InitTypeDef GPIO_InitStruct;
	
  GPIO_InitStruct.Pin = GAMEPAD_SH_LD|GAMEPAD_CLK;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH   ;
  HAL_GPIO_Init(GAMEPAD_PORT, &GPIO_InitStruct);
	
  GPIO_InitStruct.Pin = GAMEPAD_DATAIN0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GAMEPAD_PORT, &GPIO_InitStruct);
	
	GAMEPAD_PORT->ODR = 0 ;
	
}

GAMEPAD_BUTTON GamePad_Read(void)
{
	volatile u8 currState ;
	for(u8 i = 0 ; i < GAMEPAD_NO_BTN ; i++)
	{
	 currState = ReadCurrentState() ;
	 if(currState == 0) // All button released
	 {
		 *(u8*)(&(GamePad.button)) = 0xFF ;
	 }
		if( currState & (1<< i) )
		{
			if(( currState & (1<< i)) == (GamePad.Prev_rd & (1<<i))  )
			{
				  GamePad.BtnDebouceCounter[i]++ ;
			}
			else
				{
				  GamePad.BtnDebouceCounter[i] = 0 ;
				}

		}


		if(GamePad.BtnDebouceCounter[i] >= MAX_DEBOUNCE_COUNT)
		{
			*(u8*)(&(GamePad.button)) = 0xFF ;
			(*(u8*)(&(GamePad.button))) &= ~(1<<i) ;   // set 0 means pressed
			GamePad.BtnDebouceCounter[i] = 0 ;
		}
		GamePad.Prev_rd = currState ;
	}

	return GamePad ;
}

static u8 ReadCurrentState(void)
{
	volatile u8 current =0 ;

	HAL_GPIO_WritePin(GAMEPAD_PORT , GAMEPAD_CLK , GPIO_PIN_RESET) ;
	HAL_GPIO_WritePin(GAMEPAD_PORT , GAMEPAD_SH_LD , GPIO_PIN_RESET) ;

	HAL_GPIO_WritePin(GAMEPAD_PORT , GAMEPAD_SH_LD , GPIO_PIN_SET) ;
	HAL_GPIO_WritePin(GAMEPAD_PORT , GAMEPAD_SH_LD , GPIO_PIN_RESET) ;

	for ( u8 i = 0 ;  i < GAMEPAD_NO_BTN ; i++)
		{
		current = (current <<1)| HAL_GPIO_ReadPin(GAMEPAD_PORT , GAMEPAD_DATAIN0) ;

		//clock
		HAL_GPIO_WritePin(GAMEPAD_PORT , GAMEPAD_CLK  , GPIO_PIN_SET)   ;
		HAL_GPIO_WritePin(GAMEPAD_PORT , GAMEPAD_CLK  , GPIO_PIN_RESET) ;

		}
	GamePad.Connection = current ?GP_CONNECTED: GP_NOT_CONNECTED ;
	return ~current ;
}


