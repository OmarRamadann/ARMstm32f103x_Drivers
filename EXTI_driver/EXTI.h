/*
 * EXTI.h
 *
 *  Created on: Jun 3, 2023
 *      Author: hp
 */

#ifndef EXTI_DRIVER_EXTI_H_
#define EXTI_DRIVER_EXTI_H_
#include "stdint.h"
#include "stdio.h"


#define PORT_A_EXTI		0b0000
#define PORT_B_EXTI		0b0001
#define PORT_C_EXTI		0b0010

typedef enum
{
line_0,
line_1,
line_2,
line_3,
line_4,
line_5,
line_6,
line_7,
line_8,
line_9,
line_10,
line_11,
line_12,
line_13,
line_14,
line_15
}line_t;

//typedef enum
//{
//	portA,
//	portB,
//	portC
//}EXTI_Port;
typedef enum
{
	trig_rising,
	trig_falling,
	trig_onChange
}EXTI_trigger;

void EXTI_enableInterrupt(line_t line_t);
void EXTI_disableInterrupt(line_t line_t);
void EXTI_softwatreInterrupt(line_t line_t);
void EXTI_setTrigerSource(line_t line_t,EXTI_trigger trig_t);
void EXTI_setConfig(line_t line_t,uint8_t port_t);
void EXTI0_voidCallBack(void(*ptr)(void));
void EXTI1_voidCallBack(void(*ptr)(void));


#endif /* EXTI_DRIVER_EXTI_H_ */
