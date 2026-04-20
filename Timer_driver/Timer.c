/*
 * Timer.c
 *
 *  Created on: Jun 5, 2023
 *      Author: hp
 */

#include "Timer.h"
#define TIM1_BASE 					(0x40012C00)
#define TIM2_BASE 					(0x40000000)

//SELECT CHANNEL IP/OP (CCMR1)
#define CHANNEL1_DIR_BIT 					0x00
#define CHANNEL1_DIR_LEN_MASK 				0x03
//SELECT COUNT MODE (CR1)
#define COUNT_MODE_BIT						0x05
#define COUNT_MODE_LEN_MASK 				0x03
//SELECT COUNT UP/DOWN (CR1)
#define COUNTDIR_BIT			0X04
#define COUNTDIR_LEN_MASK		0X01


#define CHANNEL1_FILTER_BIT			0X04
#define CHANNEL1_FILTER_LEN_MASK	0X03

//SELECT THE POLARITY OF TRIGER RISING/FALLING(CCER)
#define CHANNEL1_TRIGER_BIT			0X01
#define CHANNEL1_TRIGGER_LEN_MASK	0X01

#define CHANNEL1_CAPENABLE_BIT		0X00
#define CHANNEL1_CAPENABLE_LEN_MASK	0X01

typedef struct
{
   uint16_t CR1;
  uint16_t  RESERVED0;
    uint16_t CR2;
  uint16_t  RESERVED1;
    uint16_t SMCR;
  uint16_t  RESERVED2;
    uint16_t DIER;
  uint16_t  RESERVED3;
    uint16_t SR;
  uint16_t  RESERVED4;
    uint16_t EGR;
  uint16_t  RESERVED5;
    uint16_t CCMR1;
  uint16_t  RESERVED6;
    uint16_t CCMR2;
  uint16_t  RESERVED7;
    uint16_t CCER;
  uint16_t  RESERVED8;
    uint16_t CNT;
  uint16_t  RESERVED9;
    uint16_t PSC;
  uint16_t  RESERVED10;
    uint16_t ARR;
  uint16_t  RESERVED11;
    uint16_t RCR;
  uint16_t  RESERVED12;
    uint16_t CCR1;
  uint16_t  RESERVED13;
    uint16_t CCR2;
  uint16_t  RESERVED14;
    uint16_t CCR3;
  uint16_t  RESERVED15;
    uint16_t CCR4;
  uint16_t  RESERVED16;
    uint16_t BDTR;
  uint16_t  RESERVED17;
    uint16_t DCR;
  uint16_t  RESERVED18;
    uint16_t DMAR;
  uint16_t  RESERVED19;
} TIM_Regs;


static volatile TIM_Regs*const TIM2=(volatile TIM_Regs*const)TIM2_BASE;
static void (*IC2_callBack)(void);




void TIM2Init(TIM_Init* Tim2Init)
{
uint16_t tempCR1=TIM2->CR1;



//set countdir
tempCR1 &=~(COUNTDIR_LEN_MASK<<COUNTDIR_BIT);
tempCR1 |=(Tim2Init->CountDir<<COUNTDIR_BIT);

//set count mode
tempCR1 &=~(COUNT_MODE_LEN_MASK<<COUNT_MODE_BIT);
tempCR1 |=(Tim2Init->CountMode<<COUNT_MODE_BIT);
TIM2->CR1=tempCR1;
//set autoreload value

TIM2->ARR=Tim2Init->Reload;

//set prescaler value
TIM2->PSC=Tim2Init->Prescaler;
}
void TIM2IcInit(IC_Init* IC2Init)
{
uint16_t tempCMR1=TIM2->CCMR1;
uint16_t tempCCER=TIM2->CCER;

//select channel dir(OP/IP->(TI1/TI2)) of channel1
if (IC2Init->channel_t==1)
{
tempCMR1 &= ~(CHANNEL1_DIR_LEN_MASK<<CHANNEL1_DIR_BIT);
tempCMR1 |= (IC2Init->channeldir_t<<CHANNEL1_DIR_BIT);
}
//SELECT sampling freq

tempCMR1&=~(CHANNEL1_FILTER_LEN_MASK<<CHANNEL1_FILTER_BIT);
tempCMR1|=(IC2Init->filter_t<<CHANNEL1_FILTER_BIT);
TIM2->CCER=tempCMR1;

//select capture trigger(rising/falling)
tempCCER&=~(CHANNEL1_TRIGGER_LEN_MASK<<CHANNEL1_TRIGER_BIT);
tempCCER|=(IC2Init->trigger_t<<CHANNEL1_TRIGER_BIT);

TIM2->CCER=tempCCER;
}
void enableCapture (void)
{
	TIM2->CCER|=(1<<0);
}

void enableCaptureInterrupt(void)
{
TIM2->DIER |=(1<<1);
}


void TIM2Enable(void)
{
	TIM2->CR1 |= (1<<0);
}


void TIM2_voidCallBack(void(*ptr)(void))
{
	if(ptr!=NULL)
		{
		IC2_callBack=ptr;
		}
}
void TIM2_IRQHandler(void)
{
	IC2_callBack();
}

uint16_t getCapture(void)
{
	return TIM2->CCR1;
}
