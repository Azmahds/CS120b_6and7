/*	Author: Hamza Syed
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 7  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *	 Demo Link: https://drive.google.com/file/d/1qf0YTqIoA6veNLvmMC_iG2HtsQI3UrA5/view?usp=sharing
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
//#include "timer.h"
#endif

void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

	DDRA = 0x00; PORTA = 0xFF;
    /* Insert your solution below */
	
	ADC_init();
	unsigned short x = ADC;
	unsigned char tmpb = 0x00;
	unsigned char tmpd = 0x00;	
	while (1) {
    		x = ADC;
		tmpb = (char)x;
		tmpd = (char)(x >> 8);
		PORTB = tmpb;
		PORTD = tmpd;
	}
    return 1;
}
