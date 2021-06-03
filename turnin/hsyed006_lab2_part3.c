/*	Author: hsyed006
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 2  Exercise 2
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
        DDRA = 0x00;
        PORTA = 0xFF;
        DDRB = 0xFF;
        PORTB = 0x00;
        unsigned char a = 0x00, b = 0x00; //temp variable
	unsigned char cntavail = 0;

    /* Insert your solution below */
    while (1) {
	a = PINA;
	cntavail = 0;
	if(!(a & 0x01)){
		cntavail += 1;
	}
	if(!(a & 0x02)){
                cntavail += 1;
        }
	if(!(a & 0x04)){
                cntavail += 1;
        }
	if(!(a & 0x08)){
                cntavail += 1;
        }
	
	if(cntavail == 0){PORTC = 0x80;}
	else{ PORTC = cntavail;}
    }
    return 1;
}

