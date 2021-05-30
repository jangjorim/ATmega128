#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
unsigned char digit[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
unsigned char latch[4] = { 0x01, 0x02, 0x04, 0x08 };
long count = 99500,i, run = 0, fnd1, fnd10, fnd100, fnd1000;

int main(){
	DDRA = 0xff;
	DDRD = 0xff;
	DDRE = 0x0f;

	SREG = 0x80;
	EIMSK = 0xC0;
	EICRB = 0xa0;
	
	PORTA = 0xff;

	while (1){
		
		if(run == 1) count++;
		if (count >= 100000) count = 0;
		fnd1 = (count/10)%10;
		fnd10 = (count/100) % 10;
		fnd100 = (count/1000) % 10;
		fnd1000 = (count/10000) % 10;
		
		PORTE = latch[0], PORTD = digit[fnd1], _delay_ms(2.5);
		PORTE = latch[1], PORTD = digit[fnd10], _delay_ms(2.5);
		PORTE = latch[2], PORTD = digit[fnd100]&0x7f, _delay_ms(2.5);
		PORTE = latch[3], PORTD = digit[fnd1000], _delay_ms(2.5);

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
