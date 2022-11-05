/*
 * timer1.h
 *
 *  Created on: Nov 3, 2022
 *      Author: Ahmed
 */

#include"gpio.h"
#ifndef TIMER1_H_
#define TIMER1_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/


/*******************************************************************************
 *                                User Defined Data-Types                      *
 *******************************************************************************/
/*MODE OF OPERATION*/
typedef enum{
	NORMAL,COMPARE=4
}Timer1_Mode;

/*Pre-scaler*/
typedef enum{
	NO_CLK,NO_PRESCALLING,CLK_8,CLK_64,CLK_256,CLK_1024,E_CLK_FALLING,E_CLK_RISING
}Timer1_Prescaler;

/*CONFIG. Struct*/
typedef struct {
uint16 initial_value;
uint16 compare_value; // it will be used in compare mode only.
Timer1_Prescaler prescaler;
Timer1_Mode mode;
} Timer1_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * CONFIG. FUNCTION FOR TIMER1
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/*
 * SET CALL BACK FUNCTION FOR TIMER1
 */
void Timer1_setCallBack(void(*a_ptr)(void));

/*
 * DECTIVATE TIMER1 FUNCTION
 */
void Timer1_deInit(void);

#endif /* TIMER1_H_ */
