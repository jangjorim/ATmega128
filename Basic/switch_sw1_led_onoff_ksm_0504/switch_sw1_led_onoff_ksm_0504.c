#include <avr/io.h>


int main(){
	DDRA = 0xff;
	DDRE = 0x0f;

	while(1){
		if((PINE & 0x40) == 0)
			PORTA = 0x00;

		else 
			PORTA = 0xff;
	}
	return 0;
}
