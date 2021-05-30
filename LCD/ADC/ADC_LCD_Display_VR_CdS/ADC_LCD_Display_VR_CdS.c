
#include<avr/io.h>
#include<util/delay.h>
#include <avr/interrupt.h>

int sw1, sw2 = 0;

void COMMAND(char byte)										 //##제공하지 않음 
{
    PORTG = 0xFC;   		 //PORTG에 RS, RW, E 가 연결되어 있다.
    PORTC = byte; 	                   //PORTC에 데이터버스가 연결되어 있다.
    PORTG ^= 0x04;   		//E 신호를 H->L로 하기 위해
    _delay_ms(2);    		//LCD 내부 동작시간
}

//LCD에 데이터를 쓰기 위한 함수
void DATA(unsigned char byte)									 //##제공하지 않음
{
    PORTG = 0xFD;    		  //PORTG에 RS, RW, E 가 연결되어 있다.
    PORTC = byte;  		  //PORTC에 데이터버스가 연결되어 있다.
    PORTG ^= 0x04;  		  //E 신호를 H->L로 하기 위해
    _delay_ms(2);   		  //LCD 내부 동작시간
}

// ATmega128의 포트 초기화
void init_SYSTEM(void)
{
	 DDRA = 0xff;
     DDRC = 0xFF; 			 //LCD 데이터 버스
     PORTC = 0xFF;
     DDRG = 0xFF; 			 //LCD 컨트롤 신호(PG2=LCD_EN, PG1=RW, PG0=RS)
     PORTG = 0xFF;
}

// LCD 초기화
void init_LCD(void)
{
       _delay_ms(15);    			     //15msec 이상 시간지연

       //Function set
       COMMAND(0x38); 			     //기능셋(데이터버스 8비트, 라인수:2줄)
       _delay_ms(5);        			     //4.1msec 이상 시간지연, 생략가능
       COMMAND(0x38); 			     //기능셋, 생략 가능
       _delay_ms(100);      			     //100usec 이상 시간지연, 생략가능

       COMMAND(0x38);  			     //기능셋, 생략 가능
	_delay_ms(50); 
       COMMAND(0x08);  			     //표시 Off , 생략 가능
	_delay_ms(50);
       COMMAND(0x01);                                             //화면 지우기
	_delay_ms(50);
       COMMAND(0x06);			     //엔트리모드셋
	_delay_ms(50);
       COMMAND(0x0C); 
	_delay_ms(50);			     //표시 on
}

void STRING(unsigned char font[], unsigned char n) 			//##혹시 모르니 암기 
{
    int i;
	for(i=0; i<n; i++)
    {
        DATA(font[i]);
    }
}

void MOVE(int y, int x)								//##혹시 모르니 암기 
{
    unsigned char data;
    if(y == 1)    data = 0x80 + x - 1;        // 1행
    else          data = 0xc0 + x - 1;        // 2행
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

void LCD_INT_DISPLAY(unsigned int val) 	// A/D 변환 결과값을 정수값으로 표시하는 함수

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
     PORTG = 0xFC;      //PORTG에 RS, RW, E 가 연결되어 있다.
     PORTC = byte;                     //PORTC에 데이터버스가 연결되어 있다.
     PORTG ^= 0x04;     //E 신호를 H->L로 하기 위해
    _delay_ms(2);      //LCD 내부 동작시간
}

 //LCD에 데이터를 쓰기 위한 함수
void DATA(unsigned char byte)
 {
     PORTG = 0xFD;        //PORTG에 RS, RW, E 가 연결되어 있다.
     PORTC = byte;      //PORTC에 데이터버스가 연결되어 있다.
     PORTG ^= 0x04;      //E 신호를 H->L로 하기 위해
    _delay_ms(2);       //LCD 내부 동작시간
}

 // ATmega128의 포트 초기화
void init_SYSTEM(void)
 {
      DDRC = 0xFF;     //LCD 데이터 버스
     PORTC = 0xFF;
      DDRG = 0xFF;     //LCD 컨트롤 신호(PG2=LCD_EN, PG1=RW, PG0=RS)
      PORTG = 0xFF;
 }

 // LCD 초기화
void init_LCD(void)
 {
        _delay_ms(15);            //15msec 이상 시간지연

       //Function set
        COMMAND(0x38);         //기능셋(데이터버스 8비트, 라인수:2줄)
        _delay_ms(5);                //4.1msec 이상 시간지연, 생략가능

       COMMAND(0x38);         //기능셋, 생략 가능
       _delay_ms(100);              //100usec 이상 시간지연, 생략가능

       COMMAND(0x38);          //기능셋, 생략 가능
  _delay_ms(50);
        COMMAND(0x08);          //표시 Off , 생략 가능
  _delay_ms(50);
        COMMAND(0x01);                                             //화면 지우기
  _delay_ms(50);
        COMMAND(0x06);        //엔트리모드셋
  _delay_ms(50);
        COMMAND(0x0C);
     _delay_ms(50);        //표시 on
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
     if(y == 1)    data = 0x80 + x - 1;        // 1행
    else          data = 0xc0 + x - 1;        // 2행
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

 void LCD_INT_DISPLAY(unsigned int val)  // A/D 변환 결과값을 정수값으로 표시하는 함수

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

