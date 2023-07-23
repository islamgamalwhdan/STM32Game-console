/*
 * STMGame.h
 *
 *  Created on: Nov 19, 2022
 *      Author: Islam
 */

#ifndef _STMGAME_H_
#define _STMGAME_H_

#include "stm32f4xx_hal.h"
#include "stm32f429i_discovery.h"
#include "gpu.h"
#include "GameEngine.h"
#include "gamepad.h"
#include "touchpad.h"
#include "gyroscope.h"
#include "auxiliary.h"
#include "Scheduler.h"

//#include "AllSprites.h"

#include "STMGame_types.h"


/* MCU_init ----------------------------------------------------------------------*/
//Public variables
extern UART_HandleTypeDef huart1 ;

//Constants
#define STLINK_RX_Pin GPIO_PIN_9
#define STLINK_RX_GPIO_Port GPIOA
#define STLINK_TX_Pin GPIO_PIN_10
#define STLINK_TX_GPIO_Port GPIOA

//Functions prototypes
void MCU_Init( void );
uint32_t Rand_num(void);
void MX_SPI_DeInit(void);
void MX_UART_DeInit(void);
void MX_USART1_UART_Init(void);
void Error_Handler(void);
/* util_spe ----------------------------------------------------------------------*/
//Functions prototypes


#endif /* SRC_STMGAME_H_ */
