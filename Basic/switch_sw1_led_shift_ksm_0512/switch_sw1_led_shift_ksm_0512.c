#include <avr/io.h>
#include <util/delay.h>

/*

int main(){
	
	unsigned char key;
	int num = 0xfe;
	int count = 0;

	DDRA = 0xff;
	DDRE = 0x0f;
	
	while(1){
		
		key = PINE & 0x80;
		if (count == 8){
			num = 0xfe;
			count = 0;
		}
		switch (key){
			case 0x00:
				PORTA = num;
				num = (num << 1) + 1;
				_delay_ms(500);
				count++;
				break;
			
			default : 
				PORTA = num;
				break;
		}

	}
}*/



int main(){
	
	int shift = 0;

	DDRA = 0xff;
	DDRE = 0x0f;

	PORTA = 0xff;

	while(1){
		if(!(PINE & 0x80)){
			PORTA = ~(0x01 << shift++);
			if (shift == 8) shift = 0;
			_delay_ms(500);
		}

	}

}



