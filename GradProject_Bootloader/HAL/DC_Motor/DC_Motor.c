/*********************includes*********************/
#include "../../MCAL/TIMER/TIMER.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "DC_Motor.h"

void HMotor_Init(void)
{
    /*set the output speed of the motor pins to be low*/
    GPIO_PinConfig_t PinConfig;
    PinConfig.OutputSpeed = Speed_Low;

    /*set Ena, Enb pins to be Alternate function output push pull*/
    PinConfig.PinMode = Mode_OutputAFPP;

    /*set the L298 enable pins numbers according to the config file*/
    PinConfig.PinNumber = L298_EnaPin;
    MGPIO_Init(L298_EnaPort, &PinConfig);

    PinConfig.PinNumber = L298_EnbPin;
    MGPIO_Init(L298_EnbPort, &PinConfig);

    /*set In1, In2, In3, In4 pins to be general purpose output push pull*/
    PinConfig.PinMode = Mode_OutputPP;

    /*set the L298 input pins numbers according to the config file*/
    PinConfig.PinNumber = L298_In1Pin;
    MGPIO_Init(L298_In1Port, &PinConfig);

    PinConfig.PinNumber = L298_In2Pin;
    MGPIO_Init(L298_In2Port, &PinConfig);

    PinConfig.PinNumber = L298_In3Pin;
    MGPIO_Init(L298_In3Port, &PinConfig);

    PinConfig.PinNumber = L298_In4Pin;
    MGPIO_Init(L298_In4Port, &PinConfig);
}

void HMotor_Move(u8 Direction, u16 Speed)
{
	/*set Ena, Enb pins to be driven by PWM signals of frequency = Motor_Frequency, and duty cycle corresponding to the desired speed*/
	MTimer_GeneratePWM(TIMER3, Motor_Frequency, Speed);
	MTimer_GeneratePWM(TIMER3, Motor_Frequency, Speed);

	/*set the direction of rotation of the 4 motors according to the specified motion direction*/
    switch (Direction)
    {
    	/*stop the 4 motors to stop the car*/
        case Direction_Stop:
            MGPIO_WritePin(L298_In1Port, L298_In1Pin, Pin_Low);
            MGPIO_WritePin(L298_In2Port, L298_In2Pin, Pin_Low);
            MGPIO_WritePin(L298_In3Port, L298_In3Pin, Pin_Low);
            MGPIO_WritePin(L298_In4Port, L298_In4Pin, Pin_Low);
            break;
        /*move the 4 motors in the forward direction to move the car forward*/
        case Direction_Forward:
            MGPIO_WritePin(L298_In1Port, L298_In1Pin, Pin_High);
            MGPIO_WritePin(L298_In2Port, L298_In2Pin, Pin_Low);
            MGPIO_WritePin(L298_In3Port, L298_In3Pin, Pin_High);
            MGPIO_WritePin(L298_In4Port, L298_In4Pin, Pin_Low);
            break;
        /*move the 4 motors in the backward direction to move the car backward*/
        case Direction_Backward:
            MGPIO_WritePin(L298_In1Port, L298_In1Pin, Pin_Low);
            MGPIO_WritePin(L298_In2Port, L298_In2Pin, Pin_High);
            MGPIO_WritePin(L298_In3Port, L298_In3Pin, Pin_Low);
            MGPIO_WritePin(L298_In4Port, L298_In4Pin, Pin_High);
            break;
        /*move the left motors in the forward direction and stop the right motors to make the car turn right*/
        case Direction_right:
            MGPIO_WritePin(L298_In1Port, L298_In1Pin, Pin_Low);
            MGPIO_WritePin(L298_In2Port, L298_In2Pin, Pin_Low);
            MGPIO_WritePin(L298_In3Port, L298_In3Pin, Pin_High);
            MGPIO_WritePin(L298_In4Port, L298_In4Pin, Pin_Low);
            break;
        /*move the right motors in the forward direction and stop the left motors to make the car turn left*/
        case Direction_Left:
			MGPIO_WritePin(L298_In1Port, L298_In1Pin, Pin_High);
			MGPIO_WritePin(L298_In2Port, L298_In2Pin, Pin_Low);
			MGPIO_WritePin(L298_In3Port, L298_In3Pin, Pin_Low);
			MGPIO_WritePin(L298_In4Port, L298_In4Pin, Pin_Low);
			break;
    }
}
