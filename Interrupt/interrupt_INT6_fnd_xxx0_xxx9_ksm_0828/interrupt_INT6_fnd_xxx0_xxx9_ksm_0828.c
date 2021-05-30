#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
unsigned char digit[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
int count = 0;

int main(){
	DDRD = 0xff;
	DDRE = 0x0f;

	SREG = 0x80;	EIMSK = 0x40;	EICRB = 0x30;
	EIMSK = 0x40;
	EICRB = 0x20;
	
	PORTE = 0x01, PORTD = digit[0];
	while(1);

}

ISR(INT6_vect){
	PORTD=digit[++count];
	if(count>=9) count= -1;
}


