
#ifndef MATRIX_KEYPAD_H
#define	MATRIX_KEYPAD_H

/* Matrix Keypad Configuration */
#define MAX_ROW				4     // Number of keypad rows
#define MAX_COL				3     // Number of keypad columns

/* Key Detection Modes */
#define STATE_CHANGE				1   // Detect key press only on state change
#define LEVEL_CHANGE				0   // Detect key as long as it is pressed

/* Matrix Keypad Port Configuration */
#define MATRIX_KEYPAD_PORT			PORTB   // Keypad connected to PORTB

/* Row Connections */
#define ROW3					PORTBbits.RB7
#define ROW2					PORTBbits.RB6
#define ROW1					PORTBbits.RB5

/* Column Connections */
#define COL4					PORTBbits.RB4
#define COL3					PORTBbits.RB3
#define COL2					PORTBbits.RB2
#define COL1					PORTBbits.RB1

/* Each macro represents a key number on the keypad. */
#define MK_SW1					1
#define MK_SW2					2
#define MK_SW3					3
#define MK_SW4					4
#define MK_SW5					5
#define MK_SW6					6
#define MK_SW7					7
#define MK_SW8					8
#define MK_SW9					9
#define MK_SW10				10
#define MK_SW11				11
#define MK_SW12				12


/* Indicates that no key is currently pressed */
#define ALL_RELEASED	0xFF

/* Logic Levels */
#define HI				1
#define LO				0

/* Initializes the matrix keypad by configuring the
   required row and column pins.*/
void init_matrix_keypad(void);

/* Scans the keypad rows and columns to determine which
 * key is currently pressed. */
unsigned char scan_key(void);

/*  Reads the keypad based on the selected detection mode. */
unsigned char read_switches(unsigned char detection_type);


#endif	/* MATRIX_KEYPAD_H */

