/*
 * auxiliary.c
 *
 *  Created on: Apr 15, 2021
 *      Author: Islam
 */
#include "auxiliary.h"

static Aux aux_var ;

void Assign_smallFun(void (*fun)(void))
{
	aux_var.SmallTasks = fun ;
}

Aux *Get_AuxiliaryStatus(void)
{
	return &aux_var ;
}
