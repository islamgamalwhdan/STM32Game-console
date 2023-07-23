/*
 * gyroscope.h
 *
 *  Created on: Apr 23, 2021
 *      Author: Islam
 */

#ifndef GYROSCOPE_H_
#define GYROSCOPE_H_


#include "stdint.h"

typedef struct
{
	float x , y ,z ;
}GYRO_RD;

typedef struct
{
	float x , y , z ;
}GYRO_Angle;

uint8_t GYRO_Init(void);
void GYRO_Reset(void);
void GYRO_GetXYZ(int16_t *rd);
void GYRO_Calibaration(void) ;
void GYRO_AngleXYZ(GYRO_Angle* Pangle);

#endif /* GYROSCOPE_H_ */
