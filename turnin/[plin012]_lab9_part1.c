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
		if(!frequency){TCCR0B &= 0x08;}
		else{TCCR0B |= 0x03;}
		if(frequency < 0.954){OCR0A = 0xFFFF;}
		
		else if(frequency > 31250){ OCR0A = 0x0000;}
		else{OCR0A = (short)(8000000/(128*frequency))-1;}
		TCNT0 = 0;
		current_frequency  = frequency;
	}
}

void PWM_on(){
	TCCR0A = (1 << COM0A0 | 1 << WGM00);
	TCCR0B = (1 << COM0A2) | (1 << CS01) | (1 << CS00);
	set_PWM(0);
}

void PWM_off(){
	TCCR0A = 0x00;
	TCCR0B = 0x00;
}

enum States{wait, cNote, dNote, eNote} state;

unsigned char buttonP = 0x00;

void sound_state(){
	buttonP = ~PINA & 0x07;
	switch(state){
		case wait:
			if(buttonP == 1){
				state = cNote;
			}
			else if(buttonP == 2){
				state = dNote;
			}
			else if(buttonP == 4){
				state = eNote;
			}
			else{
				state = wait;
			}
			break;
		case cNote:
			if(buttonP == 1){
				state = cNote;
			}
			else{
				state = wait;
			}
			break;
		case dNote:
			if(buttonP == 2){
				state = dNote;
			}
			else{
				state = wait;
			}
			break;
		case eNote:
			if(buttonP == 4){
				state = eNote;
			}
			else{
				state = wait;
			}
			break;
	}
	switch(state){
		case wait:
			set_PWM(0);
			break;
		case cNote:
			set_PWM(261.63);
			break;
		case dNote:
			set_PWM(293.66);
			break;
		case eNote:
			set_PWM(329.63);
			break;
		
				

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF; //set port A as 8 bits input
       	//DDRD = 0xFF;	PORTD = 0x00; //set port B as 8 bits output
	DDRB = 0xFF;	PORTB = 0x00; //set port C as 8 bits output
	
	PWM_on();
	state = wait;

	while(1){
		sound_state();
		
	}
	return 0;

}









































