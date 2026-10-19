
#ifndef ADC_H
#define	ADC_H

/* ADC Channel Definitions */
#define CHANNEL0		0x00       // ADC Channel 0
#define CHANNEL1		0x01       // ADC Channel 1
#define CHANNEL2		0x02       // ADC Channel 2
#define CHANNEL3		0x03       // ADC Channel 3
#define CHANNEL4		0x04       // ADC Channel 4
#define CHANNEL5		0x05       // ADC Channel 5
#define CHANNEL6		0x06       // ADC Channel 6
#define CHANNEL7		0x07       // ADC Channel 7
#define CHANNEL8		0x08       // ADC Channel 8
#define CHANNEL9		0x09       // ADC Channel 9
#define CHANNEL10		0x0A       // ADC Channel 10

/*Initializes the ADC peripheral by configuring the required 
   registers for analog-to-digital conversion.*/
void init_adc(void);

/* Reads the analog voltage from the specified ADC channel and
   returns its digital equivalent.*/
unsigned short read_adc(unsigned char channel);

#endif	/* ADC_H */

