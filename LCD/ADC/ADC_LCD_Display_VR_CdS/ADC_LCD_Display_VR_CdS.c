
#include<avr/io.h>
#include<util/delay.h>
#include <avr/interrupt.h>

int sw1, sw2 = 0;

void COMMAND(char byte)										 //##�������� ���� 
{
    PORTG = 0xFC;   		 //PORTG�� RS, RW, E �� ����Ǿ� �ִ�.
    PORTC = byte; 	                   //PORTC�� �����͹����� ����Ǿ� �ִ�.
    PORTG ^= 0x04;   		//E ��ȣ�� H->L�� �ϱ� ����
    _delay_ms(2);    		//LCD ���� ���۽ð�
}

//LCD�� �����͸� ���� ���� �Լ�
void DATA(unsigned char byte)									 //##�������� ����
{
    PORTG = 0xFD;    		  //PORTG�� RS, RW, E �� ����Ǿ� �ִ�.
    PORTC = byte;  		  //PORTC�� �����͹����� ����Ǿ� �ִ�.
    PORTG ^= 0x04;  		  //E ��ȣ�� H->L�� �ϱ� ����
    _delay_ms(2);   		  //LCD ���� ���۽ð�
}

// ATmega128�� ��Ʈ �ʱ�ȭ
void init_SYSTEM(void)
{
	 DDRA = 0xff;
     DDRC = 0xFF; 			 //LCD ������ ����
     PORTC = 0xFF;
     DDRG = 0xFF; 			 //LCD ��Ʈ�� ��ȣ(PG2=LCD_EN, PG1=RW, PG0=RS)
     PORTG = 0xFF;
}

// LCD �ʱ�ȭ
void init_LCD(void)
{
       _delay_ms(15);    			     //15msec �̻� �ð�����

       //Function set
       COMMAND(0x38); 			     //��ɼ�(�����͹��� 8��Ʈ, ���μ�:2��)
       _delay_ms(5);        			     //4.1msec �̻� �ð�����, ��������
       COMMAND(0x38); 			     //��ɼ�, ���� ����
       _delay_ms(100);      			     //100usec �̻� �ð�����, ��������

       COMMAND(0x38);  			     //��ɼ�, ���� ����
	_delay_ms(50); 
       COMMAND(0x08);  			     //ǥ�� Off , ���� ����
	_delay_ms(50);
       COMMAND(0x01);                                             //ȭ�� �����
	_delay_ms(50);
       COMMAND(0x06);			     //��Ʈ������
	_delay_ms(50);
       COMMAND(0x0C); 
	_delay_ms(50);			     //ǥ�� on
}

void STRING(unsigned char font[], unsigned char n) 			//##Ȥ�� �𸣴� �ϱ� 
{
    int i;
	for(i=0; i<n; i++)
    {
        DATA(font[i]);
    }
}

void MOVE(int y, int x)								//##Ȥ�� �𸣴� �ϱ� 
{
    unsigned char data;
    if(y == 1)    data = 0x80 + x - 1;        // 1��
    else          data = 0xc0 + x - 1;        // 2��
    COMMAND(data);
}

unsigned int READ_ADC(unsigned int adc_input){
	unsigned int adc_result = 0;
 	ADCSRA = 0x87;
	ADMUX = adc_input;
 	ADCSRA |= 0x40;
	while((ADCSRA & 0x10)==0);
	adc_result = ADCL + (ADCH<<8);
	return adc_result;
}

void LCD_INT_DISPLAY(unsigned int val) 	// A/D ��ȯ ������� ���������� ǥ���ϴ� �Լ�

{ 
	DATA(val/1000%10 + 0x30);
	DATA(val/100%10 + 0x30);
	DATA(val/10%10 + 0x30); 
	DATA(val%10 + 0x30);
	DATA(0x20);
}


int main(void)
{
	SREG = 0x80;	EIMSK = 0x40;	EICRB = 0x30;
	EIMSK = 0xC0;
	EICRB = 0xa0;

	init_SYSTEM();
	init_LCD();
	MOVE(2,1);	
	STRING("VR 0000 CdS 0000",16);
	while(1)
	{	
		PORTA = 0xff;
		MOVE(1,4);
		STRING("ADC value =",11);
		MOVE(2,1);
		STRING("VR ",3);
		LCD_INT_DISPLAY(READ_ADC(0)); 
		STRING("CdS ",4);
		LCD_INT_DISPLAY(READ_ADC(1));   


		if(sw1 == 1){
			PORTA = 0x00;
			MOVE(1,4);
			STRING("SW1 Pressed  ",13);
			_delay_ms(500);
			MOVE(1,4);
			STRING("ADC value =  ",13);
			sw1 = 0;
		
		}
		if(sw2 == 1){
			PORTA = 0b01010101;
			MOVE(1,4);
			STRING("SW2 Pressed  ",13);
			_delay_ms(500);
			MOVE(1,4);
			STRING("ADC value =  ",13);
			sw2 = 0;
		}
	}
}

ISR(INT6_vect){
	sw1=1;
}

ISR(INT7_vect){

	sw2 = 1;
}
	



/*
#include<avr/io.h>
 #include<util/delay.h>

 void COMMAND(char byte)
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

 // ATmega128�� ��Ʈ �ʱ�ȭ
void init_SYSTEM(void)
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
       _delay_ms(100);              //100usec �̻� �ð�����, ��������

       COMMAND(0x38);          //��ɼ�, ���� ����
  _delay_ms(50);
        COMMAND(0x08);          //ǥ�� Off , ���� ����
  _delay_ms(50);
        COMMAND(0x01);                                             //ȭ�� �����
  _delay_ms(50);
        COMMAND(0x06);        //��Ʈ������
  _delay_ms(50);
        COMMAND(0x0C);
     _delay_ms(50);        //ǥ�� on
 }

 void STRING(unsigned char font[], unsigned char n)
 {
  int i;
     for(i=0; i<n; i++)
     {
         DATA(font[i]);
     }
 }

 void MOVE(int y, int x)
 {
     unsigned char data;
     if(y == 1)    data = 0x80 + x - 1;        // 1��
    else          data = 0xc0 + x - 1;        // 2��
    COMMAND(data);
 }

 unsigned int READ_ADC(unsigned int adc_input){
  unsigned int adc_result = 0;
   ADCSRA = 0x87;
  ADMUX = adc_input;
   ADCSRA |= 0x40;
  while((ADCSRA & 0x10)==0);
  adc_result = ADCL + (ADCH<<8);
  return adc_result;
 }

 void LCD_INT_DISPLAY(unsigned int val)  // A/D ��ȯ ������� ���������� ǥ���ϴ� �Լ�

{
  DATA(val/1000%10 + 0x30);
  DATA(val/100%10 + 0x30);
  DATA(val/10%10 + 0x30);
  DATA(val%10 + 0x30);
  DATA(0x20);
 }


 int main(void)
 {
  init_SYSTEM();
  init_LCD();
  MOVE(1,4);
  STRING("ADC value =",11);
  MOVE(2,1);
  STRING("VR 0000 CdS 0000",16);
  while(1)
  {
   MOVE(2,1);
   STRING("VR ",3);
   LCD_INT_DISPLAY(READ_ADC(0));
   STRING("CdS ",4);
   LCD_INT_DISPLAY(READ_ADC(1));     
  }
 }

 */

