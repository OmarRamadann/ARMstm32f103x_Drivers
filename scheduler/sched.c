/*
 * sched.c
 *
 *  Created on: Jun 17, 2023
 *      Author: hp
 */

#include "sched.h"
#include "../sysTick_driver/sysTick.h"
#include<stdlib.h>


#define MAX_RUNNABLES	10


static struct
{
	uint32_t size;
	runnable_t *runnable[MAX_RUNNABLES];//create a pointer to the struct created in .h
}userRunnables;

static uint8_t isReady;
static void schedReady(void);
static void scheduler(void);


void sched_init (void)
{
	systick_setPeriodMs(TICK_MS);
	systick_setCbf(schedReady);

}

void sched_start(void)
{
	systick_start();
	while(1)
	{
		if (isReady)
		{
			isReady=0;
			scheduler();//now the scheduler runs in thread mode not handler mode
		}
	}
}
void sched_registerRunnable(runnable_t* userRunnable)
{
	if (userRunnable!=NULL)
	{
		if(userRunnables.size<MAX_RUNNABLES)
		{
			userRunnables.runnable[userRunnable->priority]=userRunnable;//add this runnable in the array of runnables according to its priority
			userRunnables.size++;
		}
	}
}
static void schedReady(void)//make this func to avoid that the system runs in the systick interrupt through the scheduler func without other int takes place
{
	isReady=1;
}
static void scheduler(void)
{

//loop on runnables and check if its time
	static uint32_t timeMs;
	uint32_t idx;

	for(idx=0;idx<MAX_RUNNABLES;idx++)
	{
		if(userRunnables.runnable[idx]!=NULL)
		{
			if((timeMs% userRunnables.runnable[idx]->periodMs)==0)
			{
				userRunnables.runnable[idx]->runnable();
			}
		}
	}
	timeMs=TICK_MS;
}
