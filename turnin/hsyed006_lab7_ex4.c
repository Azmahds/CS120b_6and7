/*	Author: Hamza Syed
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 7  Exercise 4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 * 
 * Demo Link: https://drive.google.com/file/d/1i60sgko2lKLvuaipUkOddGt0uKwN3mVr/view?usp=sharing
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
//#include "timer.h"
#endif

void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

enum states {init, off, bank1, bank2, bank3, bank4, bank5, bank6, bank7, all} state;
unsigned short x;
unsigned char tb = 0x00;
//unsigned char td = 0x00;
unsigned short thresh = 250/8;

void Light(){
	x = ADC;

	switch(state){
		case init:
			if(x < thresh){state = off;}
			else if ( x > thresh && x < thresh*2){state = bank1;}
			else if ( x > thresh*2 && x < thresh*3){state = bank2;}
			else if ( x > thresh*3 && x < thresh*4){state = bank3;}
			else if ( x > thresh*4 && x < thresh*5){state = bank4;}
			else if ( x > thresh*5 && x < thresh*6){state = bank5;}
			else if ( x > thresh*6 && x < thresh*7){state = bank6;}
			else if ( x > thresh*7 && x < thresh*8){state = bank7;}
			else if (x > thresh*8){state = all;}
		break;

		case off:
			if(x > thresh){
				state = init;
			}
			else{state = off;}
		break;

		case bank1:
			if(!(x >= thresh && x < thresh*2)){
				state = init;
			}
			else{state = bank1;}
		break;

		case bank2:
			if(!( x >= thresh*2 && x < thresh*3)){
				state = init;
			}
			else{state = bank2;}

		break;		

		case bank3:
			if(!( x >= thresh*3 && x < thresh*4)){
				state = init;
			}
			else{state = bank3;}

		break;	

		case bank4:
			if(!( x >= thresh*4 && x < thresh*5)){
				state = init;
			}
			else{state = bank4;}

		break;

		case bank5:
			if(!( x >= thresh*5 && x < thresh*6)){
				state = init;
			}
			else{state = bank5;}

		break;	

		case bank6:
			if(!( x >= thresh*6 && x < thresh*7)){
				state = init;
			}
			else{state = bank6;}

		break;	

		case bank7:
			if(!( x >= thresh*7 && x < thresh*8)){
				state = init;
			}
			else{state = bank7;}

		break;	

		case all:
			if(!(x >= thresh*8 )){
				state = init;
			}
			else{state = all;}

		break;	
	}

	switch(state){
		case off:
			tb = 0;
		break;

		case bank1:
			tb = 0x01;
		break;

		case bank2:
			tb = 0x03;
		break;		

		case bank3:
			tb = 0x07;
		break;	

		case bank4:
			tb = 0x0F;
		break;

		case bank5:
			tb = 0x1F;
		break;	

		case bank6:
			tb = 0x3F;
		break;	

		case bank7:
			tb = 0x7F;
		break;	

		case all:
			tb = 0xFF;
		break;
		
		default:
			tb = 0;
		break;	
	}
	PORTB = tb;
}



int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

	DDRA = 0x00; PORTA = 0xFF;
    /* Insert your solution below */
	
	ADC_init();
	state = init;
	while (1) {
		Light();
	}
    return 1;
}
