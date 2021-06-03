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
#endif

enum SM1_STATES {SM1_SMStart, SM1_Wait0, SM1_Wait1, SM1_PB0, SM1_PB1} SM1_STATE;

void LED_Switch();

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; //input
	DDRB = 0xFF; PORTB = 0x00; //output
    /* Insert your solution below */
   
	SM1_STATE = SM1_SMStart;

    while (1) {
	LED_Switch();	
    }
    return 1;
}

void LED_Switch(){
	unsigned char a = 0x00, temp = 0x00;
	a = PINA & 0x01;
	switch(SM1_STATE){
		case SM1_SMStart:
			SM1_STATE = SM1_Wait0;
		break;		

		case SM1_PB0:
			if(/*a*/(PINA & 0x01) == 0x00){
				SM1_STATE = SM1_Wait0;
			}
			else{
                                SM1_STATE = SM1_PB0;
                        }
						
                break;

		case SM1_PB1:
			if(a == 0x00){
                                SM1_STATE = SM1_Wait1;
                        }
			else{
				SM1_STATE = SM1_PB1;
			}
                break;

		case SM1_Wait0:
               		 if((PINA & 0x01) == 0x01){
                                SM1_STATE = SM1_PB1;
                        }
                        else{
                                SM1_STATE = SM1_Wait0;
                        }
		break;

		case SM1_Wait1:
                	if(a  == 0x01){
				SM1_STATE = SM1_PB0;
			}
			else{
				SM1_STATE = SM1_Wait1;
			}
                break;
		
		default:
			SM1_STATE = SM1_SMStart;
			break;
	}

	switch(SM1_STATE){
                case SM1_PB1:
			temp = 0x02;
                break;

                case SM1_PB0:
			temp = 0x01;
                break;
		
		case SM1_Wait0:
                        temp = 0x01;
                break;

		case SM1_Wait1:
                        temp = 0x02;
                break;		
		
		case SM1_SMStart:
			temp = 0x01;
		break;
		default:
			temp  = 0x01;
			break;
        }
	PORTB = temp;
}
