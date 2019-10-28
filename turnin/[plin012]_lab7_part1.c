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

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
unsigned char tempA = 0x00;
unsigned char tempC = 0x00;

void TimerOn(){
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0x;
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

enum States {wait, inc, dec, zero} state;

unsigned char button0;;
unsigned char button1;

unsigned char tempC;

void lcd_state(){
	button0 = ~PINA & 0x01;
	button1 = ~PINA & 0x02;
	
	switch(state){
		case zero:
			if(button0 && button1){
				state = zero;
			}
			else{
				state = wait;
			}
			break;
		case wait:
			if(button0 && !button1){
				state = inc;
			}
			else if(!button0 && button1){
				state = dec;
			}
			else if(button0 && button1){
				state = zero;
			}
			else{
				state = wait;
			}
			break;
		case inc:
			if(button0 && !button1){
				state = inc; 
			}
			else if(button0 && button1){
				state = zero;
			}
			else
				state = wait;
			break;
		case dec:
			if(!button0 && button1){
				state = dec;
			}
			else if(button0 && button1){
				state = zero;
			}
			else
				state = wait;
			
			break;
	}
	switch(state){
		case zero:
			tempC = 0;
			break;
		case wait:
			break;
		case inc:
			if(tempC < 9){
				tempC = tempC + 1;
			}
			break;
		case dec:
			if(tempC > 0){
				tempC = tempC - 1;
			}
			break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF; //set port A as 8 bits input
	DDRD = 0xFF;	PORTD = 0x00; //set port B as 8 bits output
	DDRC = 0xFF;	PORTC = 0x00; //set port C as 8 bits output
		
	TimerSet(1000);
	TimerOn();
	
	LCD_init();
	LCD_ClearScreen();
	
	state = wait;
	tempC = 0x00;
	while(1){
		LCD_Cursor(1);
		lcd_state();
		LCD_WriteData(tempC + '0');
		while(!TimerFlag){}
		TimerFlag = 0;

}









































