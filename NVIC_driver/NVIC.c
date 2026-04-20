/*
 * NVIC.c
 *
 *  Created on: May 27, 2023
 *      Author: hp
 */

#include "NVIC.h"
#define SCB_AIRCR (*(volatile uint32_t*)(0xE000ED0C))//base address+offset address of this reg
#define SCB_CCR (*(volatile uint32_t*)(0xE000ED14))//base address+offset address of this reg
#define NVIC_STIR (*(volatile uint32_t*)(0xE000EF00))
#define NVIC_BASEADDRESS  (0xE000E100)

#define VECTKEY  0x5FA//temp=SCB_AICFR
						//temp&=~
						//temp|=VECTKEY<<16
						//temp|=PRIGROUP<<8
#define VECTKEY_BIT   		0x010
#define VECTKEY_LEN_MASK 	0xffff
#define PRIGROUP_BIT  		0x08
#define PRIGROUP_LEN_MASK  	0x07

#define LEN_MASK1			0x01
#define LEN_MASK2			0x03
#define LEN_MASK3			0x07
#define LEN_MASK4			0x0F
#define LEN_MASK9			0x01FF
//
#define REGS_SET_BITS(Reg,LEN_MASk,FIRST_BIT,value)   			uint32_t temp=*Reg;\
																temp&=~(LEN_MASk<<FIRST_BIT);\
																temp|=(value<<FIRST_BIT);\
																*Reg=temp;






typedef struct
{
	uint32_t ISER[3];
	uint32_t RESERVED0[29];
	uint32_t ICER[3];
	uint32_t RESERVED1[29];
	uint32_t ISPR[3];
	uint32_t RESERVED2[29];
	uint32_t ICPR[3];
	uint32_t RESERVED3[29];
	uint32_t IABR[3];
	uint32_t RESERVED4[61];
	uint8_t  IPR[84];//300->320=21 place x4=84
	uint32_t RESERVED5[695];
//	uint32_t STIR[1];
//	uint32_t STR;


}NVIC_Regs;

//#define NVIC  ((volatile NVIC_Regs*)(NVIC_BASEADDRESS))

static volatile NVIC_Regs*const NVIC=(volatile NVIC_Regs* const)NVIC_BASEADDRESS;

//static functions prototypes
//void adjustGrouping(void);
uint32_t selectArrayindex(uint32_t IRQn);


void NVIC_setPriorityGrouping()
{

	uint32_t temp;
	temp=SCB_AIRCR;
	temp&=~(VECTKEY_LEN_MASK<<VECTKEY_BIT);//clears this certain bits
	temp&=~(PRIGROUP_LEN_MASK<<PRIGROUP_BIT);//clears this certain bits
	temp|=(VECTKEY<<VECTKEY_BIT);//added the VECTKEY
	temp|=(GROUPING_STATUS<<PRIGROUP_BIT);//added the PRIGROUP
	SCB_AIRCR=temp;
}


void NVIC_enableInterrupt(IRQn_t IRQn)
{
uint32_t y=selectArrayindex(IRQn);
if(IRQn>31)
{
	IRQn=IRQn-32;
}
REGS_SET_BITS(&(NVIC->ISER[y]),1,IRQn,1);
//NVIC->ISER[0]|=(1<<6);

}

void NVIC_disableInterrupt(IRQn_t IRQn)
{
uint32_t y=selectArrayindex(IRQn);
if(IRQn>31)
{
	IRQn=IRQn-32;
}
REGS_SET_BITS(&(NVIC->ICER[y]),1,IRQn,1);
//NVIC->ISER[0]|=(1<<6);

}

void NVIC_setPendingInterrupt(IRQn_t IRQn)
{
	uint32_t y=selectArrayindex(IRQn);
	if(IRQn>31)
	{
		IRQn=IRQn-32;
	}
	REGS_SET_BITS(&(NVIC->ISPR[y]),1,IRQn,1);
	//NVIC->ISER[0]|=(1<<6);

	}

void NVIC_clearPendingInterrupt(IRQn_t IRQn)
{
	uint32_t y=selectArrayindex(IRQn);
		if(IRQn>31)
		{
			IRQn=IRQn-32;
		}
		REGS_SET_BITS(&(NVIC->ICPR[y]),1,IRQn,1);
		//NVIC->ISER[0]|=(1<<6);

		}

void NVIC_setPriority(IRQn_t IRQn,uint32_t group_t,uint32_t subgroup_t)
{
#if GROUPING_STATUS==PRIGROUP_0G16S //G[None]S[7:4]
//		uint32_t y=selectArrayindex(IRQn);
//		if(IRQn>31)
//		{
//			IRQn=IRQn-32;
//		}
		REGS_SET_BITS(&(NVIC->IPR[IRQn]),LEN_MASK4,IRQn,subgroup_t);

#elif GROUPING_STATUS== PRIGROUP_2G8S //G[7]S[6:4]
//		REGS_SET_BITS(&(NVIC->IPR[IRQn]),LEN_MASK3,IRQn,subgroup_t);//set the subgroup number
		//REGS_SET_BITS(&(NVIC->IPR[IRQn]),LEN_MASK1,IRQn,group_t);//set the group number
		uint8_t temp=NVIC->IPR[IRQn];
		temp&=~(LEN_MASK3<<0x04);//cleared sub
		temp&=~(LEN_MASK1<<0x07);//clear group
		temp|=(subgroup_t<<0x04);//adjust sub value
		temp|=(group_t<<0x07);//adjust group value
		NVIC->IPR[IRQn]=temp;
#elif GROUPING_STATUS== PRIGROUP_4G4S //G[7:6]S[5:4]
		uint8_t temp=NVIC->IPR[IRQn];
		temp&=~(LEN_MASK2<<0x04);//cleared sub
		temp&=~(LEN_MASK2<<0x06);//clear group
		temp|=(subgroup_t<<0x04);//adjust sub value
		temp|=(group_t<<0x06);//adjust group value
		NVIC->IPR[IRQn]=temp;
#elif GROUPING_STATUS==PRIGROUP_8G2S //G[7:5]S[4]
		uint8_t temp=NVIC->IPR[IRQn];
		temp&=~(LEN_MASK1<<0x04);//cleared sub
		temp&=~(LEN_MASK3<<0x05);//clear group
		temp|=(subgroup_t<<0x04);//adjust sub value
		temp|=(group_t<<0x05);//adjust group value
		NVIC->IPR[IRQn]=temp;
#elif GROUPING_STATUS==PRIGROUP_16G0S //G[7:4]s[None]
		REGS_SET_BITS(&(NVIC->IPR[IRQn]),LEN_MASK4,IRQn,group_t);
#endif
}

void NVIC_triggerInterrupt(IRQn_t IRQn)
{
//	REGS_SET_BITS(&(NVIC->STIR),LEN_MASK9,0x00,IRQn);

//	NVIC->STIR[0] =0x05; wrong
	NVIC_STIR =IRQn;
}









//static function implementation

uint32_t selectArrayindex(uint32_t IRQn)
{
//	uint32_t x=0;
	if ( IRQn<=31)
	{
		return 0;
	}
	else if(IRQn>=32&&IRQn<=63)
	{
//		x=1;
		return 1;
	}
	else if(IRQn>=64 && IRQn<=67)
	{
		return 2;
	}
	else
		return 9;
}




//void adjustGrouping(void)
//{
//	uint32_t temp;
//		temp=SCB_AIRCR;
//		temp&=~(VECTKEY_LEN_MASK<<VECTKEY_BIT);//clears this certain bits
//		temp&=~(PRIGROUP_LEN_MASK<<PRIGROUP_BIT);//clears this certain bits
//		temp|=(VECTKEY<<VECTKEY_BIT);//added the VECTKEY
//		temp|=(GROUPING_STATUS<<PRIGROUP_BIT);//added the PRIGROUP
//		SCB_AIRCR=temp;
//}
