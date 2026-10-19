/*
 * File:   ds1307.c
 * Author: DELL
 *
 * Created on 14 July, 2026, 8:55 AM
 */



/* Include required header files */
#include "ds1307.h"
#include "i2c.h"
#include "clcd.h"
#include <xc.h>

/* 
 * DS1307 Slave address
 * D0  -  Write Mode
 * D1  -  Read Mode
 */
 
char time[10];

/*  Initializes the DS1307 RTC module. */
void init_ds1307(void)
{
	unsigned char dummy;

	/* Setting the CH bit of the RTC to Stop the Clock */
	dummy = read_ds1307(SEC_ADDR);
	write_ds1307(SEC_ADDR, dummy | 0x80); 

	/* Seting 12 Hr Format */
	dummy = read_ds1307(HOUR_ADDR);
	write_ds1307(HOUR_ADDR, dummy | 0x40); 

	/* 
	 * Control Register of DS1307
	 * Bit 7 - OUT
	 * Bit 6 - 0
	 * Bit 5 - OSF
	 * Bit 4 - SQWE
	 * Bit 3 - 0
	 * Bit 2 - 0
	 * Bit 1 - RS1
	 * Bit 0 - RS0
	 * 
	 * Seting RS0 and RS1 as 11 to achive SQW out at 32.768 KHz
	 */ 
	write_ds1307(CNTL_ADDR, 0x93); 
    
//    write_ds1307(HOUR_ADDR, 0x08);
//    write_ds1307(MIN_ADDR, 0x45);
//    write_ds1307(SEC_ADDR, 0x56);
    

	/* Clearing the CH bit of the RTC to Start the Clock */
	dummy = read_ds1307(SEC_ADDR);
	write_ds1307(SEC_ADDR, dummy & 0x7F); 

}

/* Writes one byte of data into DS1307 register. */
void write_ds1307(unsigned char address, unsigned char data)
{
    /* Start I2C communication */
	i2c_start();
    
    /* Send DS1307 slave address in write mode */
	i2c_write(SLAVE_WRITE);
    
    /* Select RTC register address */
	i2c_write(address);
    
    /* Write data into selected register */
	i2c_write(data);
    
      /* Stop I2C communication */
	i2c_stop();
}

/*  Reads one byte of data from DS1307 register. */
unsigned char read_ds1307(unsigned char address)
{
	unsigned char data;

    /* Start I2C communication */
	i2c_start();
    
     /* Send RTC slave address with write command */
	i2c_write(SLAVE_WRITE);
    
     /* Select register to read */
	i2c_write(address);
    
    /*  Restart communication
       and request data from RTC */
	i2c_rep_start();
    
    /* Send RTC slave address with read command */
	i2c_write(SLAVE_READ);
    
     /* Read data from RTC */
	data = i2c_read();
    
    /* Stop I2C communication */
	i2c_stop();

	return data;
}

/* Displays current time on LCD */
void display_time(void)
{
    /* Display HH:MM:SS format */
	clcd_print(time, LINE2(2));

    /* Check whether RTC is configured
       in 12-hour mode.*/
	if (clock_reg[0] & 0x40)
	{
        
        /*
         * Bit 5 indicates AM/PM status:
         * 1 - PM
         * 0 - AM
         */
		if (clock_reg[0] & 0x20)
		{
			clcd_print("PM", LINE2(12));
		}
		else
		{
			clcd_print("AM", LINE2(12));
		}
	}
}

/* 
   Reads current time from DS1307 RTC
   and converts BCD values into ASCII format
   for LCD display.*/
void get_time(void)
{
    /*
       Read RTC registers:
       clock_reg[0] - Hours
       clock_reg[1] - Minutes
       clock_reg[2] - Seconds
     */
	clock_reg[0] = read_ds1307(HOUR_ADDR);
	clock_reg[1] = read_ds1307(MIN_ADDR);
	clock_reg[2] = read_ds1307(SEC_ADDR);

    
    /*
     * Convert hour value.
     *
     * Different conversion is used
     * for 12-hour and 24-hour modes.
     */
	if (clock_reg[0] & 0x40)
	{
        /* 12-hour format conversion */
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	else
	{
        /* 24-hour format conversion */
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
      /* Insert colon separator */
	time[2] = ':';
    
    /* Convert minutes from BCD to ASCII */
	time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
	time[4] = '0' + (clock_reg[1] & 0x0F);
    
    /* Insert colon separator */
	time[5] = ':';
    
    /* Convert seconds from BCD to ASCII */
	time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
	time[7] = '0' + (clock_reg[2] & 0x0F);
    
     /* Null terminate string */
	time[8] = '\0';
}
