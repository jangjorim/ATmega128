#include <avr/io.h>
#include <util/delay.h>
unsigned char digit[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
unsigned char latch[4] = { 0x01, 0x02, 0x04, 0x08};
long unsigned int count = 0, fnd1, fnd10, fnd100, fnd1000;

int main(){
	DDRD = 0xff;
	DDRE = 0x0f;

	while (1){

		fnd1 = (count/10)%10;
		fnd10 = (count/100) % 10;
		fnd100 = (count/1000) % 10;
		fnd1000 = (count/10000) % 10;
		count++;
		PORTE = latch[0], PORTD = digit[fnd1], _delay_ms(2.5);
		PORTE = latch[1], PORTD = digit[fnd10], _delay_ms(2.5);
		PORTE = latch[2], PORTD = digit[fnd100], _delay_ms(2.5);
		PORTE = latch[3], PORTD = digit[fnd1000], _delay_ms(2.5);
		if (count == 100000) count = 0;

		
	
	}
}
