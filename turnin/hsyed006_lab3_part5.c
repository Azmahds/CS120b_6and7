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
	DDRD = 0x00; PORTD = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	//DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char a = 0x00, b = 0x00, tmp = 0x00;
    /* Insert your solution below */
    while (1) {
	a = PIND;
 	if  (a >= 70){
		PORTB = 0x02;
	}	
	else if (5 < a < 70){PORTB = 0x04;}
	else {PORTB = 0x00;}
    }
    return 1;
}
