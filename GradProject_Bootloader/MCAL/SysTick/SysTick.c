/*
 * SYSTEC.c
 *
 *  Created on: Jun 14, 2023
 *      Author: Muham
 */


#include "SysTick.h"

/* Defining SysTick base address*/
#define SYSTICK_BASEADDRESS 				(0xE000E010)
/**********************************************************************************************************/

#define CLKSOURCE_BIT	2
#define INT_ENABLE_BIT	1
#define ENABLE_BIT 		0
#define STK_LOAD_MASK 0x00FFFFFFFFFF

typedef struct
{
	volatile u32 STK_CTRL;
	volatile u32 STK_LOAD;
	volatile u32 STK_VAL;
	volatile u32 STK_CALIB;
}SysTick_t;

static volatile SysTick_t * const systick = (volatile SysTick_t * const) SYSTICK_BASEADDRESS ;

//static ptrCBK systkCBK=NULL;
static void (* systkCBK)(void)=NULL;


void SysTick_Start(void)
{
	if (SYS_TICK_PRESCALLER == AHB)
		systick->STK_CTRL |=(1<<CLKSOURCE_BIT);
	else if (SYS_TICK_PRESCALLER == AHB_DIVIDE_8)
		systick->STK_CTRL &=~(1<<CLKSOURCE_BIT);

	systick->STK_CTRL |=(1<<INT_ENABLE_BIT);
	systick->STK_CTRL |=(1<<ENABLE_BIT);
}

void SysTick_Stop(void)
{
	systick->STK_CTRL &=~(1<<ENABLE_BIT);
}

void SysTick_DelayMS(u32 DelayMS)
{
	if (SYS_TICK_PRESCALLER == AHB_DIVIDE_8)
	{
		/* System clock = 16/8 = 2 MHZ */
		/* convert from Micro second to milli second */
		DelayMS =DelayMS*2000;
		systick->STK_LOAD = DelayMS;
	}
}

void SysTick_CallBack(void(* systk)(void))
{
	if (systk != NULL)
	{
		systkCBK=systk;
	}
}
void SysTick_Handler(void)
{
	if (systkCBK != NULL)
	{
		systkCBK();
	}
}





