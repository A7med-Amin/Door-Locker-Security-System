 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: timer0.h
 *
 * Created on: Oct 6, 2022
 *
 * Description: header file for the ATmega16 ADC driver
 *
 * Author: Ahmed
 *
 *******************************************************************************/
#include"gpio.h"

#ifndef TIMER0_H_
#define TIMER0_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define TIMER0_OVERFLOW_VALUE 255
#define TIMER0_PWM_SIGNAL_PORT_ID PORTB_ID
#define TIMER0_PWM_SIGNAL_PIN_ID PIN3_ID
/*******************************************************************************
 *                                User Defined Data-Types                      *
 *******************************************************************************/
typedef enum{
	OVERFLOW,CTC=8,PWM=0X48   /*WGM01 & WGM00 BIT VALUE IN REG TCCR0*/
}TIMER0_OPERATION_MODE;

typedef enum{
	DISCONNECTED,NON_INVERTING=2,INVERTING=3
}PWM_MODE;

typedef enum{
	NOCLK,NOPRESCALLING,CLK8,CLK64,CLK256,CLK1024,ECLK_FALLING,ECLK_RISING
}TIMER0_CLK;

/*
 * CONFIG. STRUCT FOR TIMER0
 */
typedef struct{
	TIMER0_OPERATION_MODE oper_mode;
	PWM_MODE pwm_mode;
	TIMER0_CLK clock;
}TIMER0_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * CONFIG. FUNCTION FOR TIMER0
 */
void TIMER0_init(TIMER0_ConfigType* Config_Ptr);

/*
 * GENERATING PWM SIGNAL FUNCTOIN
 */
void PWM_Timer0_Start(uint8 duty_cycle);

/*
 * DECTIVATE TIMER0 FUNCTION
 */
void TIMER0_deinit(void);

#endif /* TIMER0_H_ */
