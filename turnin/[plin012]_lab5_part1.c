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

int main(void) {
    /* Insert DDR and PORT initializations */
	//DDRA = 0x00;	PORTA = 0xFF; //set port A as 8 bits input
	DDRB = 0xFF;	PORTB = 0x00; //set port B as 8 bits output
	//DDRC = 0xFF;	PORTB = 0x00; //set port C as 8 bits output

    while (1) {
	PORTB = 0x0F;
		
    }
    return 1;
}
