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

void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF; //set port A as 8 bits input
	DDRD = 0xFF;	PORTD = 0x00; //set port B as 8 bits output
	DDRB = 0xFF;	PORTB = 0x00; //set port C as 8 bits output

	ADC_init();		
	while(1){
		unsigned short adc_Value = ADC;
		unsigned char first8 = (char)adc_Value;
		PORTB = first8;
		unsigned char last2 = (char)(adc_Value >> 8);
		PORTD = last2;	


	}
	return 0;

}









































