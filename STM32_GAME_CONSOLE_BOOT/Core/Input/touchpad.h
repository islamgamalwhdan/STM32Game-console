/*
 * touchpad.h
 *
 *  Created on: Apr 19, 2021
 *      Author: Islam
 */

#ifndef SRC_TOUCHPAD_H_
#define SRC_TOUCHPAD_H_

#include "stdint.h"

typedef enum {TC_RELEASED , TC_PRESSED}TC_STATE ;
typedef struct
{
	int16_t x;
	int16_t y;
	TC_STATE state ;
}TC_Panel;

void touchpad_init(void);
TC_Panel touchpad_read(void);

#endif /* SRC_TOUCHPAD_H_ */
