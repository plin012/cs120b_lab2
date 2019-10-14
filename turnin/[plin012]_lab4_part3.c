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

enum States{lock, wait, release, unlock} state;

unsigned char buttonX;
unsigned char buttonY;
unsigned char buttonP;
unsigned char buttonLock;

unsigned char tempB;
unsigned char tempC;

void lock_state(){
	buttonX = PINA & 0x01;
	buttonY = PINA & 0x02;
	buttonP = PINA & 0x04;
	buttonLock = PINA & 0x80;

	switch(state){
		case lock:
			if(buttonLock){
				state = lock;
			}
			if(!buttonX && !buttonY && buttonP && !buttonLock){
				state = wait;
			}
			else{
				state = lock;
			}
			break;
		case wait:
			if(!buttonX && !buttonY && buttonP && !buttonLock){
				state = wait;
			}
			else if(!buttonX && !buttonY && !buttonP && !buttonLock){
				state = release;
			}
			else{
				state = lock;
			}
			break;
		case release:
			if(!buttonX && !buttonY && !buttonP && !buttonLock){
				state = release;
			}
			else if(!buttonX && buttonY && !buttonP && !buttonLock){
				state = unlock;
			}
			else{
				state = lock;
			}
			break;
		case unlock:
			if(!buttonX && !buttonY && !buttonP && buttonLock){
				state = lock;
			}
			else{
				state = unlock;
			}
			break;
			
			
	}
	switch(state){
		case lock:
			tempB = 0x00;
			tempC = 0x00;
			break;
		case wait:
			tempC = 0x01;
			break;
		case release:
			tempC = 0x02;
			break;
		case unlock:
			tempB = 0x01;
			tempC = 0x03;
			break;
		
		}
				
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF; //set port A as 8 bits input
	DDRB = 0xFF;	PORTB = 0x00; //set port B as 8 bits output
	DDRC = 0xFF;	PORTC = 0x00; //set port C as 8 bits output
	state = lock;
    while (1) {
	lock_state();
	PORTB = tempB;
	PORTC = tempC;
		
    }
    return 1;
}
