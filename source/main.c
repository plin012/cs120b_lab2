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

enum States{init, wait, next,buttonPress}state;

unsigned char tempA = 0x00;
unsigned char tempB = 0x00;
unsigned char nextIndex = 0x00;
unsigned char prevIndex = 0x00;


unsigned char lightIndex(unsigned char currentIndex){
	//unsigned char nextIndex = 0x00;
	//unsigned char prevIndex = 0x00;
	switch(currentIndex){
		case 0x00:
			if(prevIndex == 0x00){
				nextIndex = 0x01;
				prevIndex = 0x00;
				break;
			}
			else{
				nextIndex = 0x20;
				prevIndex = 0x00;
				break;
			}
		case 0x01:
			nextIndex = 0x03;
			prevIndex = 0x01;
			break;
		case 0x03:
			nextIndex = 0x07;
			prevIndex = 0x03;
			break;
		case 0x07:
			nextIndex = 0x0F;
			prevIndex = 0x07;
			break;
		case 0x0F:
			nextIndex = 0x1F;
			prevIndex = 0x0F;
			break;
		case 0x1F:
			nextIndex = 0x3F;
			prevIndex = 0x1F;
			break;
		case 0x3F:
			if(prevIndex != 0x3C){
				nextIndex = 0x00;
				prevIndex = 0x3F;
				break;
			}
			else{
				nextIndex = 0x00;
				prevIndex = 0x00;
				break;
			}
		case 0x20:
			nextIndex = 0x30;
			prevIndex = 0x20;	
			break;
		case 0x30:
			nextIndex = 0x38;
			prevIndex = 0x30;
			break;
		case 0x38:
			nextIndex = 0x3C;
			prevIndex = 0x38;
			break;
		case 0x3C:
			nextIndex = 0x3E;
			prevIndex = 0x3C;
			break;
		case 0x3E:
			nextIndex = 0x3F;
			prevIndex = 0x3E;
			break;
	}
	return nextIndex;
}

void light_state(){
	tempA = ~PINA & 0x01;
	switch(state){
		case init:
			state = wait;
			tempB = 0x00;
			nextIndex = 0x00;
			prevIndex = 0x00;
			break;
		case wait:
			if(tempA){
				state = next;;
			}
			else{
				state = wait;
			}
			break;
		case next:
			state = buttonPress;
			break;
		case buttonPress:
			if(tempA){
				state = buttonPress;
			}
			else{
				state = wait;
			}
			break;
	}
	switch(state){
		case init:
			break;
		case wait:
			break;
		case next:
			tempB = lightIndex(tempB);
			break;
		case buttonPress:
			break;
	}
				
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF; //set port A as 8 bits input
	DDRB = 0xFF;	PORTB = 0x00; //set port B as 8 bits output
	//DDRC = 0xFF;	PORTC = 0x00; //set port C as 8 bits output
	state = init;
	tempA = 0x00;
	tempB = 0x00;
	prevIndex = 0x00;
	nextIndex = 0x00;
    while (1) {
	light_state();
	PORTB = tempB;
		
    }
    return 1;
}
