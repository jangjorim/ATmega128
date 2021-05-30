#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char digit[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
int run = 0, count = 0;

int main(){
	DDRA = 0xff;
	DDRD = 0xff;
	DDRE = 0x0f;

	SREG = 0x80;	EIMSK = 0x40;	EICRB = 0x30;
	EIMSK = 0xC0;
	EICRB = 0xa0;
	
	PORTA = 0xff;
	PORTE = 0x01, PORTD = digit[count];
	while(1){
		if(run == 1) count++;
		if(count >=10) count = 0;
		PORTD = digit[count];
		_delay_ms(100);
	}
}

ISR(INT6_vect){
	run = (run+1)%2;
	PORTA = ~PORTA;
}

ISR(INT7_vect){
	count=0, run=0;
	PORTA = 0xff;
}
