/*
 * EXTI.c
 *
 *  Created on: Jun 3, 2023
 *      Author: hp
 */

#include"EXTI.h"
#define EXTI_BASEADDRESS	(0x40010400)

#define EXTI_CFGR_BASEADDRESS (0x40010000)

#define EXTI_CFGR_LENMASK  (0b1111)

typedef struct
{
uint32_t IMR;
uint32_t EMR;
uint32_t RTSR;
uint32_t FTSR;
uint32_t SWIER;
uint32_t PR;
}EXTI_Regs;

typedef struct
{
	uint32_t AFIO[4];
}EXTI_CFG_Regs;

static volatile  EXTI_Regs* const EXTI=(volatile  EXTI_Regs* const) EXTI_BASEADDRESS;
static volatile  EXTI_CFG_Regs* const EXTI_CFG=(volatile  EXTI_Regs* const) EXTI_CFGR_BASEADDRESS;

static void (*EXTI0_callBack)(void);//static global pointer to func to limit the scope
static void (*EXTI1_callBack)(void);//static global pointer to func to limit the scope
void EXTI_enableInterrupt(line_t line_t)
{
	if ((line_t>=0) && (line_t <= 15))
		{
			EXTI->IMR|= 1<<line_t;
		}
}
void EXTI_disableInterrupt(line_t line_t)
{
	if ((line_t>=0) && (line_t <= 15))
		{
			EXTI->IMR &=~(1<<line_t);
		}
}

void EXTI_softwatreInterrupt(line_t line_t)
{
	if ((line_t>=0) && (line_t <= 15))
			{
		EXTI->SWIER|=line_t;
			}
}

void EXTI_setTrigerSource(line_t line_t,EXTI_trigger trig_t)
{
	switch (trig_t)
	{
	case 0: //rising
		EXTI->RTSR |=1<<line_t;
		EXTI->FTSR &=~(1<<line_t);
		break;
	case 1: //falling
		EXTI->FTSR |=1<<line_t;
		EXTI->RTSR &=~(1<<line_t);
		break;
	case 2: //onChange
		EXTI->RTSR |=(1<<line_t);
		EXTI->FTSR |=(1<<line_t);
		break;
	}
}

void EXTI_setConfig(line_t line_t,uint8_t port_t)
{
	uint8_t selectReg= line_t/4;
	uint8_t selectBit= (line_t%4)*4;

//	EXTI_CFG->AFIO[selectReg]

	uint32_t temp=EXTI_CFG->AFIO[selectReg];
	temp&= ~(EXTI_CFGR_LENMASK<<selectBit);
	temp|=(port_t<<selectBit);
	EXTI_CFG->AFIO[selectReg]=temp;
}


void EXTI0_voidCallBack(void(*ptr)(void))
{
	if(ptr!=NULL)
	{
		EXTI0_callBack=ptr;
	}
}
void EXTI0_IRQHandler(void)
{
	EXTI0_callBack();//for pointer to func we call this pointer as a func to call the func it is pointing at
	EXTI->PR |=(1<<line_0);//must write 1 to the pending reg to clear it
}

void EXTI1_voidCallBack(void(*ptr)(void))
{
	if(ptr!=NULL)
	{
		EXTI1_callBack=ptr;
	}
}
void EXTI1_IRQHandler(void)
{
	EXTI1_callBack();//for pointer to func we call this pointer as a func to call the func it is pointing at
	EXTI->PR |=(1<<line_1);//must write 1 to the pending reg to clear it
}
