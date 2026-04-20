/*
 * sched.h
 *
 *  Created on: Jun 17, 2023
 *      Author: hp
 */

#ifndef SCHEDULER_SCHED_H_
#define SCHEDULER_SCHED_H_

#include<stdint.h>
#include "sched_cfg.h"

typedef struct
{
	void (*runnable)(void);
	uint32_t periodMs;
	uint32_t priority;
	char*name;
}runnable_t;

void sched_registerRunnable(runnable_t* userRunnable);

#endif /* SCHEDULER_SCHED_H_ */
