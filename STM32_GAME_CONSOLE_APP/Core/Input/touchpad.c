/*
 * touchpad.c
 *
 *  Created on: Apr 19, 2021
 *      Author: Islam
 */

#include "touchpad.h"
#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#include "stmpe811.h"

#include "stdint.h"

#define TRUE   1
#define FALSE  0
#define TFT_HOR_RES 240
#define TFT_VER_RES 320

static TC_Panel TC_status ;

static uint8_t touchpad_get_xy(int16_t *x, int16_t *y);

void touchpad_init(void)
{
	stmpe811_Init(TS_I2C_ADDRESS);
	stmpe811_TS_Start(TS_I2C_ADDRESS);
}

TC_Panel touchpad_read(void)
{
	static int16_t last_x = 0;
	static int16_t last_y = 0;

	uint8_t detected;

	detected = touchpad_get_xy(&TC_status.x, &TC_status.y);
	if(detected)
	{

		last_x = TC_status.x;
		last_y = TC_status.y;

		TC_status.state = TC_PRESSED ;
	}
	else
	{
		TC_status.x = last_x;
		TC_status.y = last_y;
		TC_status.state = TC_RELEASED ;
	}

	return TC_status;
}



//Private functions

static uint8_t touchpad_get_xy(int16_t *x, int16_t *y)
{
	static int32_t _x = 0, _y = 0;
	int16_t xDiff, yDiff, xr, yr;
	uint16_t x_raw, y_raw;;

	uint8_t detected;
	detected = stmpe811_TS_DetectTouch(TS_I2C_ADDRESS);

	if(!detected) return FALSE;


	stmpe811_TS_GetXY(TS_I2C_ADDRESS, &x_raw, &y_raw);

	/* Y value first correction */
	y_raw -= 360;

	/* Y value second correction */
	yr = y_raw / 11;

	/* Return y_raw position value */
	if(yr <= 0) yr = 0;
	else if (yr > TFT_VER_RES) yr = TFT_VER_RES - 1;

	y_raw = yr;

	/* X value first correction */
	if(x_raw <= 3000) x_raw = 3870 - x_raw;
	else  x_raw = 3800 - x_raw;

	/* X value second correction */
	xr = x_raw / 15;

	/* Return X position value */
	if(xr <= 0) xr = 0;
	else if (xr > TFT_HOR_RES) xr = TFT_HOR_RES - 1;

	x_raw = xr;
	xDiff = x_raw > _x? (x_raw - _x): (_x - x_raw);
	yDiff = y_raw > _y? (y_raw - _y): (_y - y_raw);

	if (xDiff + yDiff > 5) {
		_x = x_raw;
		_y = y_raw;
	}

	/* Update the X and Y position */
	*x = _x;
	*y = _y;

	return TRUE;
}

