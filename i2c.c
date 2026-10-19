/*
 * File:   i2c.c
 * Author: DELL
 *
 * Created on 14 July, 2026, 8:55 AM
 */


#include <xc.h>

/* Initializes the I2C module of PIC controller in master mode. */
void init_i2c(void)
{
	/* Set SCL and SDA pins as inputs */
	TRISC3 = 1;
	TRISC4 = 1;
	/* Set I2C master mode */
	SSPCON1 = 0x28;

	SSPADD = 0x31;
	/* Use I2C levels, worked also with '0' */
	CKE = 0;
	/* Disable slew rate control  worked also with '0' */
	SMP = 1;
	/* Clear SSPIF interrupt flag */
	SSPIF = 0;
	/* Clear bus collision flag */
	BCLIF = 0;
}

/*  Waits until current I2C operation is completed. */
void i2c_idle(void)
{
    /* Wait until I2C operation finishes */
	while (!SSPIF);
     /* Clear operation complete flag */
	SSPIF = 0;
}

/* Checks acknowledgement from slave device after data transmission.*/
void i2c_ack(void)
{
    /* ACKSTAT = 1 indicates slave did not acknowledge data. */
	if (ACKSTAT)
	{
		/* Do debug print here if required */
	}
}

/* Generates I2C START condition. */
void i2c_start(void)
{
    /* Enable start condition */
	SEN = 1;
    /* Wait until completion */
	i2c_idle();
}

/* Generates I2C STOP condition. */
void i2c_stop(void)
{
    /* Enable stop condition */
	PEN = 1;
    /* Wait until completion */
	i2c_idle();
}

/* Generates repeated START condition */
void i2c_rep_start(void)
{
    /* Enable repeated start condition */
	RSEN = 1;
    /* Wait until completion */
	i2c_idle();
}

/* Sends one byte of data through I2C bus. */
void i2c_write(unsigned char data)
{
    /* Load transmit buffer. */
	SSPBUF = data;
    /* Wait until completion */
	i2c_idle();
}

/* Enables I2C receive mode to read data from slave device. */
void i2c_rx_mode(void)
{
    /* Enable receive mode. */
	RCEN = 1;
    /* Wait until completion */
	i2c_idle();
}

/* Sends NACK signal after receiving data. */
void i2c_no_ack(void)
{
    /* Set ACK data bit to 1. This generates NACK. */
	ACKDT = 1;
    /* Enable acknowledge sequence. */
	ACKEN = 1;
}

/* Reads one byte of data from I2C slave. */
unsigned char i2c_read(void)
{
    /* Enable receive mode */
	i2c_rx_mode();
    /* Send NACK after receiving data. */
	i2c_no_ack();

     /* Return received data */
	return SSPBUF;
}
