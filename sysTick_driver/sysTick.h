/*
 * sysTick.h
 *
 *  Created on: Jun 17, 2023
 *      Author: hp
 */

#ifndef SYSTICK_DRIVER_SYSTICK_H_
#define SYSTICK_DRIVER_SYSTICK_H_

#include<stdint.h>

typedef void (*systickCbf_t)(void);

extern void systick_start(void);
extern void systick_stop(void);
extern void systick_setPeriodMs(uint8_t periodMs);
extern void systick_setCbf(systickCbf_t cbf);

#endif /* SYSTICK_DRIVER_SYSTICK_H_ */
