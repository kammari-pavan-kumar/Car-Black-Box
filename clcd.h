
#ifndef CLCD_H
#define	CLCD_H

//LCD Pin Configuration
#define CLCD_PORT			PORTD       // LCD data port
#define CLCD_EN				RC2         // Enable pin
#define CLCD_RS				RC1         // Register Select pin
#define CLCD_RW				RC0         // Read/Write pin
#define CLCD_BUSY			RD7         // Busy flag pin
#define PORT_DIR			TRISD7      // Data direction for busy flag

/* Logic Levels */
#define HI												1      // Logic HIGH
#define LO												0      // Logic LOW

/* Port Direction */
#define INPUT											0xFF   // Configure port as input
#define OUTPUT											0x00   // Configure port as output

/* LCD Control Modes */
#define DATA_COMMAND									1      // Data register selected
#define INSTRUCTION_COMMAND								0     // Instruction register selected
/* System Clock Frequency */
#define _XTAL_FREQ                  20000000

/* LCD Cursor Position Macros */
#define LINE1(x)									(0x80 + (x))   // Cursor position on first line
#define LINE2(x)										(0xC0 + (x))  // Cursor position on second line

/* LCD Command Macros */
#define TWO_LINE_5x8_MATRIX_8_BIT					clcd_write(0x38, INSTRUCTION_COMMAND)   // 8-bit, 2-line, 5x8 font
#define CLEAR_DISP_SCREEN				                clcd_write(0x01, INSTRUCTION_COMMAND)  // Clear LCD display
#define CURSOR_HOME							clcd_write(0x02, INSTRUCTION_COMMAND)            // Move cursor to home position
#define DISP_ON_AND_CURSOR_OFF						clcd_write(0x0C, INSTRUCTION_COMMAND)   // Display ON, cursor OFF

/* LCD Initialization Command */
#define EIGHT_BIT_MODE   0x33

/* Initializes the Character LCD with the required display configuration.*/
void init_clcd(void);

/* Displays a complete string starting from the specified LCD address.*/
void clcd_print(const unsigned char *data, unsigned char addr);

/* Displays a single character at the specified LCD position. */
void clcd_putch(const unsigned char data, unsigned char addr);

/* Sends either a command or data byte to the LCD. */
void clcd_write(unsigned char bit_values, unsigned char control_bit);


#endif	/* CLCD_H */

