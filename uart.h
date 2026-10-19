#ifndef SCI_H
#define SCI_H

/* UART Receive pin (RC7) configuration */
#define RX_PIN					TRISC7

/* UART Transmit pin (RC6) configuration */
#define TX_PIN					TRISC6

/* Initialize UART module for asynchronous
   serial communication.*/
void init_uart(void);

/* Transmit a single byte through UART. */
void putch(unsigned char byte);

/* Transmit a null-terminated string through UART. */
int puts(const char *s);

/* Receive a single byte from UART. */
unsigned char getch(void);

/* Receive a byte from UART with a timeout limit. */
unsigned char getch_with_timeout(unsigned short max_time);

/* Receive a byte and transmit it back */
unsigned char getche(void);

#endif /* SCI_H */
