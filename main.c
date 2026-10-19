/*
 * File:   main.c
 * Author: DELL
 *
 * Created on 14 July, 2026, 8:54 AM
 */

/* Include required header files */
#include "black_box.h"
#include "matrix_keypad.h"
#include "adc.h"
#include "clcd.h"
#include "ds1307.h"
#include "i2c.h"

State_t state;
unsigned char key;

/*  Performs initial application configuration. */
void init_config() 
{

    /* Start application in dashboard mode. */
    state = e_dashboard;
}

void main(void)
{
    /* Initialize application state. */
    init_config();
    
    /* Initialize LCD module. */
    init_clcd();
    
    /* Initialize matrix keypad. */
    init_matrix_keypad();
    
    /*  Initialize ADC module */
    init_adc();
    
    /* Initialize I2C communication. */
    init_i2c();
    
    
    //load_log_count();
    
    /* Initialize RTC module. */
    init_ds1307();
    
    /* Initialize UART communication for log download. */
    init_uart();
    
    /* Stores previous state value. Used to detect state changes and clear LCD only once.*/
    State_t prev_state = -1;

    while (1) {
        // Detect key press
        key = read_switches(STATE_CHANGE);
        
        /* Check if application state changed. Clear LCD when entering a new screen. */
        if (state != prev_state) 
        {
            CLEAR_DISP_SCREEN;
            prev_state = state;
        }

        /* Executes corresponding function based on current application state. */
        switch (state)
        {
            /* Dashboard screen: */
            case e_dashboard:
                clcd_print("TIME", LINE1(0));
                clcd_print("EV", LINE1(10));
                clcd_print("SP", LINE1(14));
                view_dashboard();
                break;

                /* Main menu screen: */
            case e_main_menu:
                display_main_menu();
                break;

                /* Displays stored event logs*/
            case e_view_log:

                clcd_print("L", LINE1(0));
                clcd_print("TIME", LINE1(2));
                clcd_print("EV", LINE1(11));
                clcd_print("SP", LINE1(14));
                view_log();
                break;

                /* Download log screen*/
            case e_download_log:
                download_log();
                break;

                /* Clear log screen */
            case e_clear_log:
                clear_log();
                break;


                /* Allows user to modify RTC hour and minute values.*/
            case e_set_time:
                set_time();
                break;

        }

    }

}
