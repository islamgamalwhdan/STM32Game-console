/*
 * util_spe.c
 *
 *  Created on: Nov 19, 2022
 *      Author: Islam
 */


#include "STMGame.h"

extern RNG_HandleTypeDef hrng ;

 uint32_t Rand_num(void)
{
	 if (HAL_RNG_GenerateRandomNumber(&hrng, &(hrng.RandomNumber)) == HAL_OK)
	   {
	     return hrng.RandomNumber;
	   }
	   else
	   {
	     return 0U;
	   }
}
