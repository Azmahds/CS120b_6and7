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


enum states {init, C4, D, E, F, G, A, B, C5} state;
unsigned char button = 0x00;
unsigned char depressed = 0x00;


void tone(){
	switch(state){
		case init:
			if((button & 0x01) && (depressed == 0x00)){depressed = 0x01; state = C4;}
			else {state = init;}
		break;

		case C4:
			state = B;
		break;

		case D:
			state = init;
		break;

		case E:
			state = G;
		break;
		
		case F:
			state = init;
                break;

                case G:
			state = C5;
		break;

                case A:
			state = init;
                break;

                case B:
			state = E;
                break;

                case C5:
			state = D;
                break;
	}	

	switch(state){
		case init:
			if(!(button & 0x01)){depressed = 0x00;}
			set_PWM(0.0);
		break;

		case C4:
			if(!(button & 0x01)){depressed = 0x00;}
			set_PWM(261.63);
		break;

		case D:
			if(!(button & 0x01)){depressed = 0x00;}
			set_PWM(293.66);
		break;

		case E:
			if(!(button & 0x01)){depressed = 0x00;}
			set_PWM(329.63);
		break;

		case F:
			if(!(button & 0x01)){depressed = 0x00;}
                        set_PWM(349.23);
                break;

                case G:
			if(!(button & 0x01)){depressed = 0x00;}
                        set_PWM(392.00);
                break;

                case A:
			if(!(button & 0x01)){depressed = 0x00;}
                        set_PWM(440.00);
                break;

		case B:
			if(!(button & 0x01)){depressed = 0x00;}
                        set_PWM(493.88);
                break;

                case C5:
			if(!(button & 0x01)){depressed = 0x00;}
                        set_PWM(523.25);
                break;


	}	
}

	


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0x40; PORTB = 0x00;

	DDRA = 0x00; PORTA = 0xFF;
    /* Insert your solution below */
	
	PWM_on();
	while (1) {
		button = ~PINA;
		tone();
	}
    return 1;
}
