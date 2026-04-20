#ifndef _MOTOR_CONFIG_H_
#define _MOTOR_CONFIG_H_


/*configure the frequency of driving the DC motors*/
#define Motor_Frequency			(u32)1000

/*configure L298 Ena, ENb ports*/
#define L298_EnaPort            GPIOB
#define L298_EnbPort            GPIOB

/*configure L298 Ena, ENb pins*/
#define L298_EnaPin             PIN3
#define L298_EnbPin             PIN4

/*configure L298 In1, In2, In3, In4 ports*/
#define L298_In1Port            GPIOB
#define L298_In2Port            GPIOB
#define L298_In3Port            GPIOB
#define L298_In4Port            GPIOB

/*configure L298 In1, In2, In3, In4 pins*/
#define L298_In1Pin             PIN5
#define L298_In2Pin             PIN6
#define L298_In3Pin             PIN7
#define L298_In4Pin             PIN8


#endif
