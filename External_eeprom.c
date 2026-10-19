/*
 * File:   ds1307.c
 * Author: DELL
 *
 * Created on 14 July, 2026, 8:55 AM
 */



/* Include required header files */
#include "External_eeprom.h"
#include "i2c.h"
#include <xc.h>


/* Writes a single byte of data into external EEPROM
   using I2C communication.*/
void write_external_eeprom(unsigned char address, unsigned char data)
{
    /*  Generate I2C start condition
        to begin communication.*/
	i2c_start();
    
     /*
       Send EEPROM slave address
       with write operation.
     */
	i2c_write(SLAVE_WRITE);
    
    /*
      Send memory location where
       data needs to be stored.
     */
	i2c_write(address);
    
    /*
       Send actual data byte
       to EEPROM.
     */
	i2c_write(data);
    
    /*
      Generate I2C stop condition to complete transaction.
     */
	i2c_stop();
    
    //EEPROM takes some time to write for the delay
    for(int i = 3000 ; i--;);
}

unsigned char read_external_eeprom(unsigned char address)
{
	unsigned char data;

    /*  Generate I2C start condition */
	i2c_start();
    
    /*  Send EEPROM slave address with write operation.*/
	i2c_write(SLAVE_WRITE);
    
     /* Select EEPROM memory location from where data has to be read. */
	i2c_write(address);
    
    /* Generate repeated start condition without releasing I2C bus. */
	i2c_rep_start();
    
     /* Send EEPROM slave address with read operation.*/
	i2c_write(SLAVE_READ);
    
    /* Read data byte from EEPROM. */
	data = i2c_read();
    
    /* Stop I2C communication. */
	i2c_stop();

     /* Return received EEPROM data */
	return data;
}
