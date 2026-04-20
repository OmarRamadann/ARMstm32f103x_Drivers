
#include<stdint.h>
#include "MCAL/STM32F401C8T6/STM32F401C8T6.h"
#include "MCAL/FLASH/FLASH.h"
#include "MCAL/RCC/RCC.h"
#include "MCAL/USART/USART.h"
#include "MCAL/SysTick/SysTick.h"
#include "MCAL/GPIO/GPIO.h"


uint8_t recBuffer[100]={0};
uint8_t recCounter=0;
uint8_t timeOutFlag=0;
uint8_t writeRequest=1;
uint8_t systickflag=1;


extern void Parser_voidParseRecord(u8 * RecordBuffer);

typedef void (*ptrCBK)(void); //define pointer to func type
ptrCBK addrsToCall=0;

void func(void)
{
#define SCB_VTOR   *((volatile u32*)0xE000ED08)

	SCB_VTOR = 0x08008000;

	addrsToCall= *(ptrCBK *)0x08008004;	//32k
	addrsToCall();
}


void main()
{

	//todo:enable HSI sysclk
	uint8_t recStatus;
	/* Enable HSI clock */
	MRCC_voidSetCLKSatus(CLK_HSI, STATUS_ENABLE);
	if(MRCC_u8CheckClkSourceReady(CLK_RDY_HSI) == CLK_SOURCE_READY)
	{
		MRCC_voidSetClkSource(sys_clk_HSI);
		MRCC_voidSetCLKSatus(CLK_HSE, STATUS_DISABLE);
		MRCC_voidSetCLKSatus(CLK_PLL, STATUS_DISABLE);
	}

	//todo:enable RCC UART
	//todo:enable RCC PORTA
	//todo:enable RCC FBEC (flash driver) // For M3 only

	MRCC_voidSetPeripheralStaus(Bus_AHB1,AHB1_GPIOA , STATUS_ENABLE);
	MRCC_voidSetPeripheralStaus(Bus_APB2,APB2_USART1 , STATUS_ENABLE);


	//todo:enable GPIO pinmode pin9 TX AFPP
	//todo:enable GPIO pinmode pin10 RX Input FLT

	GPIO_PinConfig_t PinConfigTX9=
	{.PinNumber=PIN9,
	 .PinMode=Mode_OutputAFPP,
	 .OutputSpeed=Speed_Low
	};

	GPIO_PinConfig_t PinConfigRX10=
	{.PinNumber=PIN10,
	 .PinMode=Mode_OutputAFPP,
	 .OutputSpeed=Speed_Low
	};

	 MGPIO_Init(GPIOA, & PinConfigTX9);
	 //MGPIO_SetAlternateFun(GPIOA,PIN9, AF7);
	 MGPIO_Init(GPIOA, & PinConfigRX10);
	 //MGPIO_SetAlternateFun(GPIOA,PIN10 , AF7);
	 *&GPIOA->AFRH=0x00000770;



	//todo:USART_voidInit(); //start the uart with baud rate 9600 ,start TX&RX
	  MUSART_voidInit(USART_1);
	//todo:sysTck_voidInit();
	  SysTick_DelayMS(15000);
	  SysTick_CallBack(func);
	  //todo:sysTck_voidSetIntervalSingle(15000000,func);//start systck for 15 sec and after them jump to func (app code)
	  SysTick_Start();

		//MUSART_Error_tSendStringSync(USART_1, "ok" , 5000);


	 while(timeOutFlag==0)
	{
		//recStatus=USART_u8Receive(& recBuffer[recCounter]);//put the received data in the array

		 recBuffer[recCounter] =MUSART_u8ReceiveByteSync(USART_1,5000,&recStatus);

		 if (recStatus==1)//that means data received
		{
			//todo:sysTck_voidStop();
			 SysTick_Stop();

			if (recBuffer[recCounter]=='\r')//reached the end of the hex line
			{
				if (writeRequest==1)
				{
					//todo:FBEC_voidEraseApp();
					MFLASH_voidAreaErase();
					writeRequest=0;
				}

				//parse
				//todo:parser_parseRecord(recBuffer);
				Parser_voidParseRecord(recBuffer);
				//todo:USART_voidTransmit("ok");//to tell the serial tool to send the second line
				MUSART_Error_tSendStringSync(USART_1, "ok" , 5000);
				recCounter=0;//to start to fill the array from the beginning

			}
			else
			{
				recCounter++;
			}
			//todo:sysTck_voidSetIntervalSingle(15000000,func);//start systck for 15 sec and after them jump to func (app code)
			if(systickflag == 1)
			{
				systickflag=0;
				SysTick_DelayMS(30000);
				SysTick_CallBack(func);
				SysTick_Start();
			}
		}
		else
		{


		}
	}

}



// ----------------------------------------------------------------------------
