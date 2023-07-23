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
#include "Math_lib.h"
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


#define TFTW             SCREEN_W     // screen width
#define TFTH             SCREEN_H     // screen height
#define TFTW2            120     // half screen width
#define TFTH2            160     // half screen height
// game constant

#define SHIP_W           29
#define SHIP_H           32
#define BULLET_W         4
#define BULLET_H         4
#define MAX_BULLETS      50 // max number of bullets can be shown in screen at the same time
#define NUM_ASTEROIDS    5
#define MAX_EXPLODES     NUM_ASTEROIDS
#define EXPLOS_FRAMES    4
#define EXPLOS_W         33
#define EXPLOS_H         37
#define PI 3.14159f

/* Exported functions prototypes ---------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void Error_Handler(void);
void Init_backGround(Sprite *spr);
void game_main(void);
void GamePad_InputsUpdate(void) ;
void TouchPad_InputsUpdate(void) ;
void process_input(void);
void Asteriod_Init(Sprite * astr , u8 index);
void Asteriod_update(Sprite * astr);
void bullet_init(void);
void Ship_Init(void);
void fire(Sprite *shp , Sprite * bul);
void Bullet_update(Sprite * bul);
void Explosion_Init(Sprite * exp ,Sprite * ast , u8 index);
void Explode(Sprite * exp ,Sprite * ast , u8 index);
/* USER CODE BEGIN EFP */

/* USER CODE END EFP */




/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
