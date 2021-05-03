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
#include "timer.h"
#endif

enum States {init, one, two, three}  State;
unsigned char tmp  =  0x00;
void blink(){
	
	switch(State){
		case init:
			State = one;		
		break;
	
		case one:
			State = two;
		break;

		case two:
			State = three;
		break;

		case three:
			State = one;
		break;
		
		default:
			State = init;
		break;
	}
	
	switch(State){
		case init:
					
		break;
	
		case one:
			tmp = 0x01;
		break;

		case two:
			tmp = 0x02;
		break;

		case three:
			tmp = 0x04;
		break;

	}
	PORTB = tmp;
}



int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
	TimerSet(1000);
	TimerOn();
	State = init;
    
	while (1) {
		blink();
		while(!TimerFlag);
		TimerFlag = 0;
    }
    return 1;
}
