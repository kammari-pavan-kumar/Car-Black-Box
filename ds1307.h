

#ifndef DS1307_H
#define	DS1307_H

/* DS1307 I2C Slave Addresses */
#define SLAVE_READ		0xD1    // DS1307 slave address for read operation
#define SLAVE_WRITE		0xD0   // DS1307 slave address for write operation

/* DS1307 Register Addresses */
#define SEC_ADDR		0x00    // Seconds register
#define MIN_ADDR		0x01    // Minutes register
#define HOUR_ADDR		0x02    // Hours register
#define DAY_ADDR		0x03    // Day register
#define DATE_ADDR		0x04    // Date register
#define MONTH_ADDR		0x05    // Month register
#define YEAR_ADDR		0x06    // Year register
#define CNTL_ADDR		0x07    // Control register

/* Stores the current time in HH:MM:SS format.
  clock_reg[0] -> Hours
  clock_reg[1] -> Minutes
 clock_reg[2] -> Seconds */
char clock_reg[3];

/* Writes a byte of data to the specified DS1307 register. */
void write_ds1307(unsigned char address1,  unsigned char data);

/* Reads a byte of data from the DS1307 register. */
unsigned char read_ds1307(unsigned char address1);

/* Displays the current RTC time on the LCD. */
void display_time(void);

/* Reads the current time from the DS1307 RTC and stores
   it in the clock_reg array. */
void get_time(void);

/* Initializes the DS1307 RTC and configures it for
   real-time clock operation. */
void init_ds1307(void);
#endif	/* DS1307_H */

