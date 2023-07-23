/*
 * Math_lib.c
 *
 *  Created on: Jan 5, 2023
 *      Author: Islam
 */


#include "Math_lib.h"
#include "STMGame_types.h"

#include "math.h"

#define PI (3.1428f)

static float Sin_table[360] ;
static float Cos_table[360] ;


void Init_TrigoTables(void)
{
	for(int i = 0 ; i < 360 ; i++)
	    {
		     Sin_table[i] = sin(i*PI/180.0);
		     Cos_table[i] = cos(i*PI/180.0);
	    }
}

float Fast_Sin(float angle)
{
	angle = fmod(angle,360) ;

	if(angle < 0) angle += 360.0f ;

	u16   INT_angle = (u16)angle ;
	float frc_angle = angle - INT_angle ;

	return  Sin_table[INT_angle] +
			frc_angle*( Sin_table[INT_angle+1] - Sin_table[INT_angle]  ) ;
}



float Fast_Cos(float angle)
{
	angle = fmod(angle,360) ;

	if(angle < 0) angle += 360.0f ;

	u16   INT_angle = (u16)angle ;
	float frc_angle = angle - INT_angle ;

	return  Cos_table[INT_angle] +
			frc_angle*( Cos_table[INT_angle+1] - Cos_table[INT_angle]  ) ;
}
