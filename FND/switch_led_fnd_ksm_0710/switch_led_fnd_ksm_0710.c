#include <avr/io.h>
#include <util/delay.h>

unsigned char digit[10] = { 0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
int count, shift;

int main(){
	DDRA = 0xff;
	DDRD = 0xff;
	DDRE = 0x0f;

	PORTA = 0xff;
	PORTE = 0x01;
	PORTD = digit[0];
	while(1) {
		if(!(PINE & 0x40)){
			PORTA = ~(0x01 << shift++);
			_delay_ms(50);
			if(shift == 8) shift=0;
			while(!(PINE & 0x40));
		}
		if(!(PINE & 0x80)){
			PORTD = digit[++count];
			_delay_ms(50);
			if(count==9) count = -1;
			while(!(PINE&0x80));
		}
	}
}
