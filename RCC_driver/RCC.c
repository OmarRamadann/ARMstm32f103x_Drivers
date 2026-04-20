//includes
#include "RCC.h"
#include <diag/Trace.h>

//defines
#define RCC_BASE  0x40021000
//pllMull bits
#define pllMull_BIT 		0x12
#define pllMull_LEN_MASK	0x0F

//pll bits
#define pllsrc_BIT           0x10
#define pllsrc_LEN_MASK      0x01

//sysclk bits
#define sysclk_BIT           0x00
#define sysclk_LEN_MASK      0x03

//AHB bits
#define AHB_BIT				0x04
#define AHB_LEN_MASK		0x0F

//APB1 bits
#define APB1_BIT			0x08
#define APB1_LEN_MASK		0x0B

//APB2 bits
#define APB2_BIT			0x0B
#define APB2_LEN_MASK		0x0B

//types
typedef struct
{
	uint32_t CR;
	uint32_t CFGR;
	uint32_t CIR;
	uint32_t APB2RSTR;
	uint32_t APB1RSTR;
	uint32_t AHBENR;
	uint32_t APB2ENR;
	uint32_t APB1ENR;
	uint32_t BDCR;
	uint32_t CSR;
}RCC_Regs;

//typedef enum{
//    res_OK,
//    res_ERROR,
//    res_ARGS,
//    res_NULL
//}res_t;

//variables
static volatile RCC_Regs*const RCC=(volatile RCC_Regs*const)RCC_BASE;








//static functions prototypes
void select_pll(void);
uint32_t pllMull_usb(uint32_t pllMull, uint32_t pllUsbDiv);
void RCC_CFGR_func(uint32_t LEN_MASK,uint32_t BIT,uint32_t user_select );

//interface functions implementation
res_t RCC_enableClock(uint32_t clk)
 {
	if(clk==clk_HSE||clk==clk_HSI||clk==clk_PLL)
	{

	(RCC->CR)|=clk;

	return res_OK;
	}
	else
	{
		return res_ERROR;
	}
 }
res_t RCC_disableClock(uint32_t clk)
 {
	if(clk==clk_HSE||clk==clk_HSI||clk==clk_PLL)
	{
	RCC->CR &=~clk;
	return res_OK;
	}
	else
	{
		return res_ERROR;
	}

 }

res_t RCC_selectSysClock(uint32_t sysClk)
{
	switch (sysClk)
	{
	case 0: //HSI
		if(((RCC->CR)&BIT1_MASK)==BIT1_MASK)//check if ready
		{
			RCC_CFGR_func(sysclk_LEN_MASK,sysclk_BIT,sysClk);
//			RCC->CFGR&=~BIT0_MASK;
//			RCC->CFGR&=~BIT1_MASK;
			//REG&(BIT_LEN_MASK<<first_BIT)
			//RCC->CFGR &(0x11<<2)
			if((RCC->CFGR &(0x03<<2))==0x00)//check  system clock switch status
					{
						return res_OK;
					}
			else
			{
				return res_ERROR;
			}
		}
		break;
	case 1://HSE
		if(((RCC->CR)&BIT17_MASK)==BIT17_MASK)//check if ready
				{
					RCC_CFGR_func(sysclk_LEN_MASK,sysclk_BIT,sysClk);
//					RCC->CFGR|=BIT0_MASK;
//					RCC->CFGR&=~BIT1_MASK;
//					if(((((((RCC->CFGR)>>1))&0x02)==1))&&(((((RCC->CR)>>1)&0x03)==0)))//check  system clock switch status
					if((RCC->CFGR &(0x01<<2))==(0x01<<2))//check  system clock switch status
							{
								return res_OK;
							}
					else
					{
						return res_ERROR;
					}
				}
				break;
	case 2: //PLL
		if(((RCC->CR)&BIT25_MASK)==BIT25_MASK)//check if ready
				{
					RCC_CFGR_func(sysclk_LEN_MASK,sysclk_BIT,sysClk);
//					RCC->CFGR&=~BIT0_MASK;
//					RCC->CFGR|=BIT1_MASK;
					if((RCC->CFGR &(0x02<<2))==0x02)//check  system clock switch status
							{
								return res_OK;
							}
					else
					{
						return res_ERROR;
					}
				}
				break;
	}
}


res_t RCC_configPll(uint32_t pllSrc,uint32_t pllMull, uint32_t pllUsbDiv,uint32_t pllHseDiv)
{
	RCC_selectSysClock(sysClk_HSE);
	RCC_disableClock(clk_PLL);
	RCC_CFGR_func(pllsrc_LEN_MASK,pllsrc_BIT,pllSrc);//configure pllsrc
	if (pllSrc==pllSrc_HSE)
	{

		if(pllHseDiv==pllHseDiv_1)

		{
		RCC->CFGR &=~ BIT17_MASK;
		return res_OK;
		}
		else if(pllHseDiv==pllHseDiv_2)
		{
			RCC->CFGR |= BIT17_MASK;
			return res_OK;
		}
		else
		{
			return res_ERROR;
		}
		 return pllMull_usb( pllMull,  pllUsbDiv);


		}


	else if(pllSrc==pllSrc_HSI)
	{

		 return pllMull_usb( pllMull,  pllUsbDiv);
//		return res_OK;

	}

	else
	{
		return res_ERROR;
	}


}


res_t RCC_controlPeriphrlClk(uint32_t bus_t,uint32_t periph_t ,uint32_t status_t)
{

switch(bus_t)
{
	case 0://AHB
		if(status_t==state_ON)
					{
						RCC->AHBENR|=periph_t;
						return res_OK;
					}
					else if(status_t==state_OFF)
					{
						RCC->AHBENR&=~periph_t;
						return res_OK;
					}
					else
					{
						return res_ERROR;
					}
		break;
	case 1://APB1
		if(status_t==state_ON)
					{
						RCC->APB1ENR|=periph_t;
						return res_OK;
					}
					else if(status_t==state_OFF)
					{
						RCC->APB1ENR&=~periph_t;
						return res_OK;
					}
					else
					{
						return res_ERROR;
					}
		break;
	case 2://APB2
		if(status_t==state_ON)
					{
						RCC->APB2ENR|=periph_t;
						return res_OK;
					}
					else if(status_t==state_OFF)
					{
						RCC->APB2ENR&=~periph_t;
						return res_OK;
					}
					else
					{
						return res_ERROR;
					}
		break;
	default:
		return res_ERROR;
}

}


void RCC_controPresclrs(uint32_t AHB_t,uint32_t APB1_t,uint32_t APB2_t)
{
	 RCC_CFGR_func(AHB_LEN_MASK,AHB_BIT,AHB_t );//for AHB
	 RCC_CFGR_func(APB1_LEN_MASK,APB1_BIT,APB1_t );//for APB1
	 RCC_CFGR_func(APB2_LEN_MASK,APB2_BIT,APB2_t );//for APB2
}





















//static function implementation
void select_pll(void)
{
	RCC_enableClock(clk_PLL);
	while((((RCC->CR)>>1)&0x25)!=1);
	RCC_selectSysClock(sysClk_PLL);
}



  uint32_t pllMull_usb(uint32_t pllMull, uint32_t pllUsbDiv)
  {
	  RCC_CFGR_func(pllMull_LEN_MASK,pllMull_BIT,pllMull);

	//		switch(pllMull)//adjust MULL
	//			{
	//			case 2:
	//				RCC->CFGR &=~BIT18_MASK;
	//				RCC->CFGR &=~BIT19_MASK;
	//				RCC->CFGR &=~BIT20_MASK;
	//				RCC->CFGR &=~BIT21_MASK;
	//				break;
	//			case 3:
	//				RCC->CFGR |=BIT18_MASK;
	//				RCC->CFGR &=~BIT19_MASK;
	//				RCC->CFGR &=~BIT20_MASK;
	//				RCC->CFGR &=~BIT21_MASK;
	//				break;
	//			case 9:
	//				RCC->CFGR |=BIT18_MASK;
	//				RCC->CFGR |=BIT19_MASK;
	//				RCC->CFGR |=BIT20_MASK;
	//				RCC->CFGR &=~BIT21_MASK;
	//				break;
	//			case 10:
	//				RCC->CFGR &=~BIT18_MASK;
	//				RCC->CFGR &=~BIT19_MASK;
	//				RCC->CFGR &=~BIT20_MASK;
	//				RCC->CFGR |=BIT21_MASK;
	//				break;
	//			default:
	//				return res_ERROR;
	//			}


				if(pllUsbDiv==pllUsbDiv_1)//adjust USB precaler
				{
					RCC->CFGR|=BIT22_MASK;
					select_pll();
					return res_OK;
				}
				else if(pllUsbDiv==pllUsbDiv_1pt5)
				{
					RCC->CFGR&=~BIT22_MASK;
					select_pll();
					return res_OK;
				}
				else
				{
					return res_ERROR;
				}
  }

  void RCC_CFGR_func(uint32_t LEN_MASK,uint32_t BIT,uint32_t user_select )
  {
	  uint32_t temp=RCC->CFGR;
	  	temp&=~(LEN_MASK<<BIT);
	  	temp|=(user_select<<BIT);
	  	RCC->CFGR = temp;
  }
