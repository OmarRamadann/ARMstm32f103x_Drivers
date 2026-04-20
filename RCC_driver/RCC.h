#ifndef  __RCC_H__
#define  __RCC_H__
#include"stdint.h"
#include "util.h"
//Defines
#define clk_HSI BIT0_MASK
#define clk_HSE BIT16_MASK
#define clk_PLL BIT24_MASK

#define sysClk_HSI 0x00
#define sysClk_HSE 0x01
#define sysClk_PLL 0x02

#define pllSrc_HSI 0x00
#define pllSrc_HSE 0x01

#define pllUsbDiv_1pt5 0
#define pllUsbDiv_1    1

#define pllHseDiv_2  0
#define pllHseDiv_1  1

#define pllMull_2  		0x00
#define pllMull_3		0x01
#define pllMull_4		0x02
#define pllMull_5		0x03
#define pllMull_6		0x04
#define pllMull_7       0x05
#define pllMull_8       0x06
#define pllMull_9       0x07
#define pllMull_10      0x08
#define pllMull_11      0x09
#define pllMull_12      0x0A
#define pllMull_13      0x0B
#define pllMull_14      0x0C
#define pllMull_15      0x0D
#define pllMull_16      0x0E


#define periph_AHB_DMA1       BIT0_MASK
#define periph_AHB_SRAM       BIT2_MASK
#define periph_APB2_AFIO      BIT0_MASK
#define periph_APB2_IOPA      BIT2_MASK
#define periph_APB2_IOPB      BIT3_MASK
#define periph_APB2_IOPC      BIT4_MASK
#define periph_APB2_ADC1      BIT9_MASK
#define periph_APB2_SPI1      BIT12_MASK
#define periph_APB2_USART1	  BIT14_MASK
#define periph_APB1_TIM2      BIT0_MASK
#define periph_APB1_TIM3      BIT1_MASK
#define periph_APB1_CAN       BIT25_MASK



#define AHB_1  		0x00
#define AHB_2 		0x08
#define AHB_4 	 	0x09
#define AHB_8  		0x0A
#define AHB_16  	0x0B
#define AHB_64  	0x0C
#define AHB_128  	0x0D
#define AHB_256  	0x0E
#define AHB_512  	0x0F


#define APB1_1		0x00
#define APB1_2		0x08
#define APB1_4		0x09
#define APB1_8		0x0A
#define APB1_16		0x0B


#define APB2_1		0x00
#define APB2_2		0x08
#define APB2_4		0x09
#define APB2_8		0x0A
#define APB2_16		0x0B


//Datatypes
//typedef enum
//{
//	res_OK,
//	res_ERROR,
//	res_ARGS,
//	res_NULL
//}res_t;

//typedef enum
//{
//	pllMull_2=2,
//	pllMull_3,
//	pllMull_4,
//	pllMull_5,
//	pllMull_6,
//	pllMull_7,
//	pllMull_8,
//	pllMull_9,
//	pllMull_10,
//	pllMull_11,
//	pllMull_12,
//	pllMull_13,
//	pllMull_14,
//	pllMull_15,
//	pllMull_16
//}pllMull;


//typedef enum
//{
//	bus_AHB,
//	bus_APB1,
//	bus_APB2
//}bus_t;


//Prototypes


res_t RCC_enableClock(uint32_t clk );
res_t RCC_disableClock(uint32_t clk);
res_t RCC_selectSysClock(uint32_t sysClk);
//res_t RCC_configPll(uint32_t pllSrc,uint32_t pllMull, uint32_t pllUsbOtg,uint32_t pllPreDiv1);//for connectivity line device
res_t RCC_configPll(uint32_t pllSrc,uint32_t pllMull, uint32_t pllUsbDiv,uint32_t pllHseDiv);//for medium density
res_t RCC_controlPeriphrlClk(uint32_t bus_t,uint32_t periph_t ,uint32_t status_t);
void RCC_controPresclrs(uint32_t AHB_t,uint32_t APB1_t,uint32_t APB2_t);



#endif
