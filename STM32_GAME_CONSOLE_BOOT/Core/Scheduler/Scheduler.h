/*
 * Scheduler.h
 *
 *  Created on: Mar 22, 2021
 *      Author: Islam
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>

/******************************************************************************
* Constants
*******************************************************************************/

#define SYS_TICK_INTERVAL     1000UL  //1000us sec means 1ms

#define INTERVAL_10MS        (10000UL / SYS_TICK_INTERVAL)


#define INTERVAL_16MS        (16667UL / SYS_TICK_INTERVAL)
/**
 * The interval to call the 16 ms tasks (~60Hz)
 */
#define INTERVAL_20MS        (20000UL / SYS_TICK_INTERVAL)

/**
 * The interval to call the 66ms (~15Hz)  tasks
 */
#define INTERVAL_30MS       (30000UL / SYS_TICK_INTERVAL)

/**
 * The interval to call the 1000 ms tasks
 */
#define INTERVAL_1000MS       (1000000UL / SYS_TICK_INTERVAL)
#define MAIN_INTERVAL             (0)

/******************************************************************************
* Typedefs
*******************************************************************************/

typedef struct
{
	void (*Func)(void);			/**< Function pointer to the task  */
  	uint16_t Interval;			/**< Defines how often a task will run  */
  	uint32_t LastTick;			/**< Stores the last tick task was ran  */
}TaskConfigType;


void Run_Scheduler(void);
//void Add_Task( void(*Ptask)(void) , uint16_t interval );
void Delete_Task( void(*Ptask)(void));
void SCH_Dispatch(void);
void SCH_AddHandlerTable(TaskConfigType* CfgTable , uint8_t size);
#endif /* INC_SCHEDULER_H_ */
