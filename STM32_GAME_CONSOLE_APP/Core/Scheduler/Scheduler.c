/*
 * Scheduler.c
 *
 *  Created on: May 12, 2021
 *      Author: Islam
 */

/* Includes ------------------------------------------------------------------*/
#include "STMGame.h"
#include "Scheduler.h"


//static TaskType Tasks[MAX_TASKS];
static TaskConfigType* TasksTable ;        //Pointer to configuration table from app layer
static uint8_t TableSize;
/* Private Functions ------------------------------------------------------------------*/

#if 0
static int8_t Tsk_GetNumTasks(void)
{
    uint32_t task_count = 0 ;
	for(uint32_t i = 0 ; i< MAX_TASKS ; i++ )
		{
		     if(Tasks[i].Func) task_count++ ;
		}
	return task_count ;
}

/* Public Functions ------------------------------------------------------------------*/

void Add_Task( void(*Ptask)(void) , uint16_t interval )
{
	static uint16_t tsk_cnt =0 ;

	Tasks[tsk_cnt].Func     = Ptask ;
	Tasks[tsk_cnt].Interval = interval ;
	Tasks[tsk_cnt].LastTick = 0 ;
	tsk_cnt++ ;
}
#endif

void SCH_AddHandlerTable(TaskConfigType* CfgTable , uint8_t size)
{
	TasksTable = CfgTable ;
	TableSize = size ;
}

void Delete_Task( void(*Ptask)(void))
{
	for(uint8_t i = 0 ; i < TableSize ; i++ )
	{
		if(TasksTable[i].Func)
		{
			if(TasksTable[i].Func == Ptask) TasksTable[i].Func = NULL ;
		}
	}
}

void Setup_Scheduler(void)
{

}
void SCH_Dispatch(void)
{
	uint32_t tick = HAL_GetTick();    // Get current system tick
	//uint32_t NumTasks = Tsk_GetNumTasks() ;

	// Loop through all tasks.  First, run all continuous tasks.  Then,
	// if the number of ticks since the last time the task was run is
	// greater than or equal to the task interval, execute the task.
	for(uint32_t TaskIndex = 0; TaskIndex < TableSize ; TaskIndex++)
	        {
	          if(TasksTable[TaskIndex].Interval == 0)
	          {
	            // Run continuous tasks.
	            (TasksTable[TaskIndex].Func)();
	          }
	         else if((tick - TasksTable[TaskIndex].LastTick) >= TasksTable[TaskIndex].Interval)
	          {
	            (TasksTable[TaskIndex].Func)();         // Execute Task

	            TasksTable[TaskIndex].LastTick = tick;  // Save last tick the task was ran.
	          }
	        }
}




