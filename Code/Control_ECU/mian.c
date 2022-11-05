/*
 * mian.c
 *
 *  Created on: Nov 5, 2022
 *      Author: Ahmed
 */
#include "./APPLICATION./controlMain.h"


int main(void)
{
	/* ======================== Variables ============================== */
	/*uart config. structure*/
	UART_CONFIGURATION uart_Conf={DISABLE,ONE,EIGHT,9600};

	/*timer1 config. structure*/
	Timer1_ConfigType timer1_conf={0,23437,CLK_1024,COMPARE};

	/*I2C config. structure*/
	TWI_ConfigType twi_conf={TWI_SLAVE_ADDRESS,2,0};


	/* ======================== SYSTEM Initialization ============================== */
	//ACTIVATE (I-BIT) FOR INTERRUPTS
	sei();

	UART_init(&uart_Conf);
	Timer1_setCallBack(TIMER1_CallBack); /*SET CALL BACK FUNCTION FOR TIMER*/
	Timer1_init(&timer1_conf);
	TWI_init(&twi_conf);
	Buzzer_init();
	DcMotor_Init();


	/* ======================== Program ============================== */
	CREATE_PASS();

	for(;;)
	{
		MAIN_OPT();
	}
}


