#include <avr/io.h>
#include <util/delay.h>

int main(){
	
	DDRA = 0xff;


	while(1){
		PORTA = 0x00;
		_delay_ms(1000);
		PORTA = 0xff;
		_delay_ms(1000);
	}

}


