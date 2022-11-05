 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: dc_Motor.h
 *
 * Created on: Oct 6, 2022
 *
 * Description: header file for the ATmega16 ADC driver
 *
 * Author: Ahmed
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "../MCAL/gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define DC_MOTOR_IN1_PORT_ID PORTB_ID
#define DC_MOTOR_IN1_PIN_ID  PIN0_ID
#define DC_MOTOR_IN2_PORT_ID PORTB_ID
#define DC_MOTOR_IN2_PIN_ID  PIN1_ID

/*******************************************************************************
 *                                User Defined Data-Types                      *
 *******************************************************************************/
typedef enum{
	STOP,CW,A_CW
}DcMotor_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description:
 * The Function responsible for setup the direction for the two
   motor pins through the GPIO driver.
 * Stop at the DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_Init(void);

/*
 * Description:
 * The function responsible for rotate the DC Motor CW/ or A-CW or stop
   the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the required
   speed value.
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DC_MOTOR_H_ */
