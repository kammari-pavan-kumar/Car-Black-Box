
#ifndef I2C_H
#define	I2C_H

/* Initializes the I2C module by configuring the required
   registers for master mode communication.*/
void init_i2c(void);

/* Generates the START condition to begin I2C communication. */
void i2c_start(void);

/* Generates a REPEATED START condition without releasing the I2C bus. */
void i2c_rep_start(void);

/* Generates the STOP condition to terminate I2C communication. */
void i2c_stop(void);

/* Sends one byte of data over the I2C bus to the slave device. */
void i2c_write(unsigned char data);

/* Reads a byte of data from the I2C bus. */
unsigned char i2c_read(void);

#endif	/* I2C_H */

