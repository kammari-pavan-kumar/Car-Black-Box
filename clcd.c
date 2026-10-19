/*
 * File:   clcd.c
 * Author: DELL
 *
 * Created on 14 July, 2026, 8:56 AM
 */


#include <xc.h>
#include "clcd.h"

/* Write command/data byte to LCD */
void clcd_write(unsigned char byte, unsigned char control_bit)
{
    /* Select command or data mode */
	CLCD_RS = control_bit;
    
    /* Send data to LCD port */
	CLCD_PORT = byte;

	/* Should be atleast 200ns */
    /* Generate enable pulse */
	CLCD_EN = HI;
	CLCD_EN = LO;

    /* Set port as input for busy flag */
	PORT_DIR = INPUT;
    
    /* Read LCD busy status */
	CLCD_RW = HI;
	CLCD_RS = INSTRUCTION_COMMAND;

    /* Wait until LCD is ready */
	do
	{
		CLCD_EN = HI;
		CLCD_EN = LO;
	} while (CLCD_BUSY);

    /* Set LCD back to write mode */
	CLCD_RW = LO;
    
    /* Set port as output */
	PORT_DIR = OUTPUT;
}

/* Initializes the CLCD. */
void init_clcd()
{
	/* Set PortD as output port for CLCD data */
	TRISD = 0x00;
	/* Set PortC as output port for CLCD control */
	TRISC = TRISC & 0xF8;

	CLCD_RW = LO;

	
     /* Startup Time for the CLCD controller */
    __delay_ms(30);
    
    /* The CLCD Startup Sequence */
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND	);
    __delay_us(4100);
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND	);
    __delay_us(100);
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND	);
    __delay_us(1); 
    
    /* Cursor to home position */
    CURSOR_HOME;
    __delay_us(100);
    
    /* Select 2 line 8-bit mode */
    TWO_LINE_5x8_MATRIX_8_BIT;
    __delay_us(100);
    
    /* Clear LCD display */
    CLEAR_DISP_SCREEN;
    __delay_us(500);
    
    /* Turn ON display, cursor OFF */
    DISP_ON_AND_CURSOR_OFF;
    __delay_us(100);
}

/* Displays a string on the LCD at the specified address. */
void clcd_print(const unsigned char *data, unsigned char addr)
{
    /* Set LCD address */
	clcd_write(addr, INSTRUCTION_COMMAND);
    /* Send string characters */
	while (*data != '\0')
	{
		clcd_write(*data++, DATA_COMMAND);
	}
}

/* Display single character on LCD */
void clcd_putch(const unsigned char data, unsigned char addr)
{
    /* Set LCD address */
	clcd_write(addr, INSTRUCTION_COMMAND);
    
    /* Send character data */
	clcd_write(data, DATA_COMMAND);
}

