
#ifndef BLACK_BOX_H
#define	BLACK_BOX_H

#include <xc.h>


typedef enum {
    e_dashboard, e_main_menu, e_view_log, e_set_time, e_download_log, e_clear_log
} State_t;

/* Maximum number of gear positions */
#define MAX_GEAR 6

/* EEPROM address reserved for storing log count */
#define LOG_COUNT_ADDR 0x00 
/* ADC channel connected to the speed sensor */
#define SPEED_ADC_CHANNEL 0x04
/* Key definitions for gear control */
#define GEAR_UP             SWITCH1
#define GEAR_DOWN           SWITCH2
#define COLLISION           SWITCH3

/*  Reads the speed sensor value and converts it into
    the corresponding vehicle speed.*/

/* Reads the analog speed sensor value through ADC and
   converts it into the corresponding vehicle speed. */
uint24_t get_speed();

/* Initializes the UART peripheral for serial communication. */
void init_uart(void);

/* Current application state */
extern State_t state; 

//Dashboard function declaration
void view_dashboard(void);

//main menu function declaration
void display_main_menu(void);

//View log function declaration
void view_log(void);

//Reading events function declaration
void event_reader(void);

//Set time function declaration
void set_time(void);

//Download log function declaration
void download_log(void);

//Clear log function declaration
void clear_log(void);

/* Converts a decimal number into a string. */
void decimal_to_string(unsigned char num, char *str);

/* Stores an event along with time and speed into EEPROM. */
void event_log(char *time,char *event,unsigned char *speed);

/* Loads the total number of stored logs from EEPROM. */
void load_log_count();
#endif	/* BLACK_BOX_H */

