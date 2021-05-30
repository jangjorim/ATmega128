#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int HOUR = 0, MIN = 0, SEC = 0;

void COMMAND(unsigned char byte)
{
    PORTG = 0xFC;      //PORTG�� RS, RW, E �� ����Ǿ� �ִ�.
    PORTC = byte;           //PORTC�� �����͹����� ����Ǿ� �ִ�.
    PORTG ^= 0x04;     //E ��ȣ�� H->L�� �ϱ� ����
    _delay_ms(2);      //LCD ���� ���۽ð�
}

void DATA(unsigned char byte)
{
    PORTG = 0xFD;        //PORTG�� RS, RW, E �� ����Ǿ� �ִ�.
    PORTC = byte;      //PORTC�� �����͹����� ����Ǿ� �ִ�.
    PORTG ^= 0x04;      //E ��ȣ�� H->L�� �ϱ� ����
    _delay_ms(2);       //LCD ���� ���۽ð�
}

void init_system(void)
{
     DDRC = 0xFF;     //LCD ������ ����
     PORTC = 0xFF;
     DDRG = 0xFF;     //LCD ��Ʈ�� ��ȣ(PG2=LCD_EN, PG1=RW, PG0=RS)
     PORTG = 0xFF;
}

void init_LCD(void)
{
       _delay_ms(15);            //15msec �̻� �ð�����
       COMMAND(0x38);         //Function set, ��ɼ�(�����͹��� 8��Ʈ, ���μ�:2��)
       _delay_ms(5);                //4.1msec �̻� �ð�����, ��������
       COMMAND(0x38);         //��ɼ�, ���� ����
       _delay_us(100);              //100usec �̻� �ð�����, ��������
       COMMAND(0x38);          //��ɼ�, ���� ����
       COMMAND(0x08);          //ǥ�� Off , ���� ����
       COMMAND(0x01);         //ȭ�� �����
       COMMAND(0x06);        //��Ʈ������
       COMMAND(0x0C);         //ǥ�� on
}

void STRING(unsigned char font[], unsigned char n)
{
	 unsigned char i;
	 for(i=0 ; i<n ; i++)
	     {
	          DATA(font[i]);
	     }
}

void MOVE(int y, int x)     //Ŀ�� �̵�
{               
	 if(y==1)  
	  COMMAND(0x80+x-1);  //1��
	 else      
	  COMMAND(0xc0+x-1);  //2��
}

int main(){

	init_system();
	init_LCD();

	while(1){

		_delay_ms(1000);

		SEC++;
		if(SEC >= 60){
			SEC = 0;
			MIN++;
			if(MIN >= 60){
				MIN = 0;
				HOUR++;
				if(HOUR >=24){
					HOUR = 0;
				}
			}
		}
		MOVE(1,7);
		STRING("TIME",4);
		MOVE(2,5);
		DATA(HOUR/10+0x30);
		DATA(HOUR%10+0x30);
		DATA(':');
		DATA(MIN/10+0x30);
		DATA(MIN%10+0x30);
		DATA(':');
		DATA(SEC/10+0x30);
		DATA(SEC%10+0x30);
		
	}

}
