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
	//DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char a = 0x00, b = 0x00, tmp = 0x00;
    /* Insert your solution below */
    while (1) {
	a = PINA & 0x0F;
	b = PINA >> 4;
	
	if (a  == 0x00){tmp = 0x40;}
	else if(a < 3){tmp  = 0x50;}
	else if(a < 5){tmp  = 0x70;}
	else if(a < 7){tmp  = 0x38;}
	else if(a < 10){tmp  = 0x3C;}
	else if(a < 13){tmp  = 0x3E;}
	else {tmp  = 0x3F;}
	
	if(b == 0x03){tmp = tmp | 0x80;}
	PORTC = tmp;	
    }
    return 1;
}
