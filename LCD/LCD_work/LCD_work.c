#include <avr/io.h>
#include <util/delay.h>

//  PC7 PC6 PC5 PC4 PC3 PC2 PC1 PC0                     // PG2  PG1  PG0
//  DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0                   //   E     RW   RS

void COMMAND(unsigned char byte); // COMMAND �Լ� ����
void DATA(unsigned char byte);  // DATA �Լ� ����
void init_LCD(void);   // init_LCD �Լ� ����
void init_system(void);                                      // init_system �Լ� ����

int main(void)
{
	 init_system();

	 init_LCD ();

	 DATA(0x47);
	 DATA(0x53);
	 DATA(0x4D);
	 _delay_ms(1000);

	 COMMAND(0x01);
	 _delay_ms(1000);

	 DATA('M');
	 DATA('S');
	 DATA('T');

	 //COMMAND(0x01);
	 //_delay_ms(10);

	 while(1);
}

//LCD�� ����� ���� ���� �Լ�

void COMMAND(unsigned char byte)
{
    PORTG = 0xFC;      //PORTG�� RS, RW, E �� ����Ǿ� �ִ�.
    PORTC = byte;                     //PORTC�� �����͹����� ����Ǿ� �ִ�.
    PORTG ^= 0x04;     //E ��ȣ�� H->L�� �ϱ� ����
    _delay_ms(2);      //LCD ���� ���۽ð�
}

//LCD�� �����͸� ���� ���� �Լ�

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

// LCD �ʱ�ȭ

void init_LCD(void)
{
       _delay_ms(15);            //15msec �̻� �ð�����
       //Function set
       COMMAND(0x38);         //��ɼ�(�����͹��� 8��Ʈ, ���μ�:2��)
       _delay_ms(5);                //4.1msec �̻� �ð�����, ��������
       COMMAND(0x38);         //��ɼ�, ���� ����
       _delay_us(100);              //100usec �̻� �ð�����, ��������
       COMMAND(0x38);          //��ɼ�, ���� ����
       COMMAND(0x08);          //ǥ�� Off , ���� ����
       COMMAND(0x01);                                             //ȭ�� �����
       COMMAND(0x06);        //��Ʈ������
       COMMAND(0x0C);         //ǥ�� on
}
