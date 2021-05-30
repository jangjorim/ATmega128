#include <avr/io.h>
#include <util/delay.h>
unsigned char digit[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
unsigned char latch[4] = { 0x01, 0x02, 0x04, 0x08};


int i, fnd[4];

int main(){
	DDRD = 0xff;
	DDRE = 0x0f;

	while(1){
		for(i = 0; i < 100; i++){
			PORTE = latch[0], PORTD = digit[fnd[0]], _delay_ms(2.5);
			PORTE = latch[1], PORTD = digit[fnd[1]], _delay_ms(2.5);
			PORTE = latch[2], PORTD = digit[fnd[2]]&0x7f, _delay_ms(2.5);
			PORTE = latch[3], PORTD = digit[fnd[3]], _delay_ms(2.5);
		}
		fnd[0]++;
		if(fnd[0] == 10) fnd[0]=0, fnd[1]++;
		if(fnd[1] == 6) fnd[1]=0, fnd[2]++;
		if(fnd[2] == 10) fnd[2]=0, fnd[3]++;
		if(fnd[3] == 6) fnd[3]=0;
	}
}



/*
int i, M10, M1, S10, S1, Min =0, Sec = 0;
int main(void)
{
  DDRD = 0xff;
  DDRE = 0x0f;
  while (1)
  {
	  for( i =0 ; i<100; i++) 
	  {
		  PORTE=latch[0], PORTD=digit[S1], _delay_ms(2.5);
		  PORTE=latch[1], PORTD=digit[S10], _delay_ms(2.5);
		  PORTE=latch[2], PORTD=digit[M1]&0x7f, _delay_ms(2.5);
		  PORTE=latch[3], PORTD=digit[M10], _delay_ms(2.5);
	  }
	  M10 = Min/10, M1 = Min%10, S10 = Sec/10, S1 = Sec++%10;
	  if(Sec == 60)
	  {
		  Sec = 0, Min++;
		  if(Min == 60)Min = 0;
	  }
  }
}
*/
