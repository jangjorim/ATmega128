#include <avr/io.h>


int main(){
	
	unsigned char key;
	DDRA = 0xff;
	DDRE = 0x0f;
	PORTA = 0xff;
	
	while(1){

		key = (PINE & 0xc0);

		switch(key){
			case 0x40:
				PORTA = 0xfb;
				break;
			case 0x80:
				PORTA = 0xfd;
				break; 
			case 0x00:
				PORTA = 0xf9;
				break;
			default :
				PORTA = 0xff;
				break;
				
		}
	}
}

/*
int main(){
	DDRA = 0xff;
	DDRE = 0x0f;
	PORTA = 0xff;
	while(1){
		
		if((PINE & 0x40) == 0)
			PORTA = 0xFD;
		else if ((PINE & 0x80) == 0)
			PORTA = 0xFB;
		else if (!(PINE & 0xc0))
			PORTA = 0xF9;
		else 
			PORTA = 0xff;
	}

}

*/
