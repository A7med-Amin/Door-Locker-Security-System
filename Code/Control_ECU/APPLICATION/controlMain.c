/*
 * controlMain.c
 *
 *  Created on: Nov 1, 2022
 *      Author: Ahmed
 */

#include "controlMain.h"

/*******************************************************************************
 *                          GLOBAL VARIABLES                                   *
 *******************************************************************************/
volatile uint8 ticks=0;
uint8 uart_data;
uint8 eeprom_mem_loc_add;

/*PASSWORDS*/
uint8 PASS[PASS_LENGTH+1];
uint8 PASS_CONF[PASS_LENGTH+1];
uint8 CHECK_PASS[PASS_LENGTH+1];    /*VARIABLE TO GET ENTERED PASS BY UART TO DO A TASK THEN*/
uint8 STORED_PASS[PASS_LENGTH];    /*VARIABLE TO SAVE STORED PASS IN IT*/

/*BOOL VARIABLE IS TRUE ONLY IF 2 PASS ARE MATCHED RECEIVED FROM CONTROL ECU*/
uint8 is_matched=0;

/*OPTION TO BE SELECTED +: OPEN DOOR / -:CHANGE PASS*/
uint8 opt;

/*ITTERATOR*/
uint8 i=0;

/*MEMORY LOCATION TO SAVE INSIDE IN EEPROM*/
uint16 eeprom_add=0x0311;


/*******************************************************************************
 *                          FUNCTIONS  DEFINITOINS                             *
 *******************************************************************************/
void TIMER1_CallBack(void)
{
	++ticks;
}

void SAVE_PASS(void)
{
	eeprom_add=0x0311;
	for(i=0;i<PASS_LENGTH;i++)
	{
		EEPROM_writeByte(eeprom_add, PASS[i]);
		_delay_ms(EEPROM_DELAY);   /*delay 10 ms between each read/write to EEPROM*/
		eeprom_add++;
	}
	/*return to main process after save password*/
}

void OPEN_DOOR(void)
{
	/*to start counting from sec=0*/
	ticks=0;
	DcMotor_Rotate(CW, 90);
	while(ticks<DOOR_OPEN);   /*ROTATE MOTOR TO OPEN THE DOOR FOR 15 SEC*/
	DcMotor_Rotate(STOP, 0);
	while(ticks<(DOOR_OPEN+DOOR_HOLD));   /*HOLD FOR 3 SEC TO LET USER ENTER FROM DOOR*/
	DcMotor_Rotate(A_CW, 90);
	while(ticks<(DOOR_OPEN+DOOR_HOLD+DOOR_CLOSE)); /*ROTATE MOTOR TO CLOSE THE DOOR FOR 15 SEC*/
	DcMotor_Rotate(STOP, 0);
}

void BUZZER_ON(void)
{
	ticks=0;
	Buzzer_on();
	while(ticks<BUZZER_ACTIVE); /*BUZZER IS ACTIVE FOR A MINUTE*/
	Buzzer_off();
}

/*
 * RECEIVE ENTERED PASS AND CHECK IT WITH STOREED ON
 * */
void PASS_CHECK(void)
{
	/*TO BE RECEIVED FROM CONTROL ECU*/
	is_matched=1;      /*let 2 pass are matched*/
	i=0;
	/*=======================receive password1 by Uart=================================*/
	UART_sendByte(CON_READY);
	i=0;
	while(i<PASS_LENGTH)
	{
		CHECK_PASS[i]=UART_recieveByte();
		_delay_ms(UART_DELAY);
		++i;
	}

	eeprom_add=0x0311;
	for(i=0;i<PASS_LENGTH;i++)
	{
		EEPROM_readByte(eeprom_add,STORED_PASS+i);
		_delay_ms(EEPROM_DELAY);   /*delay 10 ms between each read/write to EEPROM*/
		eeprom_add++;
	}

	is_matched=1;
	i=0;
	while(i<PASS_LENGTH)
	{
		if(CHECK_PASS[i] != STORED_PASS[i])
		{
			is_matched=0;
			break;
		}
		i++;
	}
}

void OPEN_DOOR_REQ(void)
{
	uint8 trial=0;
	is_matched=0;

	while(is_matched==0 && trial<3)
	{
		/*CHECK IF RECEIVED PASS MATCH THAT STORED*/
		PASS_CHECK();

		/*SEND TO HMI IF ENTERED PASS IS VALID OR NOT
		 * IF VALID HOLD FOR 1 MIN UNTIL OPEN DOOR
		 * */
		while(UART_recieveByte() != HMI_READY);
		UART_sendByte(is_matched);
		_delay_ms(UART_DELAY);

		/*increment trial-error*/
		++trial;
	}

	if(is_matched==1)
	{
		OPEN_DOOR();
	}
	else
	{
		/*ACTIVATE BUZZER*/
		BUZZER_ON();
	}
}

void CREATE_PASS(void)
{
	is_matched=0;
	while(is_matched==0)
	{
		/*TO BE RECEIVED FROM CONTROL ECU*/
		is_matched=1;      /*let 2 pass are matched*/
		i=0;
		/*=======================receive password1 by Uart=================================*/
		//		UART_sendByte(CON_READY);
		//		UART_receiveString(PASS);
		//		_delay_ms(UART_DELAY);

		UART_sendByte(CON_READY);
		i=0;
		while(i<PASS_LENGTH)
		{
			PASS[i]=UART_recieveByte();
			_delay_ms(UART_DELAY);
			++i;
		}

		/*=======================receive confirmation password by Uart=================================*/
		//		UART_sendByte(CON_READY);
		//		UART_receiveString(PASS_CONF);
		//		_delay_ms(UART_DELAY);

		UART_sendByte(CON_READY);
		i=0;
		while(i<PASS_LENGTH)
		{
			PASS_CONF[i]=UART_recieveByte();
			_delay_ms(UART_DELAY);
			++i;
		}

		/*=======================check if 2 passwords matched and send result by Uart=================================*/
		i=0;
		while(i<PASS_LENGTH)
		{
			if(PASS[i] != PASS_CONF[i])
			{
				is_matched=0;
				break;
			}
			i++;
		}

		while(UART_recieveByte() != HMI_READY);
		UART_sendByte(is_matched);
		_delay_ms(UART_DELAY);
	}

	/*save password in EEPROM*/
	SAVE_PASS();
}

void CHANGE_PASS(void)
{

	uint8 trial=0;
	is_matched=0;

	while(is_matched==0 && trial<3)
	{
		/*CHECK IF RECEIVED PASS MATCH THAT STORED*/
		PASS_CHECK();

		/*SEND TO HMI IF ENTERED PASS IS VALID OR NOT
		 * IF VALID HOLD FOR 1 MIN UNTIL OPEN DOOR
		 * */
		while(UART_recieveByte() != HMI_READY);
		UART_sendByte(is_matched);
		_delay_ms(UART_DELAY);

		/*increment trial-error*/
		++trial;
	}

	if(is_matched==1)
	{
		CREATE_PASS();
	}
	else
	{
		/*ACTIVATE BUZZER*/
		BUZZER_ON();
	}
}

void MAIN_OPT(void)
{
	/*receive option by uart*/
	UART_sendByte(CON_READY);
	opt=UART_recieveByte();
	_delay_ms(UART_DELAY);

	if(opt=='+')
	{
		OPEN_DOOR_REQ();
	}
	else
	{
		CHANGE_PASS();
	}
}

