/*	Author: plin012
 *  Partner(s) Name: 
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

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF;
	DDRB = 0xFF;	PORTB = 0x00;
    /* Insert your solution below */
	unsigned char tmpA = 0x00;
	unsigned char tmpB = 0x00;
	unsigned char tmpC = 0x00;
    while (1) {
	
	tmpA = PINA & 0x01;
	tmpC = PINA & 0x02;
	if(tmpA == 0x01 && tmpC == 0x00){
		tmpB = (tmpB & 0xFC) | 0x01;
	}
	else{
		tmpB = (tmpB & 0xFC) | 0x00;
	}
	PORTB = tmpB;	



    }
    return 1;
}
