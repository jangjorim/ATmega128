#include <avr/io.h>
#include <util/delay.h>
unsigned char digit[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
unsigned char latch[4] = { 0x01, 0x02, 0x04, 0x08};

int main(){
	int i;

	DDRD = 0xff;
	DDRE = 0x0f;

	while (1){
		for(i = 0; i< 4; i++)
			PORTE = latch[i], PORTD = digit[4-i], _delay_ms(5);
	}
}
