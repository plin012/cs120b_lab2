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
#include <stdlib.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
volatile unsigned char TimerFlag = 0;

//Internl vairables for mapping AVR's ISR to our cleaner TimerISR model
unsigned long _avr_timer_M = 1; // start count down to 1, default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // current internal count of 1ms ticks
unsigned char tempB = 0x00;

enum States{init, light1, light2, light3}state;

void TimerOn(){
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;	

}

void TimerOff(){
	TCCR1B = 0x00;
}

void TimerISR(){
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect){
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr == 0){
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M){
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void light_state(){
	switch(state){
		case init:
			state = light1;
			break;
		case light1:
			state = light2;
			break;
		case light2:
			state = light3;
			break;
		case light3:
			state = light1;
			break;
	}	
	switch(state){
		case init:
			break;
		case light1:
			tempB = 0x01;
			break;
		case light2:
			tempB = 0x02;
			break;
		case light3:
			tempB = 0x04;
			break;
	}
				
}

int main(void) {
    /* Insert DDR and PORT initializations */
	//DDRA = 0x00;	PORTA = 0xFF; //set port A as 8 bits input
	DDRB = 0xFF;	PORTB = 0x00; //set port B as 8 bits output
	//DDRC = 0xFF;	PORTC = 0x00; //set port C as 8 bits output
	state = init;
	TimerSet(1000);
	TimerOn90;
    while (1) {
	light_state();
	while(!TimerFlag); // wait 1 sec
	TimerFlag = 0;
	PORTB = tempB;
		
    }
    return 1;
}
