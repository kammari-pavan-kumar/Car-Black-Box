
#ifndef AT24C04_H
#define	AT24C04_H

/* AT24C04 I2C Slave Addresses */
#define SLAVE_READ		0xA1  // EEPROM slave address for read operation
#define SLAVE_WRITE		0xA0  // EEPROM slave address for write operation

/* EEPROM address reserved for storing the current log index */
#define LOG_INDEX_ADDR 0x01

/* Writes a single byte of data to the specified EEPROM memory location.*/
void write_external_eeprom(unsigned char address1,  unsigned char data); 

/* Reads a single byte of data from the specified EEPROM
   memory location. */
unsigned char read_external_eeprom(unsigned char address1);
#endif	/* AT24C04_H */

