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

volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M =1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn() {
	// AVR timer/counter controller register TCCR1
	TCCR1B = 0x0B;// bit3 = 0: CTC mode (clear timer on compare)
	// bit2bit1bit0=011: pre-scaler /64
	// 00001011: 0x0B
	// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
	// Thus, TCNT1 register will count at 125,000 ticks/s

	// AVR output compare register OCR1A.
	OCR1A = 125;	// Timer interrupt will be generated when TCNT1==OCR1A
	// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
	// So when TCNT1 register equals 125,
	// 1 ms has passed. Thus, we compare to 125.
	// AVR timer interrupt mask register
	TIMSK1 = 0x02; // bit1: OCIE1A -- enables compare match interrupt

	//Initialize avr counter
	TCNT1=0;

	_avr_timer_cntcurr = _avr_timer_M;
	// TimerISR will be called every _avr_timer_cntcurr milliseconds

	//Enable global interrupts
	SREG |= 0x80; // 0x80: 1000000
}

void TimerOff() {
	TCCR1B = 0x00; // bit3bit1bit0=000: timer off
}

void TimerISR() {
	TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect) {
	// CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}



// 0.954 hz is lowest frequency possible with this function,
// based on settings in PWM_on()
// Passing in 0 as the frequency will stop the speaker from generating sound
void set_PWM(double frequency) {
	static double current_frequency; // Keeps track of the currently set frequency
	// Will only update the registers when the frequency changes, otherwise allows
	// music to play uninterrupted.
	if (frequency != current_frequency) {
		if (!frequency) { TCCR0B &= 0x08; } //stops timer/counter
		else { TCCR0B |= 0x03; } // resumes/continues timer/counter
		
		// prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is smallest frequency that will not result in overflow
		if (frequency < 0.954) { OCR0A = 0xFFFF; }
		
		// prevents OCR0A from underflowing, using prescaler 64					// 31250 is largest frequency that will not result in underflow
		else if (frequency > 31250) { OCR0A = 0x0000; }
		
		// set OCR3A based on desired frequency
		else { OCR0A = (short)(8000000 / (128 * frequency)) - 1; }

		TCNT0 = 0; // resets counter
		current_frequency = frequency; // Updates the current frequency
	}
}

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

enum States{off, play}state;

unsigned char buttonP = 0x00;

const double notes[26] = {329.63, 329.63, 329.63, 329.63, 329.63, 329.63, 329.63, 392.00, 261.63, 293.66, 329.63, 349.23, 349.23, 349.23, 349.23, 349.23, 329.63, 329.63, 329.63, 329.63, 329.63, 293.66, 293.66, 329.63, 293.66, 392.00 };
unsigned char i = 0x00;
unsigned char j = 0x00;

void sound_state(){
	buttonP = ~PINA & 0x01;
	switch(state){
		case off:
			if(buttonP){
				state = play;
				i = 0;
				j = 0;
			}
			else
				state = off;
			break;
		case play:
			if(j<2)
				state = play;
			else 
				state = off;
			if(i>25)
				j++;
			i++;
			break;
		}
	switch(state){
		case off:
			set_PWM(0);
			break;
		case play:
			set_PWM(notes[i]);
			set_PWM(0);
			break;
	}
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF; //set port A as 8 bits input
       	//DDRD = 0xFF;	PORTD = 0x00; //set port B as 8 bits output
	DDRB = 0xFF;	PORTB = 0x00; //set port C as 8 bits output
	

	TimerSet(400);
	TimerOn();
	PWM_on();
	state = off;

	while(1){
		sound_state();
		while(!TimerFlag){}
		TimerFlag = 0;
	}
	return 0;

}









































