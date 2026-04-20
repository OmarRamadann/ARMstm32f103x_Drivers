/////////*
//////// * UART_Check.c
//////// *
//////// *  Created on: Jun 16, 2023
//////// *      Author: Muham
//////// */
////////
////////
////#include<stdint.h>
////#include "MCAL/STM32F401C8T6/STM32F401C8T6.h"
////#include "MCAL/FLASH/FLASH.h"
////#include "MCAL/RCC/RCC.h"
////#include "MCAL/USART/USART.h"
////#include "MCAL/SysTick/SysTick.h"
////#include "MCAL/GPIO/GPIO.h"
////
////uint8_t recBuffer[100]={0};
////uint8_t recCounter=0;
////uint8_t timeOutFlag=0;
////uint8_t writeRequest=1;
////
////
////
////void main ()
////{
////	//todo:enable HSI sysclk
////	uint8_t recStatus;
////	/* Enable HSI clock */
////	MRCC_voidSetCLKSatus(CLK_HSI, STATUS_ENABLE);
////	if(MRCC_u8CheckClkSourceReady(CLK_RDY_HSI) == CLK_SOURCE_READY)
////	{
////		MRCC_voidSetClkSource(sys_clk_HSI);
////		MRCC_voidSetCLKSatus(CLK_HSE, STATUS_DISABLE);
////		MRCC_voidSetCLKSatus(CLK_PLL, STATUS_DISABLE);
////	}
////
////	//todo:enable RCC UART
////	//todo:enable RCC PORTA
////	//todo:enable RCC FBEC (flash driver) // For M3 only
////	MRCC_voidSetPeripheralStaus(Bus_AHB1,AHB1_GPIOA , STATUS_ENABLE);
////	MRCC_voidSetPeripheralStaus(Bus_APB2,APB2_USART1 , STATUS_ENABLE);
////
////
////	//todo:enable GPIO pinmode pin9 TX AFPP
////	//todo:enable GPIO pinmode pin10 RX Input FLT
////
////	GPIO_PinConfig_t PinConfigTX9=
////	{.PinNumber=PIN9,
////			.PinMode=Mode_OutputAFPP,
////			.OutputSpeed=Speed_Low
////	};
////
////	GPIO_PinConfig_t PinConfigRX10=
////	{.PinNumber=PIN10,
////			.PinMode=Mode_OutputAFPP,
////			.OutputSpeed=Speed_Low
////	};
////
////	MGPIO_Init(GPIOA, & PinConfigTX9);
////	//MGPIO_SetAlternateFun(GPIOA,PIN9, AF7);
////	*&GPIOA->AFRH=0x00000770;
////	MGPIO_Init(GPIOA, & PinConfigRX10);
////	//MGPIO_SetAlternateFun(GPIOA,PIN10 , AF7);
////	v_u8 glal;
////	MUSART_voidInit(USART_1);
////	 glal =MUSART_u8ReceiveByteSync(USART_1,5000,&recStatus);
////	 //MUSART_Error_tSendStringSync(USART_1,"Aaa" , 5000);
////
////
////
////	while(1)
////	{
////		 MUSART_Error_tSendByteSync(USART_1,'A', 5000);
////		 MUSART_Error_tSendByteSync(USART_1,'A', 5000);
////
////		//MUSART_Error_tSendStringSync(USART_1, "ok" , 5000);
////
////	}
////
////}
//////
//////
//////
//////#include "MCAL/FLASH/FLASH.h"
//////#include "stdint.h"
//////
//////
//////int main()
//////{
//////
//////	uint16_t arr[6]={0b000001010010001,8,3,5,9,2};
//////	MFLASH_voidAreaErase();
//////	MFLASH_voidWrite(0x08008000, arr, 6);
//////
//////	volatile int var=50;
//////
//////	while(1)
//////	{
//////		var ++;
//////
//////			if (var == 55)
//////			{
//////				MFLASH_voidAreaErase();
//////				arr[0]=22;
//////				arr[1]=50;
//////				arr[2]=70;
//////				arr[3]=40;
//////				arr[4]=50;
//////				MFLASH_voidWrite(0x08008000, arr, 6);
//////
//////
//////			}
//////
//////	}
//////
//////}
//////
//////
//////
//////
/////
/////
/////
/////
//
//
//
//
//
//#include <stdio.h>
//#include <stdlib.h>
//#include "diag/Trace.h"
//
//
//
//#include<stdint.h>
//#include "MCAL/STM32F401C8T6/STM32F401C8T6.h"
//#include "MCAL/FLASH/FLASH.h"
//#include "MCAL/RCC/RCC.h"
//#include "MCAL/USART/USART.h"
//#include "MCAL/SysTick/SysTick.h"
//#include "MCAL/GPIO/GPIO.h"
//
//void func(void);
//
//
//
//void main()
//{
//		MRCC_voidSetCLKSatus(CLK_HSI, STATUS_ENABLE);
//		if(MRCC_u8CheckClkSourceReady(CLK_RDY_HSI) == CLK_SOURCE_READY)
//		{
//			MRCC_voidSetClkSource(sys_clk_HSI);
//			MRCC_voidSetCLKSatus(CLK_HSE, STATUS_DISABLE);
//			MRCC_voidSetCLKSatus(CLK_PLL, STATUS_DISABLE);
//		}
//
//	/*GPIO_INIT*/
////	MRCC_ret_tEnablePeripheralClk(peri_AHB1_GPIOA,peri_busAHB1);
////	MRCC_ret_tEnablePeripheralClk(peri_APB2_USART1,peri_busAPB2);
//
//		MRCC_voidSetPeripheralStaus(Bus_AHB1,AHB1_GPIOA , STATUS_ENABLE);
//		MRCC_voidSetPeripheralStaus(Bus_APB2,APB2_USART1 , STATUS_ENABLE);
//
////	GPIO_SetPinMode(GPIO_PORTA,GPIO_PIN9,GPIO_MODE_ALF);
////	GPIO_SetPinMode(GPIO_PORTA,GPIO_PIN10,GPIO_MODE_ALF);
//
//
//		GPIO_PinConfig_t PinConfigTX9=
//		{.PinNumber=PIN9,
//				.PinMode=Mode_OutputAFPP,
//				.OutputSpeed=Speed_Low
//		};
//
//		GPIO_PinConfig_t PinConfigRX10=
//		{.PinNumber=PIN10,
//				.PinMode=Mode_OutputAFPP,
//				.OutputSpeed=Speed_Low
//		};
//
//		MGPIO_Init(GPIOA, & PinConfigTX9);
//		//MGPIO_SetAlternateFun(GPIOA,PIN9, AF7);
//		*&GPIOA->AFRH=0x00000770;
//		MGPIO_Init(GPIOA, & PinConfigRX10);
//		//MGPIO_SetAlternateFun(GPIOA,PIN10 , AF7);
//
//
//
////	GPIO_SetAlternativeFunction(GPIO_PORTA,GPIO_PIN9,GPIO_AF7);
////	GPIO_SetAlternativeFunction(GPIO_PORTA,GPIO_PIN10,GPIO_AF7);
//
//
//	//GPIO_SetPinMode(GPIO_PORTA,GPIO_PIN2,GPIO_MODE_OUTPUT);
//
//	MUSART_voidInit(USART_1);
//
//	while(1)
//	{
//		MUSART_Error_tSendStringSync(USART_1,"ABC ",5000);
//	}
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
