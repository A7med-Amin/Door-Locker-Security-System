/*
 * uart.c
 *
 *  Created on: Oct 7, 2022
 *      Author: Ahmed
 */

#include "uart.h"
#include "avr/io.h" /* To use the UART Registers */
#include "../CONFIG./common_macros.h" /* To use the macros like SET_BIT */

 /*******************************************************************************
  *                      Functions Definitions                                  *
  *******************************************************************************/

  /*
   * Description :
   * Functional responsible for Initialize the UART device by:
   * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
   * 2. Enable the UART.
   * 3. Setup the UART baud rate.
   */
void UART_init(UART_CONFIGURATION* uart_Config)
{
	uint16 ubrr_value = 0;

	/* U2X = 1 for double transmission speed */
	UCSRA = (1 << U2X);

	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/
	UCSRB = (1 << RXEN) | (1 << TXEN);

	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = parity bit CONFIG.
	 * USBS    = stop bit CONFIG.
	 * UCSZ1:0 = bit data mode (5,6,7,8)  *******with UCSZ2 in UCSRB******
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/
	/* Set Bits number 3 in The Data size number in The bit UCSZ2 in Register UCSRB */
		UCSRB = (UCSRB & 0xFB) | (uart_Config->data_bits & 0x04);

		/* To Write in Register UCSRC, Firstly we need to make URSEL with LOGIC HIGH */
		/* But the first 2 bits in Data size in the bits UCSZ1 and UCSZ0 to Specify the size of Data */
		UCSRC = (1 << URSEL) | (uart_Config->data_bits << 1);

		/* Specify Parity bit Mode(Even/ Odd / Disabled) in Data frame */
		UCSRC = (UCSRC & 0xCF) | (uart_Config->parity_mode << 4);

		/* Specify number of stop bits in the Data frame */
		UCSRC = (UCSRC & 0xF7) | (uart_Config->stop_bit << 3);

	if (uart_Config->data_bits == NINE)
	{
		/*
		 * SET BIT UCSZ2 FOR 9-BIT MODE IN REG UCSRB
		 * */
		SET_BIT(UCSRB, UCSZ2);
	}
	/* Calculate the UBRR register value */
	ubrr_value = (uint16)(((F_CPU / (uart_Config->baud_rate * 8UL))) - 1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	//CLEAR_BIT(UCSRC,URSEL);
	UBRRH = ubrr_value >> 8; /*SHIFT BY 8 BIT TO PUT IN REG. HIGH*/
	UBRRL = ubrr_value;
}

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while (BIT_IS_CLEAR(UCSRA, UDRE)) {}

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR = data;

	/************************* Another Method *************************
	UDR = data;
	while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transmission is complete TXC = 1
	SET_BIT(UCSRA,TXC); // Clear the TXC flag
	 *******************************************************************/
}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while (BIT_IS_CLEAR(UCSRA, RXC)) {}

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
	return UDR;
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8* Str)
{

	uint8 i = 0;

	/* Send the whole string */
	while (Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
	/************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}
	 *******************************************************************/
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8* Str)
{
	uint8 i = 0;

	/* Receive the whole string until the '#' */
	Str[i] = UART_recieveByte();

	while (Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}
