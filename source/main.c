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

void set_PWM(double frequency){
	static double current_frequency;
	if(frequency != current_frequency){
		if(!frequency){TCCR3B &= 0x08;}
		else{TCCR0B |= 0x03;}
		if(frequency < 0.954){OCR3A = 0xFFFF;}
		
		else if(frequency > 31250){ OCR3A = 0x0000;}
		else{OCR3A = (short)(8000000/(128*frequency))-1;}
		TCNT3 = 0;
		current_frequency  = frequency;
	}
}

void PWM_on(){
	TCCR3A = (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	set_PWM(0);
}

void PWM_off(){
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

enum States{off, tOff, on, cOn, up, wUp, down, wDown}state;

unsigned char buttonP = 0x00;

const double notes[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};

unsigned char i = 0x04;

void sound_state(){
	buttonP = ~PINA & 0x07;
	switch(state){
		case off:
			if(buttonP == 0x01){
				state = on;
			}
			else{ 
				state = off;
			}
			break;
		case tOff:
			if(buttonP == 0x01){
				state = tOff;
			}
			else{
				state = off;
			}		
		case on:
			if(buttonP == 0x01){
				state = on;
			}
			else{
				state = cOn;
			}
			break;
		case cOn:
			if(buttonP == 0x02){
				if(i>0){
					i--;
				}
				state = down;
				
			}
			else if(buttonP == 0x04){
				if(i<7){
					i++;
				}
				state = up;
			}
			else if(buttonP == 0x01){
				state = tOff;
			}
			else{
				state = cOn;
			}
			break;
		case up:
			state = wUp;
			break;
		case wUp:
			if(buttonP == 0x02)
				state = wUp;
			else
				state = cOn;
			break;
		case down:
			state = wDown;
			break;
		case wDown:
			if(buttonP == 0x04)
				state = wDown;
			else 
				state = cOn;
			break;
		}
	switch(state){
		case off:
			PWM_off();
			PORTB = 0x00;
			break;
		case tOff:
			break;
		case on:
			PWM_on();
			break;
		case cOn:
			PORTB = 0x01;
			break;
		case up:
			set_PWM(notes[i]);
			break;
		case wUp:
			break;
		case down:
			set_PWM(notes[i]);
		case wDown:
			break;
	}
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF; //set port A as 8 bits input
       	//DDRD = 0xFF;	PORTD = 0x00; //set port B as 8 bits output
	DDRB = 0xFF;	PORTB = 0x00; //set port C as 8 bits output
	
	PWM_on();
	state = off;

	while(1){
		sound_state();
		
	}
	return 0;

}









































