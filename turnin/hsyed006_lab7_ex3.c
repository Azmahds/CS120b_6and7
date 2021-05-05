/*	Author: Hamza Syed
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 7  Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *  Demo  Link: https://drive.google.com/file/d/1ldxvJnaKQhzLh5LuSfaRSZDyaBN20c3u/view?usp=sharing
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
//#include "timer.h"
#endif

void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

enum states {off, on} state;
unsigned short x;
unsigned char tb = 0x00;
unsigned char td = 0x00;
unsigned short max = 590;

void Light(){
	x = ADC;
	tb = (char)x;
	td = (char)(x >> 8);

	switch(state){
		case off:
			if(x >= (max/2)){
				state = on;
			}
			else{state = off;}
		break;

		case on:
			if(x < (max/2)){
				state = off;
			}
			else {state = on;}
		break;	
	}

	switch(state){
		case off:
			PORTB = 0;
			PORTD = 0;
		break;

		case on:
			PORTB = tb;
			PORTD = td;
		break;	
	}

}



int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

	DDRA = 0x00; PORTA = 0xFF;
    /* Insert your solution below */
	
	ADC_init();
	while (1) {
		Light();
	}
    return 1;
}
