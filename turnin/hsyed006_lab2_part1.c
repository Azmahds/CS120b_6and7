/*	Author: hsyed006
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 2  Exercise 1
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
        unsigned char a = 0x00, b = 0x00; //temp variables

    /* Insert your solution below */
    while (1) {
        a = PINA & 0x01;
        b = PINA & 0x02;

        if(a == 0x01 && b == 0x00){
                PORTB = 0x01;
        }
        else{PORTB = 0x00;}
    }
    return 1;
}

