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
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn(){
    TCCR1B = 0x0B;

    OCR1A = 125;

    TIMSK1 = 0X02;

    TCNT1 = 0;

    _avr_timer_cntcurr = _avr_timer_M;

    SREG |= 0x80;
}

void TimerOff(){
    TCCR1B = 0x00;
}

void TimerISR(){
    TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect){
    _avr_timer_cntcurr--;
    if(_avr_timer_cntcurr == 0){
        TimerISR();
        _avr_timer_cntcurr = _avr_timer_M;
    }
}

void TimerSet(unsigned long M){
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}


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


enum states {C4, D, E, F, G, A, B, C5} state;
enum starts {off, on, waitOn, waitOff} start;
unsigned char button = 0x00;
unsigned char trueornah = 0x01;
unsigned char test = 0x00;

void theSitch(){
	test = button & 0x01;
	switch(start){
		case off:
			if(test == 0x01){state = off;}
			else{state = waitOff;}	
		break;

		case on:
			if(test == 0x01){state = on;}
                        else{state = waitOn;}
		break;
		
		case waitOn:
			if(test == 0x01){state = off;}
                        else{state = waitOn;}
		break;
		
		case waitOff:
			if(test == 0x01){state = on;}
                        else{state = waitOff;}
		break;
	}
	switch(start){
		case off:
           		set_PWM(0);
                break;
                case on:
                break;		
		case waitOn:
		break;	
		case waitOff:
		break;
		default:
			set_PWM(0);
		break;
	}

}

void tone(){
	switch(state){
		case C4:
			if(!(button & 0x02)){trueornah = 0x01;}
			if(button & 0x02 && trueornah == 0x01){trueornah = 0x00; state = D;}
			else {state = C4;}
		break;

		case D:
			if(!(button & 0x02) && !(button & 0x04)){trueornah = 0x01;}
			if(button & 0x02 && trueornah == 0x01){trueornah = 0x00; state = E;}
			else if(button & 0x04 && trueornah == 0x01){trueornah = 0x00; state = C4;}
			else {state = D;}

		break;
			
		case E:
			if(!(button & 0x02) && !(button & 0x04)){trueornah = 0x01;}
			if(button & 0x02 && trueornah == 0x01){trueornah = 0x00; state = F;}
			else if(button & 0x04 && trueornah == 0x01){trueornah = 0x00; state = D;}
			else {state = E;}
		break;
			
		case F:
			if(!(button & 0x02) && !(button & 0x04)){trueornah = 0x01;}
			if(button & 0x02 && trueornah == 0x01){trueornah = 0x00; state = G;}
                        else if(button & 0x04 && trueornah == 0x01){trueornah = 0x00; state = E;}
                        else {state = F;}
                break;
			
                case G:
			if(!(button & 0x02) && !(button & 0x04)){trueornah = 0x01;}
			if(button & 0x02 && trueornah == 0x01){trueornah = 0x00; state = A;}
                        else if(button & 0x04 && trueornah == 0x01){trueornah = 0x00; state = F;}
                        else {state = G;}
		break;
			
                case A:
			if(!(button & 0x02) && !(button & 0x04)){trueornah = 0x01;}
        		if(button & 0x02 && trueornah == 0x01){trueornah = 0x00; state = B;}
                        else if(button & 0x04 && trueornah == 0x01){trueornah = 0x00; state = G;}
                        else {state = A;}
                break;
			
                case B:
			if(!(button & 0x02) && !(button & 0x04)){trueornah = 0x01;}
                	if(button & 0x02 && trueornah == 0x01){trueornah = 0x00; state = C5;}
                        else if(button & 0x04 && trueornah == 0x01){trueornah = 0x00; state = A;}
                        else {state = B;}
                break;
			
                case C5:
			if(!(button & 0x04)){trueornah = 0x01;}
                        if(button & 0x04 && trueornah == 0x01){trueornah = 0x00; state = B;}
                        else {state = C5;}
                break;
	}	

	switch(state){
		case C4:
			set_PWM(261.63);
		break;

		case D:
			set_PWM(293.66);
		break;

		case E:
			set_PWM(329.63);
		break;

		case F:
                        set_PWM(349.23);
                break;

                case G:
                        set_PWM(392.00);
                break;

                case A:
                        set_PWM(440.00);
                break;

		case B:
                        set_PWM(493.88);
                break;

                case C5:
                        set_PWM(523.25);
                break;


	}	
}

	


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0x40; PORTB = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
    /* Insert your solution below */
	
	state = C4;
	start = on;
	PWM_on();
	TimerSet(50);
	TimerOn();
	while (1) {
		button = ~PINA;
		//theSitch();
		if(start == off || start == waitOff){}
		else{tone();}
		while(!TimerFlag);
		TimerFlag = 0;
	}
    return 1;
}
