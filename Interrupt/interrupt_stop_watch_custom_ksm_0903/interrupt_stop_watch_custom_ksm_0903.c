#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
unsigned char digit[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
unsigned char latch[4] = { 0x01, 0x02, 0x04, 0x08 };
int run = 0, fnd[4], i;

int main(){
	DDRA = 0xff;
	DDRD = 0xff;
	DDRE = 0x0f;

	SREG = 0x80;	EIMSK = 0x40;	EICRB = 0x30;
	EIMSK = 0xf0;
	EICRB = 0xaa;
	
	PORTA = 0xff;

	while (1){
		
		if(run == 1) fnd[0]++;

		if(fnd[0] == 10) fnd[0]=0, fnd[1]++;
		if(fnd[1] == 6) fnd[1]=0, fnd[2]++;
		if(fnd[2] == 10) fnd[2]=0, fnd[3]++;
		if(fnd[3] == 6) fnd[3]=0;

		for(i = 0 ; i < 10; i++){
			PORTE = latch[0], PORTD = digit[fnd[0]], _delay_ms(2.5);
			PORTE = latch[1], PORTD = digit[fnd[1]], _delay_ms(2.5);
			PORTE = latch[2], PORTD = digit[fnd[2]]&0x7f, _delay_ms(2.5);
			PORTE = latch[3], PORTD = digit[fnd[3]], _delay_ms(2.5);
		}	
	}
}


ISR(INT4_vect){
	fnd[2] = fnd[2] + 1;
}

ISR(INT5_vect){
	fnd[3] = fnd[3] + 1;
}

ISR(INT6_vect){
	run = (run+1)%2;
	PORTA = ~PORTA;
}

ISR(INT7_vect){
	fnd[0] = 0, fnd[1] = 0,fnd[2] = 0, fnd[3] = 0 , run=0;
	PORTA = 0xff;
}
