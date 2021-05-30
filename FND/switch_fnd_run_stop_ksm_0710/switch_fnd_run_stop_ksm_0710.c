#include <avr/io.h>
#include <util/delay.h>

unsigned char digit[10] = { 0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
unsigned char latch[4] = {0x01, 0x02, 0x04, 0x08};


int run,  i, k, fnd[4];
int main(void) {
	  DDRD = 0xff;
	  DDRE = 0x0f;
	  while (1) {
		  if(!(PINE & 0x40))   run=1;
		  if(!(PINE & 0x80))   run=0;
		  if(run==1){
			  fnd[0]++;
			  if(fnd[0]==10) fnd[0]=0, fnd[1]++;
			  if(fnd[1]==10) fnd[1]=0, fnd[2]++;
			  if(fnd[2]==10) fnd[2]=0, fnd[3]++;
			  if(fnd[3]==10) fnd[3]=0;
		  }
		  for(k=0;k<10;k++) {
			  for(i=0 ; i<4 ; i++)
			  	PORTE=latch[i], PORTD=digit[fnd[i]], _delay_ms(2.5);
		  }
	  }
}
