/*
 * STMGame_types.h
 *
 *  Created on: Nov 25, 2022
 *      Author: Islam
 */

#ifndef INC_STMGAME_TYPES_H_
#define INC_STMGAME_TYPES_H_

#include "stdint.h"

typedef int32_t s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  /*!< Read Only */
typedef const int16_t sc16;  /*!< Read Only */
typedef const int8_t  sc8;   /*!< Read Only */

typedef volatile int32_t  vs32;
typedef volatile int16_t  vs16;
typedef volatile int8_t   vs8;

typedef volatile const int32_t vsc32;  /*!< Read Only */
typedef volatile const int16_t vsc16;  /*!< Read Only */
typedef volatile const int8_t  vsc8;   /*!< Read Only */

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;

#endif /* INC_STMGAME_TYPES_H_ */
