/*
 * File:   adc.c
 * Author: DELL
 *
 * Created on 14 July, 2026, 8:56 AM
 */



#include <xc.h>
#include "adc.h"

/* Initializes the ADC module by configuring the conversion
   format, acquisition time, conversion clock, voltage
   references, and enabling the ADC peripheral*/
void init_adc(void)
{
	/* Selecting right justified ADRES Registers order */
	ADFM = 1;

	/* 
	 * Acqusition time selection bits 
	 * Set for 4 Tad
	 */
	ACQT2 = 0;
	ACQT1 = 1;
	ACQT0 = 0;

	/*
	 * Selecting the conversion clock of Fosc / 32 -> 1.6usecs -> 1Tad
	 * Our device frequency is 20 MHz
	 */
	ADCS0 = 0;
	ADCS1 = 1;
	ADCS2 = 0;

	/* Stop the conversion to start with */
	GODONE = 0;

	

	/* Voltage reference bit as VSS */
	VCFG1 = 0;
	/* Voltage reference bit as VDD */
	VCFG0 = 0;

	/* Just clearing the ADRESH & ADRESL registers, for time pass */
	ADRESH = 0;
	ADRESL = 0;

	/* Turn ON the ADC module */
	ADON = 1;
}


/* Selects the required ADC channel, starts the conversion,
   waits until the conversion is complete, and returns the
   converted digital value.*/
unsigned short read_adc(unsigned char channel)
{
	unsigned short reg_val;

	/*select the channel*/
	ADCON0 = (ADCON0 & 0xC3) | (channel << 2);

	/* Start the conversion */
	GO = 1;
    /* Wait until conversion is completed */
	while (GO);
    /* Combine high and low result registers */
	reg_val = (ADRESH << 8) | ADRESL; 

    /* Return the converted digital value */
	return reg_val;
}