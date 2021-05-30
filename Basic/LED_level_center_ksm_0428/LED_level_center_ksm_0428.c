#include <avr/io.h>
#include <util/delay.h>


int main (){
	int i, led_R,led_L;
	DDRA = 0xff;
	
	while(1){
		led_R = 0x7f;
		led_L = 0xfe;

		for (i = 0; i < 3; i++){
			PORTA = led_R & led_L;
			_delay_ms(1000);
			led_R = led_R >> 1;
			led_L = led_L << 1;

		}
		for (i = 0; i < 3; i++){
			PORTA = led_R & led_L;
			_delay_ms(1000);
			led_R = led_R << 1;
			led_L = led_L >> 1;
		}

	}

}


