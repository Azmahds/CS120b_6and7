/*	Author: hsyed006
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char a = 0x00, b = 0x00, tmp = 0x00;
    /* Insert your solution below */
    while (1) {
	a = PINA;
	b = PINB;
	
	tmp = 0;
	
	int i = 0;
	while(i < 8){
		++i;
		if((a & 0x01) ==0x01){tmp += 1;}
		if((b & 0x01) == 0x01){tmp++;}
		a = PINA >> i;
		b = PINB >> i;
	}

	PORTC = tmp;
	
    }
    return 1;
}
