/*
 * main.c
 *
 *  Created on: Nov 5, 2022
 *      Author: Ahmed
 */

#include "./APPLICATION./hmiMain.h"


int main(void)
{
	/* ======================== Variables ============================== */

	/*uart config. structure*/
	UART_CONFIGURATION uart_Conf={DISABLE,ONE,EIGHT,9600};

	/*timer! config. structure*/
	Timer1_ConfigType timer1_conf={0,23437,CLK_1024,COMPARE};

	/* ======================== SYSTEM Initialization ============================== */
	//ACTIVATE (I-BIT) FOR INTERRUPTS
	sei();

	UART_init(&uart_Conf);
	Timer1_setCallBack(TIMER1_CallBack); /*SET CALL BACK FUNCTION FOR TIMER*/
	Timer1_init(&timer1_conf);
	LCD_init();

	/* ======================== Program ============================== */

	CREATE_PASS();

	for(;;)
	{
		MAIN_OPT();
	}
}
