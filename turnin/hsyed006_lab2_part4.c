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
        DDRB = 0x00;
        PORTB = 0xFF;
	DDRC = 0x00;
	PORTC = 0x00;
	DDRD = 0xFF;
	PORTD = 0x00; 
        unsigned char a = 0x00, b = 0x00, c = 0x00, tmp = 0x00; //temp variable


    /* Insert your solution below */
    while (1) {
	a = PINA;
	b = PINB;
	c = PINC;
	
	tmp = a + b + c;
	
	
	tmp = tmp >> 2;
	tmp = tmp & 0xFC;
	
	if((a+b+c) > 140){
		tmp = tmp | 0x01;
	}
	
	if((a-c) > 80 || (c-a) > 80){
		tmp = tmp | 0x02;
	}
  
	PORTD = tmp;
    }
    return 1;
}

