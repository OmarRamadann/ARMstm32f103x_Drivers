#include "TIMER.h"
#include "../RCC/RCC.h"
#include "../GPIO/GPIO.h"



void MTIMER3_Init(u8 Chanel)
{
	GPIO_t* GPIOx = NULL;
	GPIO_PinConfig_t PinConfig = {.PinMode = Mode_OutputAFPP, .OutputSpeed = Speed_High};
	switch (Chanel)
	{
		case Chanel_1:
			GPIOx = GPIOA;
			PinConfig.PinNumber = PIN6;
			break;
		case Chanel_2:
			GPIOx = GPIOA;
			PinConfig.PinNumber = PIN7;
			break;
		case Chanel_3:
			GPIOx = GPIOB;
			PinConfig.PinNumber = PIN0;
			break;
		case Chanel_4:
			GPIOx = GPIOB;
			PinConfig.PinNumber = PIN1;
			break;
	}
	u8 ClockPort = (GPIOx == GPIOA) ? AHB1_GPIOA : AHB1_GPIOB;
	MRCC_voidSetPeripheralStaus(Bus_AHB1, ClockPort, STATUS_ENABLE);
	MGPIO_Init(GPIOx, &PinConfig);
	MGPIO_SetAlternateFun(GPIOA, PinConfig.PinNumber, AF2);

	/*Enable Timer3 clock to be 16 / 8 = 2 MHz*/
	MRCC_voidSetBusPrescaler(Bus_APB1, PRESCALER_APB_8);
	MRCC_voidSetPeripheralStaus(Bus_APB1, APB1_TIM3, STATUS_ENABLE);
}

void MTimer_GeneratePWM(TIMER_t* Timer, u32 Frequency, u16 Duty)
{
	/* Set Capture/Compare 1 as output */
	Timer->CCMR1 &= ~TIMER_CCMR1_CC1S;

	/*Configure the output compare channel for PWM mode1*/
	Timer->CCMR1 |= (TIMER_CCMR1_OC1M_1 | TIMER_CCMR1_OC1M_2);

	/* Output Compare 1 preload enable */
	Timer->CCMR1 |= TIMER_CCMR1_OC1PE;

	/*Set counter direction as up-counter*/
	Timer->CR1 &= ~(TIMER_CR1_DIR | TIMER_CR1_CMS);

	/*Enable Auto-reload preload */
	Timer->CR1 |= TIMER_CR1_ARPE;

	Timer->CCER |= TIMER_CCER_CC1E;

	/*Configure the timer prescaler and period to generate the desired frequency*/
	Timer->PSC = Timer_Clk / Frequency - 1;
	Timer->ARR = ARR_Value;

	/*Set the initial duty cycle*/
	Timer->CCR1 = ARR_Value * Duty / Max_Duty;

	/* Initialize all the registers */
	Timer->EGR |= TIMER_EGR_UG;

	/*Start the counter*/
	Timer->CR1 |= TIMER_CR1_CEN;
}
