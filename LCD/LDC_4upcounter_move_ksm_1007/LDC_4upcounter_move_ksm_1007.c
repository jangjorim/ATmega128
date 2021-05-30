#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

long count = 0;

void COMMAND(unsigned char byte)
{
    PORTG = 0xFC;      //PORTG에 RS, RW, E 가 연결되어 있다.
    PORTC = byte;           //PORTC에 데이터버스가 연결되어 있다.
    PORTG ^= 0x04;     //E 신호를 H->L로 하기 위해
    _delay_ms(2);      //LCD 내부 동작시간
}

void DATA(unsigned char byte)
{
    PORTG = 0xFD;        //PORTG에 RS, RW, E 가 연결되어 있다.
    PORTC = byte;      //PORTC에 데이터버스가 연결되어 있다.
    PORTG ^= 0x04;      //E 신호를 H->L로 하기 위해
    _delay_ms(2);       //LCD 내부 동작시간
}

void init_system(void)
{
     DDRC = 0xFF;     //LCD 데이터 버스
     PORTC = 0xFF;
     DDRG = 0xFF;     //LCD 컨트롤 신호(PG2=LCD_EN, PG1=RW, PG0=RS)
     PORTG = 0xFF;
}

void init_LCD(void)
{
       _delay_ms(15);            //15msec 이상 시간지연
       COMMAND(0x38);         //Function set, 기능셋(데이터버스 8비트, 라인수:2줄)
       _delay_ms(5);                //4.1msec 이상 시간지연, 생략가능
       COMMAND(0x38);         //기능셋, 생략 가능
       _delay_us(100);              //100usec 이상 시간지연, 생략가능
       COMMAND(0x38);          //기능셋, 생략 가능
       COMMAND(0x08);          //표시 Off , 생략 가능
       COMMAND(0x01);         //화면 지우기
       COMMAND(0x06);        //엔트리모드셋
       COMMAND(0x0C);         //표시 on
}

void STRING(unsigned char font[], unsigned char n)
{
	 unsigned char i;
	 for(i=0 ; i<n ; i++)
	     {
	          DATA(font[i]);
	     }
}

void MOVE(int y, int x)     //커서 이동
{               
	 if(y==1)  
	  COMMAND(0x80+x-1);  //1행
	 else      
	  COMMAND(0xc0+x-1);  //2행
}

int main(){
	
	init_system();
	init_LCD();
	
	MOVE(1,7);
	STRING("0000",4);

	while(1){	

		MOVE(1,7);
		DATA((count/1000)%10+0x30);
		DATA((count/100)%10+0x30);
		DATA((count/10)%10+0x30);
		DATA(count%10+0x30);
		
		count++;
		if (count >= 10000) count = 0;
		_delay_ms(100);
	}

}
