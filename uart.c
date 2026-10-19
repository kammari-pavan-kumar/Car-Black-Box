#include <xc.h>
#include "uart.h"

/*  Initialize the UART peripheral for
     asynchronous serial communication.*/
void init_uart(void)
{
	/* Serial initialization */
	RX_PIN = 1;
	TX_PIN = 0;

	/* TXSTA:- Transmitor Status and control Register */
	/* 9bit TX enable or disable bit */ 
	TX9 = 0;
	/* UART Tarsmition enable bit */
	TXEN = 1;
	/* Synchronous or Asynchronous mode selection */
	/* Asynchronous */
	SYNC = 0;
	/* Send the Break character bit */
	SENDB = 0;
	/* Low or High baud rate selection bit */
	/* High Baud Rate */
	BRGH = 1;

	/* RCSTA :- Recepition Status and control Register */
	/* TX/RC7 and RX/RC6 act as serial port */ 
	SPEN = 1;
	/* 9bit RX enable or disable bit */
	RX9 = 0;
	/* Continous reception enable or disable */ 
	CREN = 1;

	/* BAUDCTL:- Baud rate control register */

	/* 16bit baud generate bit */ 
	BRG16 = 0;
	

	/* Baud Rate Setting Register */
	/* Set to 10 for 115200, 64 for 19200 and 129 for 9600 */
	SPBRG = 129;


	/* TX interrupt flag bit */
	TXIF = 0;

	/* RX interrupt enable bit */
	RCIF = 0;
}

/* Transmit a single character over UART. */
void putch(unsigned char byte) 
{
	/* Output one byte */
	/* Set when register is empty */
	while(!TXIF)
	{
		continue;
	}
    /* Clear transmit flag */
	TXIF = 0;
    
    /* Load character into transmit register */
	TXREG = byte;
} 

/* Transmit a null-terminated string over UART. */
int puts(const char *s)
{
    /* Transmit each character until end of string */
	while(*s)		
	{  
		putch(*s++);	
	}
	return 0;
}

/* Receive a single character from UART. */
unsigned char getch(void)
{
	/* Retrieve one byte */
	/* Set when register is not empty */
	while(!RCIF)
	{
		continue;
	}
    /* Clear receive flag */
	RCIF = 0;
    
    /* Return received character */
	return RCREG;
}

/* Receive one character and echo it back */
unsigned char getche(void)
{
	unsigned char c;

    /* Read character and transmit it back */
	putch(c = getch());

	return (c);
}
