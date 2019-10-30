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
#include <avr/interrupt.h>
#include "io.h"

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
unsigned char tempA = 0x00;
unsigned char tempC = 0x00;
unsigned char records = 0x00;



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

enum States {on1, chill1, on2, chill2, on3, chill3} state;

void lcd_state(){
	
	switch(state){
		case on1:
			if(tempC){
				state = chill1;
				if(records > 0){
					records = records -1;
				}
			}
			else{
				state = on2;
			}
			break;
		case chill1:
			if(tempC){
				state = on1;
			}
			else{
				state = chill1;
			}
		case on2:
			if(tempC){
				state = chill2;
				if(score < 9){
					records = records + 1;
				}
			}
			else{
				state = on3;
			}
			break;
		case chill2:
			if(tempC){
				state = on2;
			}
			else{
				state = chill2;
			}
			break;
		case on3:
			if(tempC){
				state = chill3;
				if(score > 0){
					records = records -1;
				}
			}
			else{
				state = on1;
			}
			break;
		case chill3:
			if(tempC){
				state = on3;
			}
			else{
				state = chill3;
			}
			break;
	}
	switch(state){
		case on1:
			tempA = 0x01;
			break;
		case chill1:
			tempA = 0x01;
			break;
		case on2:
			tempA = 0x02;
			break;
		case chill2:
			tempA = 0x02;
			break;
		case on3:
			tempA = 0x04;
			break;
		case chill3:
			tempA = 0x04;
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

	records = 0x05;
	state = light1;

	while(1){
		LCD_Cursor(1);
		if(records == 9){
			LCD_DisplayString(1, "You Win!!");
		}
		else{
			LCD_WriteData(records + '0');
		}
		tempC = ~PINA & 0x01;

		lcd_state();

		while(!TimerFlag){}
		TimerFlag = 0;

		PORTB = tempA;
	}
	return 0;

}









































