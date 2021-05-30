#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

long count = 0;

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
