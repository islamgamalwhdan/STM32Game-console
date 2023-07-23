/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "STMGame.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
typedef enum
{
	GAME_STATE_INIT ,
	GAME_STATE_LEVEL ,
	GAME_STATE_RUN ,
	GAME_STATE_END
}GameState;

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
#define SCREEN_W                 240
#define SCREEN_H                 320
#define SCREEN_W_RO              320
#define SCREEN_H_RO              240
#define ONEBRICK_WIDHT           40
#define ONEBRICK_HEIGHT          16
#define ONEBRICK_WIDHT_ROT       16
#define ONEBRICK_HEIGHT_ROT      40
#define BRICKS_WIDTH             6
#define BRICKS_HEIGHT            5
#define BRICKS_WIDTH_RO          8
#define BRICKS_HEIGHT_RO         4
#define PADDLE_WIDTH             60
#define PADDLE_HEIGHT            16
#define PADDLE_WIDTH_RO          80
#define PADDLE_HEIGHT_RO         12
#define BALL_WIDTH               12
#define BALL_HEIGHT              12

#define PADDLE_CENTRE            SCREEN_W/2 - PADDLE_WIDTH/2

/* Exported functions prototypes ---------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void Error_Handler(void);
void FileError_Handler(char *file, int line);
void Init_backGround(Sprite *spr);
void Init_bird(Sprite *spr);
void InitBricks(Sprite *bricks);
void Init_Paddle(Sprite *paddle);
void Init_Ball(Sprite *ball);
void Init_Arrow(Sprite *spr);
void Control_Ball_Move(Sprite * ball, GAMEPAD_BUTTON *GamePad);
void Control_Paddle_Move(Sprite * paddle ,Sprite * ball ,  GAMEPAD_BUTTON *GamePad);
void DrawBricks(Sprite *bricks);
void Control_collsion(void);
void game_main(void);
void GamePad_InputsUpdate(void) ;
void TouchPad_InputsUpdate(void) ;
void GET_GYRO_Angles(void);

void test_code(void);
void Alien_init(void) ;


/* USER CODE BEGIN EFP */

/* USER CODE END EFP */




/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
