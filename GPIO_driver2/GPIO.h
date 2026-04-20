/*
 * GPIO.h
 *
 *  Created on: May 26, 2023
 *      Author: hp
 */
#ifndef GPIO_DRIVER_GPIO_H_
#define GPIO_DRIVER_GPIO_H_

#include <stdlib.h>
#include"stdint.h"


typedef struct
{
	uint32_t port;
	uint32_t pin;
	uint32_t mode;
	uint32_t confg;
	uint32_t speed;
	uint32_t af;
}gpioPinCfg_t;

typedef enum
{
	portA_GPIO,
	portB_GPIO,
	portC_GPIO,
	portD_GPIO,
	portE_GPIO,
	portF_GPIO,
	portG_GPIO
}port_GPIO;

typedef enum
{
	Pin_0_GPIO,
	Pin_1_GPIO,
	Pin_2_GPIO,
	Pin_3_GPIO,
	Pin_4_GPIO,
	Pin_5_GPIO,
	Pin_6_GPIO,
	Pin_7_GPIO,
	Pin_8_GPIO,
	Pin_9_GPIO,
	Pin_10_GPIO,
	Pin_11_GPIO,
	Pin_12_GPIO,
	Pin_13_GPIO,
	Pin_14_GPIO,
	Pin_15_GPIO
}pin_GPIO;

typedef enum
{
	pin_ON,
	pin_OFF
}pinValue;

typedef enum
{
	speed_max10,
	speed_max2,
	speed_max50
}speed_GPIO;

typedef enum
{
	mode_input_GPIO,
	mode_output_GPIO
}mode_GPIO;

typedef enum
{
	confg_op_GPP,
	confg_op_GOD,
	confg_op_APP,
	confg_op_AOD,
	confg_ip_ANLG,
	confg_ip_FLT,
	confg_ip_PU,
	confg_ip_PD,
}confg_GPIO;

extern void gpio_initPin(gpioPinCfg_t * module_t);
extern void gpio_writePinValue(port_GPIO port_t,pin_GPIO pin_t,pinValue value_t);
extern uint8_t gpio_getPinValue(port_GPIO port_t,pin_GPIO pin_t);












#endif
#ifndef GPIO_DRIVER_GPIO_H_
#define GPIO_DRIVER_GPIO_H_

#include <stdlib.h>
#include"stdint.h"


#define port_PORTA 	0
#define port_PORTB 	1
#define port_PORTC 	2
#define port_PORTD 	3
#define port_PORTE 	4
#define port_PORTF 	5
#define port_PORTG 	6


#define mode_INPUT 		0
//#definmodeE_OUTPUT 		1
#define mode_OUT10 		0b01
#define mode_OUT2 		0b10
#define mode_OUT50 		0b11

#define confg_OTPT_GPP		0
#define confg_OTPT_GOD		1
#define confg_OTPT_APP		2
#define confg_OTPT_AOD		3

#define confg_INPT_ANLG		0
#define confg_INPT_FLT		1
#define confg_INPT_PU		2
#define confg_INPT_PD		2

#define confgMode_PU 		1
#define confgMode_PD 		2


typedef enum
{
	Pin_0,
	Pin_1,
	Pin_2,
	Pin_3,
	Pin_4,
	Pin_5,
	Pin_6,
	Pin_7,
	Pin_8,
	Pin_9,
	Pin_10,
	Pin_11,
	Pin_12,
	Pin_13,
	Pin_14,
	Pin_15
}pin_t;




void GPIO_voidSetPinMode(uint32_t port_t,pin_t pin_t, uint32_t mode_t,uint32_t confg_t,uint32_t confgMode_t);
//void GPIO_voidSetPinType(uint32_t port_t,pin_t pin_t, uint32_t confg_t);
void GPIO_voidOutputData(uint32_t data,uint32_t port_t,pin_t pin_t);
void GPIO_voidSetPin(uint32_t port_t,pin_t pin_t);
void GPIO_voidResetPin(uint32_t port_t,pin_t pin_t);
void Tim2AFRemap(void);
#endif /* GPIO_DRIVER_GPIO_H_ */
