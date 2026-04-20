/*
 * Timer.h
 *
 *  Created on: Jun 7, 2023
 *      Author: hp
 */

#ifndef TIMER_DRIVER_TIMER_H_
#define TIMER_DRIVER_TIMER_H_


#include<stdint.h>
#include "stdio.h"
typedef struct
{
uint16_t CountMode;
uint16_t CountDir;
uint16_t Reload;
uint16_t Prescaler;
}TIM_Init;

typedef struct
{
	uint16_t channel_t;
	uint16_t filter_t;
	uint16_t channeldir_t;
	uint16_t captureEnable_t;
	uint16_t trigger_t;
}IC_Init;


//void TI1Config()
void TIM2DeInit(void);//use RCC reset func. inside
/*
 * @brief:the user selects (through a pointer to TIM_Init struct) the
 * CR1->counter mode,Direction
 * ARR->Reload value
 * PSC->Prescaler
 * @param:pointer to pointer to TIM_Init struct
 */
void TIM2Init(TIM_Init* Tim2Init);
/*
 * @brief:the user selects (through a pointer to IC_Init struct) the
 * CCMR->IC channel select CC1S,IC filter
 * CCER->IC polarity(Rising or falling trigger) CC1P,IC enable CC1E
 */
void TIM2IcInit(IC_Init* IC2Init);

void TIM2_voidCallBack(void(*ptr_func)(void));
void enableCapture (void);
void enableCaptureInterrupt(void);
void TIM2Enable(void);
uint16_t getCapture(void);
#endif /* TIMER_DRIVER_TIMER_H_ */
