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
	DDRB = 0x00;	PORTB = 0xFF; //set port B as 8 bits input
	DDRC = 0xFF;	PORTC = 0x00; //set port C as 8 bits output
    /* Insert your solution below */
	unsigned char tempC = 0x00; //initial c as 0
	//unsigned char count = 0x00;
    while (1) {
	unsigned char count = 0x00;
	unsigned char iter; // iterator for the for loop
	for(iter = 0; iter < 8; iter++){
		//for portA
		tempC = PINA;
		if(GetBit(tempC,iter)){
			count++;	
		}
		//for portB
		tempC = PINB;
		if(GetBit(tempC,iter)){
			count++;
		}	
	}
	PORTC = count;
	
    }
    return 1;
}
