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
	unsigned short max = 816;
	unsigned char tempB = 0x00;		
	while(1){
		unsigned short adc_Value = ADC;
		
		if( adc_Value <= 0){
			tempB = 0x80;
		}		
		else if (adc_Value <= max * .125){
			tempB = 0x40;
		}
		else if( adc_Value <= max * .25){
			tempB = 0x20;
		}
		else if( adc_Value <= max * .375){
			tempB = 0x10;
		}
		else if( adc_Value <= max * .50){
			tempB = 0x08;
		}
		else if( adc_Value <= max * .625){
			tempB = 0x04;
		}
		else if( adc_Value <= max * .75){
			tempB = 0x02;
		}
		else if( adc_Value <= max * .875){
			tempB = 0x01;
		}
		else if( adc_Value <= max ){
			tempB = 0x00;
		}


		PORTB = tempB;


	}
	return 0;

}









































