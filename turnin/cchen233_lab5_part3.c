/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum states { start, WAITRISE, INC, WAITFALL} state;

unsigned char cnt;
unsigned char tmpA;
unsigned char tmpD;

void tick()
{
	tmpA = (~PINA) & 0x01;
	switch(state){
		case start:
			state = WAITRISE;
			break;
		case WAITRISE:
			if(tmpA == 0)
				state = WAITRISE;
			else if(tmpA == 1)
				state = INC;
			break;
		case INC:
			state = WAITFALL;
			break;
		case WAITFALL:
			if(tmpA == 1)
				state = WAITFALL;
			else if(tmpA == 0)
				state = WAITRISE;
			break;
		default:
			state = start;
			break;
		
	}
	//state actions
	switch(state){
		case start:
			// cnt = 0x07;
			break;
		case WAITRISE:
			break;
		case WAITFALL:
			break;
		case INC:
			if(cnt < 0x0E) cnt = cnt + 1;
			else cnt = 0;
			break;
		default:
			break;
		
	}
	switch(cnt){
		case 0: tmpD = 0; break;
		case 1: tmpD = 0x01; break;
		case 2: tmpD = 0x03; break;
		case 3: tmpD = 0x07; break;
		case 4: tmpD = 0x0F; break;
		case 5: tmpD = 0x1F; break;
		case 6: tmpD = 0x3F; break;
		case 7: tmpD = 0x00; break;
		case 8: tmpD = 0x20; break;
		case 9: tmpD = 0x30; break;
		case 10: tmpD = 0x38; break;
		case 11: tmpD = 0x3C; break;
		case 12: tmpD = 0x3E; break;
		case 13: tmpD = 0x3F; break;
		default: tmpD = 0x00; break;
	}
	PORTD = tmpD;
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRD = 0xFF; PORTD = 0x00; // Configure port B's 8 pins as inputs
    /* Insert your solution below */
	state = start;   
	cnt = 0x00;
	while (1) {
		tick();
    	}
   	 return 1;
}
