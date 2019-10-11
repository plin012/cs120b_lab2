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

enum States{init, led2, wait, led1} state;

unsigned char button;
unsigned char tempB;

void led_state(){
	switch(state){
		case init:
			if(button == 1){
				state = led2;
			}
			else{
				state = init;
			}
			break;
		case led2:
			if(button == 1){
				state = led2;
			}
			else{
				state = wait;
			}
			break;
		case wait:
			if(button == 1){
				state = led1;
			}
			else{
				state = init;
			}
			break;
	}
	switch(state){
		case init:
			tempB = 0x01;
			break;
		case led2:
			tempB = 0x02;
			break;
		case wait:
			tempB = 0x02;
			break;
		case led1:
			tempB = 0x01;
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF; //set port A as 8 bits input
	DDRB = 0xFF;	PORTB = 0x00; //set port B as 8 bits output
	//DDRC = 0xFF;	PORTB = 0x00; //set port C as 8 bits output
	state = init;
    while (1) {
	button = PINA & 0x01;
	led_state();
	PORTB = tempB;
		
    }
    return 1;
}
