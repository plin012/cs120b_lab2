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

unsigned char GetBit(unsigned char bitString, unsigned char index){
	return ((bitString & (0x01 << index)) != 0);
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF; //set port A as 8 bits input
	//DDRB = 0x00;	PORTB = 0xFF; //set port B as 8 bits input
	DDRB = 0xFF;	PORTB = 0x00; //set port B as 8 bits output
    /* Insert your solution below */
	unsigned char tempC = 0x00; //initial c as 0
	unsigned char tempB = 0x00;
	//unsigned char count = 0x00;
    while (1) {
	tempC = PINA;
	if (tempC == 0){
		tempB = 0x00;
	}
	else if(tempC == 1 || tempC == 2){
		tempB =  0x20;
	}
	else if (tempC == 3 || tempC == 4){
		tempB = 0x30;
	}
	else if (tempC == 5 || tempC == 6){
		tempB = 0x38;
	}
	else if (tempC == 7 || tempC == 8 || tempC == 9){
		tempB = 0x3C;
	}
	else if (tempC == 10 || tempC == 11 || tempC ==12){
		tempB = 0x3E;
	}
	else if (tempC == 13 || tempC == 14 || tempC == 15){
		tempB = 0x3F;
	}
	
	if(tempC <= 4){
		tempB = (tempB | 0x40);
	}
	PORTB = tempB;
    }
    return 1;
}
