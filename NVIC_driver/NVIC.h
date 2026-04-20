/*
 * NVIC.h
 *
 *  Created on: May 27, 2023
 *      Author: hp
 */

#ifndef NVIC_DRIVER_NVIC_H_
#define NVIC_DRIVER_NVIC_H_

#include"stdint.h"
#include "cfg.h"


typedef enum
{
	IRQn_WWDG,
	IRQn_PVD,
	IRQn_TAMPER,
	IRQn_EXTI0=6,
	IRQn_EXTI1,
	IRQn_EXTI2,
	IRQn_EXTI3,
	IRQn_EXTI4,
	IRQn_DMA1_Channel1,
	IRQn_DMA1_Channel2,
	IRQn_ADC1_2=18,
	IRQn_USB_HP_CAN_TX,
	IRQn_USB_LP_CAN_RX0,
	IRQn_TIM2=28,
	IRQn_TIM3,
	IRQn_TIM4,
	IRQn_I2C1_EV,
	IRQn_SPI1=35,
	IRQn_SPI2,
	IRQn_USART1

}IRQn_t;

typedef enum
{
	group_0,
	group_1,
	group_2,
	group_3,
	group_4,
	group_5,
	group_6,
	group_7,
	group_8,
	group_9,
	group_10,
	group_11,
	group_12,
	group_13,
	group_14,
	group_15
}group_t;
typedef enum
{
	subgroup_0,
	subgroup_1,
	subgroup_2,
	subgroup_3,
	subgroup_4,
	subgroup_5,
	subgroup_6,
	subgroup_7,
	subgroup_8,
	subgroup_9,
	subgroup_10,
	subgroup_11,
	subgroup_12,
	subgroup_13,
	subgroup_14,
	subgroup_15
}subgroup_t;


/*
 * NVIC_setPriorityGrouping:selects the no. of groups and subgroups.
 * inputs:options from PRIGROUP_t.
 */
void NVIC_setPriorityGrouping();

/*
 * NVIC_enableInterrupt:NVIC enable for certain interrupt.
 * inputs:interrupt names options from IRQn_t.
 */
void NVIC_enableInterrupt(IRQn_t IRQn);
/*
 * NVIC_disableInterrupt:NVIC disable for certain interrupt.
 * inputs:interrupt names options from IRQn_t.
 */
void NVIC_disableInterrupt(IRQn_t IRQn);
/*
 * NVIC_setPendingInterrupt:raise the pending flag for certain interrupt
 * Inputs:interrupt names options from IRQn_t.
 */
void NVIC_setPendingInterrupt(IRQn_t IRQn);
/*
 * NVIC_clearPendingInterrupt:clear the pending flag for certain interrupt.
 * Inputs:interrupt names options from IRQn_t.
 */
void NVIC_clearPendingInterrupt(IRQn_t IRQn);
/*
 *  NVIC_setPriority:assigns the oftware priority of certain interrupt.
 *  Inputs:interrupt names options from IRQn_t.
 *  		Group priority.
 *  		subgroup priority.
 */
void NVIC_setPriority(IRQn_t IRQn,uint32_t group_t,uint32_t subgroup_t);
/*
 *  NVIC_triggerInterrupt:triggers certain interrupt and starts its ISR without being reached in code
 *  INPUTS:interrupt names options from IRQn_t.
 */
void NVIC_triggerInterrupt(IRQn_t IRQn);



#endif /* NVIC_DRIVER_NVIC_H_ */
