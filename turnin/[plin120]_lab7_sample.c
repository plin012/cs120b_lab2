/*	Author: plin012
 *	Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #6  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#incllude <avr/interrupt.h>
#include "io.h"

int main(void) {
    /* Insert DDR and PORT initializations */
	//DDRC = 0x00;	PORTA = 0xFF; //set port A as 8 bits input
	DDRD = 0xFF;	PORTD = 0x00; //set port B as 8 bits output
	DDRC = 0xFF;	PORTC = 0x00; //set port C as 8 bits output
		
	LCD_init();

	LCD_DisplayString(1, "Hello World");
	
	while(1) {continue;}
}
