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
unsigned char tempA = 0x00;
enum States{init, wait1, light1,wait2, light2,wait3, light3}state;

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
			if(tempA){
				state = wait1;
			}
			else{
				state = light2;
			}
			break;
		case wait1:
			if(tempA){
				state = light1;
			}
			else{
				state = wait1;
			}
			break;
		case light2:
			if(tempA){
				state = wait2;
			}
			else{
				state = light3;
			}
			break;
		case wait2:
			if(tempA){
				state = light2;
			}
			else{
				state = wait2;
			}
			break;
		case light3:
			if(tempA){
				state = wait3;
			}
			else{
				state = light1;
			}
			break;
		case wait3:
			if(tempA){
				state = light3;
			}
			else{
				state = wait3;
			}
			break;
	}	
	switch(state){
		case init:
			break;
		case light1:
			tempB = 0x01;
			break;
		case wait1:
			tempB = 0x01;
			break;
		case light2:
			tempB = 0x02;
			break;
		case wait2:
			tempB = 0x02;
			break;
		case light3:
			tempB = 0x04;
			break;
		case wait3:
			tempB = 0x04;
			break;
	}
				
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF; //set port A as 8 bits input
	DDRB = 0xFF;	PORTB = 0x00; //set port B as 8 bits output
	//DDRC = 0xFF;	PORTC = 0x00; //set port C as 8 bits output
	state = init;
	TimerSet(300);
	TimerOn();
    while (1) {
	tempA = ~PINA & 0x01;
	light_state();
	while(!TimerFlag); // wait 1 sec
	TimerFlag = 0;
	PORTB = tempB;
		
    }
    return 1;
}
