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
#include "timer.h"

enum threeLEDS{init, one, two, zero} threeled;
enum blinkingLEDS{start, z, three} blinkled;
enum combineLED{synch} combine;

enum speakers {begin, on} speaker;

unsigned char tLED = 0x00;
unsigned char bLED = 0x00;
unsigned char comb = 0x00;
unsigned char speak = 0x00;

void threeLEDsSM(){

	switch(threeled){
		case init:
			threeled = zero;
		break;

		case zero:
			threeled = one;
		break;

		case one:
			threeled = two;
		break;

		case two:
			threeled = zero;
		break;
	}
	switch(threeled){
		case init:
			tLED = 0x00;
		break;

		case zero:
			tLED = 0x01;
		break;

		case one:
			tLED = 0x02;
		break;

		case two:
			tLED = 0x04;
		break;
	}

}

void BlinkLEDSM(){

	switch(blinkled){
		case start:
			blinkled = three;
		break;

		case z:
			blinkled = three;
		break;

		case three:
			blinkled = z;
		break;
	}
	switch(blinkled){
		case start:
			bLED = 0x00;
		break;

		case z:
			bLED = 0x00;
		break;

		case three:
			bLED = 0x08;
		break;
	}

}

void combineLEDSM(){
	switch(combine){
		case synch:
			comb = bLED | tLED | speak;
		break;
	}
	
	PORTB = comb;
}

void Speaker(){
	unsigned char temp = ~PINA;
	switch(speaker){
		case begin:
			if(temp == 0x04){speaker = on;}
			else{speaker = begin;}
		break;

		case on:
			speaker = begin;
		break;
	}
	switch(speaker){
		case begin:
			speak = 0x00;
		break;
		case on:
			speak = 0x10;
		break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
    /* Insert your solution below */
	blinkled = start;
	threeled = init;
	combine = synch;
	speaker = begin;
	int tTime = 100;
	int bTime = 300;
	int sTime = 2;
	TimerSet(1);
	TimerOn();
    while (1) {
	
	if(tTime >= 100){
		threeLEDsSM();
		combineLEDSM();
		tTime = 0;
	}

	if(bTime >= 300){
		BlinkLEDSM();
		combineLEDSM();
		bTime = 0;
	}

	if(sTime >= 2){
		Speaker();
		combineLEDSM();
		sTime = 0;
	}

	while(!TimerFlag){}
	TimerFlag = 0;
	tTime += 1;
	bTime += 1;
	sTime += 1;
    }
    return 1;
}
