/*
 * GPIO.c
 *
 *  Created on: May 26, 2023
 *      Author: hp
 */
#include "GPIO.h"


#define GPIO_PORTA_BASEADDRESS   (0x40010800)
#define GPIO_PORTB_BASEADDRESS   (0x40010C00)
#define GPIO_PORTC_BASEADDRESS   (0x40011000)
#define GPIO_PORTD_BASEADDRESS   (0x40011400)
#define GPIO_PORTE_BASEADDRESS   (0x40011800)
#define GPIO_PORTF_BASEADDRESS   (0x40011C00)
#define GPIO_PORTG_BASEADDRESS   (0x40012000)


#define AFIO_MAPR  (*(volatile uint32_t*)(0x40010004))

#define GPIO_LEN_MASK  0x03

typedef struct
{
	uint32_t CR[2];
//	uint32_t CRH;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t BRR;
	uint32_t LCKR;


}GPIO_t;

#define GPIOA ((volatile GPIO_t*)(GPIO_PORTA_BASEADDRESS))//base address
#define GPIOB ((volatile GPIO_t*)(GPIO_PORTB_BASEADDRESS))//base address
#define GPIOC ((volatile GPIO_t*)(GPIO_PORTC_BASEADDRESS))//base address
#define GPIOD ((volatile GPIO_t*)(GPIO_PORTD_BASEADDRESS))//base address
#define GPIOE ((volatile GPIO_t*)(GPIO_PORTE_BASEADDRESS))//base address
#define GPIOF ((volatile GPIO_t*)(GPIO_PORTF_BASEADDRESS))//base address
#define GPIOG ((volatile GPIO_t*)(GPIO_PORTG_BASEADDRESS))//base address



void GPIO_voidSetPinMode(uint32_t port_t,pin_t pin_t, uint32_t mode_t,uint32_t confg_t,uint32_t confgMode_t)
{
	uint8_t indx;
	if (pin_t>7)
	{
		 indx=1;
	}
	else
	{
		indx=0;
	}

	switch(port_t)
	{
	uint32_t temp;
	case 0://portA

			//assign mode
			temp=GPIOA->CR[indx];
			temp &=~(GPIO_LEN_MASK<<((pin_t)*4));
			temp|=(mode_t<<(pin_t*4));
			GPIOA->CR[indx]=temp;
			//assign cnfg
			temp &= ~(GPIO_LEN_MASK<<(((pin_t)*4)+2));
			temp |=(confg_t<<(((pin_t)*4)+2));
			GPIOA->CR[indx]=temp;
			break;
	case 1://portB
			//assign mode
			temp=GPIOB->CR[indx];
			temp &= ~(GPIO_LEN_MASK<<(pin_t*4));
			temp |=(mode_t<<(pin_t*4));
			//assign cnfg
			temp &= ~(GPIO_LEN_MASK<<((pin_t*4)+2));
			temp |=(confg_t<<((pin_t*4)+2));
			GPIOB->CR[indx]=temp;
			break;
	case 2://portC
			//assign mode
			temp &= ~(GPIO_LEN_MASK<<(pin_t*4));
			temp |=(mode_t<<(pin_t*4));
			//assign cnfg
			temp &= ~(GPIO_LEN_MASK<<((pin_t*4)+2));
			temp |=(confg_t<<((pin_t*4)+2));
			GPIOC->CR[indx]=temp;
			break;

	}
	if ((confg_t==confg_INPT_PU)&&(confgMode_t==1))
	{

		GPIOA->ODR|=(1<<pin_t);
	}
	else if((confg_t==confg_INPT_PD) &&(confgMode_t==0))
	{
		GPIOA->ODR&=~(1<<pin_t);
	}

	else if((confg_t==confg_OTPT_GOD) ||(confg_t==confg_OTPT_GPP))
	{
		GPIOA->ODR&=~(1<<pin_t);
	}

}

//void GPIO_voidSetPinType(uint32_t port_t,pin_t pin_t, uint32_t confg_t)
//{
//
//	uint8_t indx=3;
//		if (pin_t>7)
//		{
//			 indx=1;
//		}
//		else
//		{
//			indx=0;
//		}
//
//	switch(port_t)
//		{
//		case 0:
//			GPIOA->CRL &= ~(GPIO_LEN_MASK<<((pin_t*4)+2));
//			GPIOA->CRL |=(confg_t<<((pin_t*4)+2));
//			break;
//		case 1:
//			GPIOB->CRL &= ~(GPIO_LEN_MASK<<((pin_t*4)+2));
//			GPIOB->CRL |=(confg_t<<((pin_t*4)+2));
//			break;
//		case 2:
//			GPIOC->CRL &= ~(GPIO_LEN_MASK<<((pin_t*4)+2));
//			GPIOC->CRL |=(confg_t<<((pin_t*4)+2));
//			break;
//
//
//		}
//}
void GPIO_voidOutputData(uint32_t data,uint32_t port_t,pin_t pin_t)
{

	switch(port_t)
			{
			case 0:
				GPIOA->ODR &= ~(GPIO_LEN_MASK<<((pin_t*4)+2));
				GPIOA->ODR |=(data<<(pin_t));
				break;
			case 1:
				GPIOB->ODR &= ~(GPIO_LEN_MASK<<((pin_t*4)+2));
				GPIOB->ODR |=(data<<(pin_t));
				break;
			case 2:
				GPIOC->ODR &= ~(GPIO_LEN_MASK<<((pin_t*4)+2));
				GPIOC->ODR |=(data<<(pin_t));
				break;


			}
}

void GPIO_voidSetPin(uint32_t port_t,pin_t pin_t)
{
	switch(port_t)
				{
				case 0:
					GPIOA->BSRR |=(1<<(pin_t));
					break;
				case 1:
					GPIOB->BSRR |=(1<<(pin_t));
					break;
				case 2:
					GPIOC->BSRR |=(1<<(pin_t));
					break;


				}
}

void GPIO_voidResetPin(uint32_t port_t,pin_t pin_t)
{
	switch(port_t)
				{
				case 0:
					GPIOA->BSRR |=(1<<(pin_t+16));
					break;
				case 1:
					GPIOB->BSRR |=(1<<(pin_t+16));
					break;
				case 2:
					GPIOC->BSRR |=(1<<(pin_t+16));
					break;


				}
}

void Tim2AFRemap(void)
{
	uint32_t temp=AFIO_MAPR;
	temp &= ~(0x03<<0x08);
	temp |= (0b00<<0x08);
	AFIO_MAPR=temp;
}
