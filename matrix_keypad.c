/*
 * File:   matrix_keypad.c
 * Author: DELL
 *
 * Created on 14 July, 2026, 8:54 AM
 */

#include <xc.h>
#include "matrix_keypad.h"

/* Initializes the matrix keypad interface. */
void init_matrix_keypad(void)
{
	/* Config PORTB as digital */
	ADCON1 = 0x0F;

	/* Set Rows (RB7 - RB5) as Outputs and Columns (RB4 - RB1) as Inputs */
	TRISB = 0x1E;

	/* Set PORTB input as pull up for columns */
	RBPU = 0;

    /*  Set all row lines HIGH initially. */
	MATRIX_KEYPAD_PORT = MATRIX_KEYPAD_PORT | 0xE0;
}

unsigned char scan_key(void)
{
    /* Scans the matrix keypad to identify the pressed key.*/
	ROW1 = LO;
	ROW2 = HI;
	ROW3 = HI;

    /* Check columns of first row. */
	if (COL1 == LO)
	{
		return 1;
	}
	else if (COL2 == LO)
	{
		return 4;
	}
	else if (COL3 == LO)
	{
		return 7;
	}
	else if (COL4 == LO)
	{
		return 10;
	}

    /* Select second row. */
	ROW1 = HI;
	ROW2 = LO;
	ROW3 = HI;

    /*  Check columns of second row. */
	if (COL1 == LO)
	{
		return 2;
	}
	else if (COL2 == LO)
	{
		return 5;
	}
	else if (COL3 == LO)
	{
		return 8;
	}
	else if (COL4 == LO)
	{
		return 11;
	}

    /* Select third row. */
	ROW1 = HI;
	ROW2 = HI;
	ROW3 = LO;
	/* TODO: Why more than 2 times? */
	ROW3 = LO;

    /* Check columns of third row. */
	if (COL1 == LO)
	{
		return 3;
	}
	else if (COL2 == LO)
	{
		return 6;
	}
	else if (COL3 == LO)
	{
		return 9;
	}
	else if (COL4 == LO)
	{
		return 12;
	}

    /* No key press detected. */
	return 0xFF;
}

/*  Reads keypad input based on detection mode. */
unsigned char read_switches(unsigned char detection_type)
{
    /* Static variables retain values between function calls. */
	static unsigned char once = 1, key;

    /* State change detection mode. */
	if (detection_type == STATE_CHANGE)
	{
        /* Scan keypad. */
		key = scan_key();
        
        /* Detect only first occurrence of key press. */
		if(key != 0xFF && once  )
		{
            /* Disable repeated detection until key is released. */
			once = 0;
			return key;
		}
        /* Enable next key detection. */
		else if(key == 0xFF)
		{
			once = 1;
		}
	}
    /* Level change mode: Return current key status directly. */
	else if (detection_type == LEVEL_CHANGE)
	{
		return scan_key();
	}

    /* No valid key press. */
	return 0xFF;
}
