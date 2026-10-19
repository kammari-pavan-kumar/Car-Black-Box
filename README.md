# Car Black Box

A microcontroller-based Car Black Box project developed using Embedded C and PIC18F4580 to display vehicle information and record driving events with time and speed details.

## Features

- Live Dashboard - Displays vehicle information, time, and speed.
- Event Logging - Records driving events along with time and speed information.
- Real-Time Clock - Uses the DS1307 RTC to maintain time information.
- Event Storage - Stores event records in external EEPROM.
- Circular Buffer - Reuses storage locations when the event log becomes full.
- Keypad Interface - Uses a matrix keypad to interact with the system.

## Technologies Used

- Programming Language: Embedded C
- Microcontroller: PIC18F4580
- IDE: MPLAB X IDE
- Compiler: MPLAB XC8
- Communication Protocol: I2C
- Peripherals: CLCD, Matrix Keypad, ADC, DS1307 RTC, and External EEPROM
- Concepts: Microcontroller Interfacing, Peripheral Drivers, Circular Buffer, Event Logging, and EEPROM Data Storage

---

## Installation

### Prerequisites

- MPLAB X IDE.
- MPLAB XC8 Compiler.
- PIC18F4580 microcontroller or a compatible development board.
- Required hardware peripherals and circuit connections.

### Get the Project

1. Download the project from GitHub as a ZIP file.
2. Extract the downloaded ZIP file.
3. Open MPLAB X IDE.
4. Select File → Open Project.
5. Navigate to the extracted project folder and open the Car Black Box project.

---

## How to Build and Run

### Using MPLAB X IDE

1. Open the project in MPLAB X IDE.
2. Verify that the PIC18F4580 microcontroller and XC8 compiler are selected.
3. Build the project using Clean and Build Project.
4. Connect the required hardware peripherals.
5. Program the generated HEX file into the microcontroller.
6. Power on the system and test the dashboard and event-logging functionality.

Note: Ensure that the hardware connections and peripheral configurations match the project implementation.

---

## Project Structure

    Car-Black-Box/
    |
    |-- main.c
    |-- main.h
    |-- black_box.c
    |-- black_box.h
    |-- clcd.c
    |-- clcd.h
    |-- matrix_keypad.c
    |-- matrix_keypad.h
    |-- adc.c
    |-- adc.h
    |-- ds1307.c
    |-- ds1307.h
    |-- i2c.c
    |-- i2c.h
    |-- External_eeprom.c
    |-- External_eeprom.h
    |-- nbproject/
    |-- README.md

Note: Make sure the filenames match the actual files in your GitHub repository.

---

## File Responsibilities

- main.c: Contains the main function and controls the overall program flow.
- main.h: Contains shared declarations and project definitions.
- black_box.c: Implements the main black box functionality and event logging.
- black_box.h: Contains declarations related to black box operations.
- clcd.c / clcd.h: Handles the character LCD interface.
- matrix_keypad.c / matrix_keypad.h: Handles matrix keypad input.
- adc.c / adc.h: Implements analog-to-digital conversion.
- ds1307.c / ds1307.h: Handles DS1307 real-time clock operations.
- i2c.c / i2c.h: Implements I2C communication.
- External_eeprom.c / External_eeprom.h: Handles external EEPROM read and write operations.
- nbproject/: Contains MPLAB X IDE project configuration files.
- README.md: Describes the project and explains how to build and use it.

---

## Data Storage

The application uses external EEPROM to store event information.

- Each event record occupies 12 bytes.
- Each record contains time, event, and speed information.
- The configured event log supports a maximum of 10 records.
- The circular buffer reuses storage locations when the buffer becomes full.

The exact record format and storage addresses depend on the implementation in the source code.

---

## Learning Outcomes

- Improved understanding of Embedded C programming.
- Practiced PIC18F4580 microcontroller programming.
- Learned peripheral interfacing with CLCD, matrix keypad, ADC, RTC, and external EEPROM.
- Gained practical experience with I2C communication.
- Understood circular buffer implementation and event logging.
- Improved modular embedded software development skills.

---

## Applications

- Vehicle event monitoring.
- Automotive data logging.
- Embedded systems development and practice.
- Microcontroller peripheral interfacing.

---

## Author

K. Pavan Kumar
