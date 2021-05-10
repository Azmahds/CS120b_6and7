/*	Author: lab
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
//#include "timer.h"
#endif

void set_PWM(double frequency){
	static double current_frequency;

	if(frequency != current_frequency){
		if(!frequency) {TCCR3B &= 0x08;}
		else{TCCR3B |= 0x03;}


		if(frequency < 0.954) { OCR3A = 0xFFFF;}

		else if(frequency > 31250){OCR3A = 0x0000;}

		else{OCR3A = (short)(8000000/(128*frequency)) - 1;}

		TCNT3 = 0;
		current_frequency = frequency;
	}
}


void PWM_on(){
	TCCR3A = (1 << COM3A0);

	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);

	set_PWM(0);
}

void PWM_off(){
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}


enum states {init, off, toneC, toneD, toneE} state;
unsigned char button = 0x00;

void tone(){
	button = ~PINA & 0x07;

	switch(state){
		case init:
			if(button == 0x01){state = toneC;}
			else if(button == 0x02){state = toneD;}
			else if (button == 0x04){state = toneE;}
			else{state = init;}
		break;
		
		case off:

		break;

		case toneC:
			if(!(button == 0x01)){state = init;}
			else {state = toneC;}
		break;

		case toneD:
			if(!(button == 0x02)){state = init;}
			else {state = toneD;}

		break;

		case toneE:
			if(!(button == 0x04)){state = init;}
			else {state = toneE;}

		break;
	}	

	switch(state){
		case init:
			set_PWM(0.0);
		break;
		
		case off:

		break;

		case toneC:
			set_PWM(261.63);
		break;

		case toneD:
			set_PWM(293.66);
		break;

		case toneE:
			set_PWM(329.63);

		break;
	}	
}

	


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0x40; PORTB = 0x00;

	DDRA = 0x00; PORTA = 0xFF;
    /* Insert your solution below */
	
	state = init;
	PWM_on();
	while (1) {
		tone();
	}
    return 1;
}
