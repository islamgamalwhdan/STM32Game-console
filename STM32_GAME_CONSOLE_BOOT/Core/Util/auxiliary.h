/*
 * auxiliary.h
 *
 *  Created on: Apr 15, 2021
 *      Author: Islam
 */

#ifndef SRC_AUXILIARY_H_
#define SRC_AUXILIARY_H_

typedef struct aux_
		{
	         void (*SmallTasks)(void);
		}Aux;


void Assign_smallFun(void (*)(void) );
Aux *Get_AuxiliaryStatus(void);
#endif /* SRC_AUXILIARY_H_ */
