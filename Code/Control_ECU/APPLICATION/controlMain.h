/*
 * controlMain.h
 *
 *  Created on: Nov 5, 2022
 *      Author: Ahmed
 */

#ifndef CONTROLMAIN_H_
#define CONTROLMAIN_H_

#include "../HAL./buzzer.h"
#include "../MCAL./uart.h"
#include "../HAL./dc_Motor.h"
#include "../CONFIG./std_types.h"
#include "../MCAL./timer1.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../MCAL./twi.h"
#include "../HAL./external_eeprom.h"

/*******************************************************************************
 *                          DEFINITIONS                                        *
 *******************************************************************************/
/*ACKNOWLEDGE FOR BOTH ECUS FOR UART*/
#define CON_READY 0x10
#define HMI_READY 0x10

#define DOOR_HOLD 1
#define DOOR_OPEN 5
#define DOOR_CLOSE 5
#define BUZZER_ACTIVE 20
#define TWI_SLAVE_ADDRESS 1
#define EEPROM_DELAY 10
#define PASS_LENGTH 5
#define UART_DELAY 50

/*******************************************************************************
 *                          FUNCTIONS  DECLARATION                             *
 *******************************************************************************/
void TIMER1_CallBack(void);

void SAVE_PASS(void);

void OPEN_DOOR(void);

void BUZZER_ON(void);

void PASS_CHECK(void);

void OPEN_DOOR_REQ(void);

void CREATE_PASS(void);

void CHANGE_PASS(void);

void MAIN_OPT(void);

#endif /* CONTROLMAIN_H_ */
