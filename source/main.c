/*	Author: plin012
 *	Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <stdlib.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{init, inc, dec, zero, wait, wait2} state;

unsigned char buttonInc;
unsigned char buttonDec;

unsigned char tempC;

void number_state(){
	buttonInc = PINA & 0x01;
	buttonDec = PINA & 0x02;

	switch(state){
		case init:
			if(!buttonInc && !buttonDec){
				state = init;
			}
			else if(buttonInc && !buttonDec){
				state = inc;
			}
			else if (!buttonInc && buttonDec){
				state = dec;
			}
			else if (buttonInc && buttonDec)[
				state = zero;
			}
			break;
		case inc:
			if(buttonInc && buttonDec){
				state = zero;
			}
			else{
				state = wait2;
			}
			break;
		case dec:
			if(buttonInc && buttonDec){
				state = zero;
			}
			else{
				state = wait2;
			}
			break;
		case zero:
			if(!buttonInc && !buttonDec)[
				
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF; //set port A as 8 bits input
	DDRC = 0xFF;	PORTC = 0x00; //set port B as 8 bits output
	//DDRC = 0xFF;	PORTB = 0x00; //set port C as 8 bits output
	state = init;
	tempC = 0x07;
    while (1) {
	number_state();
	PORTC = tempC;
		
    }
    return 1;
}
