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
	unsigned char cntavail  = 0;
	unsigned char covered = 0;
	unsigned char space_avail = 4;
    while (1) {
	
	covered = (PINA & 0x01) + ((PINA>>1) & 0x01) + ((PINA >> 2) & 0x01) + ((PINA>>3) & 0x01);
	cntavail = space_avail - covered;

	PORTB = cntavail;

    }
    return 1;
}
