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


#define TFTW             SCREEN_W     // screen width
#define TFTH             SCREEN_H     // screen height
#define TFTW2            120     // half screen width
#define TFTH2            160     // half screen height
// game constant
#define PIPE_SPEED        1.0f
#define GRAVITY           9.8
#define JUMP_FORCE        1.5


// pipe size
#define PIPEW              67     // pipe width
#define PIPEH              145
#define GAPHEIGHT          36     // pipe gap height
#define PIPEDN_MINY        176
#define PIPEDN_MAXY        248
#define PIPEUP_MINY        -72
#define PIPEUP_MAXY         0
#define GAP_MIN             32
#define GAP_MAX            176

//Bird
#define BIRDW2            8     // half width
#define BIRDH2            8     // half height
/* Exported functions prototypes ---------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void Error_Handler(void);
void Init_backGround(Sprite *spr);
void game_main(void);
void GamePad_InputsUpdate(void) ;
void TouchPad_InputsUpdate(void) ;
void Init_pipes(Sprite* pDwn , Sprite* pUp);
void fbird_Init(void);
void process_input(void);
void update_pipes(void);
void Kill_Sprites(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */




/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
