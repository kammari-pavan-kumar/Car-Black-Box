/*
 * File:   dashboard.c
 * Author: DELL
 *
 * Created on 14 July, 2026, 2:40 PM
 */

/* Define crystal frequency for delay calculations */
#define _XTAL_FREQ 20000000  

/* Include required peripheral and driver header files */
#include <xc.h>
#include "matrix_keypad.h"
#include "adc.h"
#include "black_box.h"
#include "clcd.h"
#include "ds1307.h"
#include "i2c.h"
#include "External_eeprom.h"
#include "uart.h"

/* External variables used from other modules */
extern char time[10];    // Stores current RTC time
extern unsigned char key;  // Stores keypad key press value

/* Log management variables */
unsigned char log_count = 0;    // Number of stored event logs
unsigned char log_index = 0;    // Current log display index
unsigned char event_index = 0;  // EEPROM storage index for next event

/* Buffers to store logs read from EEPROM */
char time_buffer[12][9];   // Stores time values of logs
char event_buffer[12][3];  // Stores event/gear values
char speed_buffer[12][3];  // Stores speed values


unsigned int address;    // EEPROM memory address variable


/* Displays the current dashboard information such as
   time, gear position, and vehicle speed.*/
void view_dashboard()
{

    /* Get current time from RTC module */
    get_time();
    char str[3];    // Buffer to store speed value as string

    /* Read ADC value from speed sensor channel */
    uint24_t adc_value = read_adc(CHANNEL4);
    
    /* Convert ADC value into speed value */
    uint24_t speed_data = (adc_value / 10.3);

    /* Convert speed number into ASCII characters */
    str[0] = ((speed_data / 10) % 10) + '0';
    str[1] = (speed_data % 10) + '0';
    str[2] = '\0';

    

    /* Gear position names */
    char *gear_arr[] = {"ON", "GN", "G1", "G2", "G3", "G4", "G5", "GR", "GC"};


    /* Static variables retain their values between function calls */
    static int index = 0;
    static int collision_flag = 0;
    
    /* If collision occurs and user presses gear buttons,
       reset dashboard back to normal gear mode. */
    if (collision_flag == 1 && (key == MK_SW1 || key == MK_SW2)) 
    {
        index = 0;
        collision_flag = 0;
    }       
    /* Increase gear */
    else if (key == MK_SW1)
    {
        if (index < 7) 
        {
            index++;
            event_log(time, gear_arr[index], str);
        }

    }       
    /* Decrease gear */
    else if (key == MK_SW2)
    {
        if (index > 0) 
        {
            index--;
            event_log(time, gear_arr[index], str);
        }

    }       
    /* Collision detected */
    else if (key == MK_SW3) 
    {
        /* Set collision flag */
        collision_flag = 1;
        /* Set gear index to collision state */
        index = 8;
        
        /* Store collision event in EEPROM */
        event_log(time, gear_arr[index], str);
    }
     /* Open main menu */
    else if (key == MK_SW11)
    {
        state = e_main_menu;
    }
    /* Exit dashboard */
    else if (key == MK_SW12)
    {
        return;
    }

    /* Display dashboard information on CLCD */
    clcd_print(time, LINE2(0));

    /* Display current gear */
    clcd_print(gear_arr[index], LINE2(10));
    
    /* Display speed */
    clcd_print(str, LINE2(14));




}

/*  Displays the main menu options and handles navigation
    using keypad switches.*/
void display_main_menu() 
{
    /* Stores current selected menu option */
    static int index = 0;

     /* Array containing all menu options */
    char *menu_arr[] = {"VIEW LOG", "DOWNLOAD LOG", "CLEAR LOG", "SET TIME"};
     /* Move cursor down in menu */
    if (key == MK_SW2)
    {
        if (index < 3)
        {
            index++;
        }

    } 
    /* Move cursor up in menu */
    else if (key == MK_SW1) 
    {
        if (index > 0) 
        {
            index--;
        }

    }
    /* Select current menu option */
    else if (key == MK_SW11)
    {
        if (index == 0)
        {
            /* Open view log screen */
            CLEAR_DISP_SCREEN;
            state = e_view_log;
        } 
        else if (index == 1) 
        {
            /* Open download log function */
            CLEAR_DISP_SCREEN;
            state = e_download_log;
        }
        else if (index == 2)
        {
            /* Open clear log function */
            CLEAR_DISP_SCREEN;
            state = e_clear_log;
        } 
        else if (index == 3) 
        {
            /* Open set time function */
            CLEAR_DISP_SCREEN;
            state = e_set_time;
        }
    } 
    /* Return back to dashboard */
    else if (key == MK_SW12)
    {

        state = e_dashboard;

    }
    /* Clear LCD before displaying menu */
    CLEAR_DISP_SCREEN;
    
    /*  Display two menu items at a time */
    if (index < 2)
    {
        clcd_print(menu_arr[0], LINE1(3));
        clcd_print(menu_arr[1], LINE2(3));
    }
    else
    {
        clcd_print(menu_arr[2], LINE1(3));
        clcd_print(menu_arr[3], LINE2(3));
    }

    /* Display arrow indicator for selected option */
    if (index % 2 == 0)
    {
        clcd_print("->", LINE1(0));
    } 
    else
        clcd_print("->", LINE2(0));


    
    /* Small delay for button debounce */
    __delay_ms(200);


}

/* Stores time, event type, and speed information
   into external EEPROM memory. */
void event_log(char *time, char *event, unsigned char *speed)
{
    unsigned int address;

    /* Calculate EEPROM starting address.
       Each log occupies 12 bytes:
       8 bytes time + 2 bytes event + 2 bytes speed */
    address = event_index * 12;
    
    /* Store time information */
    for (int i = 0; i < 8; i++)
    {
        write_external_eeprom(address + i, time[i]);
    }
    /* Store event/gear information */
    write_external_eeprom(address + 8, event[0]);
    write_external_eeprom(address + 9, event[1]);
    
    /* Store speed information */
    write_external_eeprom(address + 10, speed[0]);
    write_external_eeprom(address + 11, speed[1]);
    
    /* Update EEPROM write index */
    event_index++;
    
    /* Implement circular buffer for 10 logs */
    if (event_index >= 10) 
    {
        event_index = 0;
    }
    
     /* Increase log count until maximum capacity */
    if (log_count < 10)
    {
        log_count++;
    }
    
    /*
     * EEPROM storage of log count and index
     * can be enabled if permanent storage is required.
     */
    //    write_external_eeprom(LOG_COUNT_ADDR, log_count);
    //    write_external_eeprom(LOG_INDEX_ADDR, event_index);
}

/* Reads stored logs from EEPROM and displays them
   on the LCD display.*/
void view_log()
{
    
    /* Ensures EEPROM is read only once when entering screen */
    static unsigned char once = 1;

    if (once == 1)
    {
         /* Load log details from EEPROM */
        event_reader();
        once = 0;
        log_index = 0;
    }

    /* Scroll logs forward */
    if (key == MK_SW1)
    {
        if (log_index < log_count - 1) 
        {
            log_index++;
        }
    }
    
    /* Scroll logs backward */
    else if (key == MK_SW2)
    {
        if (log_index > 0)
        {
            log_index--;
        }
    } 
     /* Return to main menu */
    else if (key == MK_SW12)
    {
        once = 1;
        CLEAR_DISP_SCREEN;
        state = e_main_menu;
        return;
    }
    /* Display message when no logs are available */
    if (log_count == 0) 
    {
        CLEAR_DISP_SCREEN;
        clcd_print("    NO LOGS", LINE1(0));
        clcd_print("  TO DISPLAY", LINE2(0));
        __delay_ms(200);
        return;
    }

    /* Display selected log information */
    clcd_putch(log_index + '0', LINE2(0));
    clcd_print(time_buffer[log_index], LINE2(2));
    clcd_print(event_buffer[log_index], LINE2(11));
    clcd_print(speed_buffer[log_index], LINE2(14));
    __delay_ms(200);

}

/* Sends stored logs through UART communication. */
void download_log()
{

    /* Prevent repeated EEPROM reading */
    static unsigned char once = 1;

    if (once == 1) 
    {
        CLEAR_DISP_SCREEN;
         /* Read logs from EEPROM */
        event_reader();
        once = 0;
    }

     /* Check whether logs are available */
    if (log_count == 0) 
    {
        clcd_print("    NO LOGS", LINE1(0));
        clcd_print("  TO DOWNLOAD", LINE2(0));
        puts("NO LOGS TO DISPLAY");
        __delay_ms(2000);
        state = e_main_menu;
        return;
    }
    
    /* Send each log through UART */
    for (int i = 0; i < log_count; i++)
    {
        putch(i + '0');
        putch(' ');
        puts(time_buffer[i]);
        putch(' ');
        putch(event_buffer[i][0]);
        putch(event_buffer[i][1]);
        putch(' ');
        putch(speed_buffer[i][0]);
        putch(speed_buffer[i][1]);

        putch('\r');
        putch('\n');
    }


     /* Display download success message */
    clcd_print("   DOWNLOADED", LINE1(0));
    clcd_print("  SUCCESSFULLY", LINE2(0));
    __delay_ms(2000);
    once = 1;
    
    /* Return to main menu */
    state = e_main_menu;


}

/* Clears all stored event logs. */
void clear_log()
{
    /* Clear LCD screen */
    CLEAR_DISP_SCREEN;
    
     /* Reset log counters */
    log_count = 0;
    event_index = 0;

    /* Display confirmation message */
    clcd_print("   CLEAR LOG", LINE1(0));
    clcd_print("  SUCCESSFULL", LINE2(0));
    
    
    __delay_ms(2000);
    /* Return to main menu */
    state = e_main_menu;
}


/*  Allows the user to modify RTC hour and minute values
   using keypad switches and updates the DS1307 RTC. */
void set_time(void)
{
    /* Variables to store edited hour and minute values */
    static char hour;
    static char min;
    
     /* Stores selected field:
       0 - Minute field
       1 - Hour field
    */
    static int field = 0;
    
    /* Used for blinking effect of selected field */
    static unsigned long int delay = 0;

    /* Ensures RTC values are loaded only once */
    static char once = 0;

    
    /*
       Read current RTC time when entering
       set time screen.
     */
    if (once == 0)
    {
        get_time();

        /*
           Convert BCD hour value from RTC
           into decimal format.
         */
        hour = ((clock_reg[0] >> 4) & 0x03) * 10 + (clock_reg[0] & 0x0F);
        
         /*
           Convert BCD minute value from RTC
           into decimal format.
         */
        min = ((clock_reg[1] >> 4) & 0x0F) * 10 + (clock_reg[1] & 0x0F);

        once = 1;
    }

    /* Switch between hour and minute selection.*/
    if (key == MK_SW2)
    {
        field = !field;
    }

    /* Increase minute value when minute field
       is selected.*/
    if (key == MK_SW1 && field == 0)
    {
        if (min++ > 58) {
            min = 0;
        }
    }

     /*
       Increase hour value when hour field
       is selected.
     */
    if (key == MK_SW1 && field == 1) {
        if (hour++ > 22)
        {
            hour = 0;
        }
    }

      /*
       Blink selected field to indicate
       currently editable parameter.
     */
    if (delay++ < 1200 && field == 0) 
    {
        /* Blink minute field */
        clcd_print("  ", LINE2(7));

    } 
    else if (delay++ < 1200 && field)
    {
        /* Blink hour field */
        clcd_print("  ", LINE2(4));

    }
    /* Display updated time value. */
    else if (delay < 2400) 
    {
        clcd_print("RESET TIME", LINE1(3));

        /* Convert hour into ASCII format */
        time[0] = hour / 10 + '0';
        time[1] = hour % 10 + '0';

        time[2] = ':';

        /* Convert minute into ASCII format */
        time[3] = min / 10 + '0';
        time[4] = min % 10 + '0';

        /* Seconds are reset to zero */
        time[5] = ':';
        time[6] = '0';
        time[7] = '0';
        time[8] = '\0';

        /* Display modified time */
        clcd_print(time, LINE2(4));
    } 
    else 
    {
        /* Reset blinking timer */
        delay = 0;
    }

    
    /*
       Save modified time into RTC
       when enter button is pressed.
     */
    if (key == MK_SW11) 
    {
        /*
           Convert decimal values back into
           BCD format required by DS1307.
         */
        clock_reg[0] = ((hour / 10) << 4) | (hour % 10);
        clock_reg[1] = ((min / 10) << 4) | (min % 10);

        /* Update RTC registers */
        write_ds1307(HOUR_ADDR, clock_reg[0]);
        write_ds1307(MIN_ADDR, clock_reg[1]);

        /* Allow reloading RTC values next time */
        once = 0;

        CLEAR_DISP_SCREEN;
        
         /* Return to main menu */
        state = e_main_menu;
    }

    
    /*
       Cancel time setting and return
       without saving changes.
     */
    if (key == MK_SW12) 
    {
        CLEAR_DISP_SCREEN;
        state = e_main_menu;
    }
}


/* 
   Reads event logs stored in external EEPROM
   and loads them into RAM buffers for display
   and UART download.*/
void event_reader(void) 
{
    unsigned int address;
    
    /* 
      Starting EEPROM location.
      If EEPROM contains 10 logs, start reading from the oldest log
      using circular buffer logic.*/
    unsigned char start;
    if (log_count == 10)
        start = event_index;
    else
        start = 0;
    
    /* Read each stored log entry. */
    for (int i = 0; i < log_count; i++) 
    {
        /*
          Calculate actual EEPROM index
          using circular buffer arrangement.
         */
        unsigned char index = (start + i) % 10;
        
        /*
           Calculate EEPROM address. Each log occupies 12 bytes.
         */
        address = index * 12;
        
        /* Read 8-byte time information. */
        for (int j = 0; j < 8; j++) 
        {
            time_buffer[i][j] = read_external_eeprom(address + j);
        }
        
         /* Add string termination character */
        time_buffer[i][8] = '\0';

        /* Read event/gear information. */
        event_buffer[i][0] = read_external_eeprom(address + 8);
        event_buffer[i][1] = read_external_eeprom(address + 9);
        event_buffer[i][2] = '\0';

        /* Read speed information. */
        speed_buffer[i][0] = read_external_eeprom(address + 10);
        speed_buffer[i][1] = read_external_eeprom(address + 11);
        speed_buffer[i][2] = '\0';
    }

}
