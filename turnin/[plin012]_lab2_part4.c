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
#include <stdlib.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF;
	DDRB = 0x00;	PORTB = 0x00;
	DDRC = 0x00; 	PORTC = 0x00;
	DDRD = 0xFF;	PORTD = 0x00;
    /* Insert your solution below */
	unsigned char A  = 0x00;
	unsigned char B  = 0x00;
	unsigned char C  = 0x00;
	unsigned char D  = 0x00;
	unsigned char totalWeight = 0x00;
    while (1) {
	
	A = PINA;
	B = PINB;
	C = PINC;
	totalWeight = A + B + C;
	D = 0x00;

	if(A + B + C >= 140){
		D = D | 0x01;
	}
	if(abs(A-C)>80){
		D = D |0x02;
	}

	totalWeight = totalWeight & 0xFC;

	D = totalWeight + D;

	PORTD = D;




    }
    return 1;
}
