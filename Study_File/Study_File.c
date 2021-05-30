#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

/*
int sw1, sw2 = 0;

void init_SYSTEM(){
	DDRA = 0xff;
	DDRC = 0xff;
	DDRG = 0xff;
	PORTC = 0xff;
	PORTG = 0xff;
}

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

void COMMAND(char byte){
	PORTG = 0xFC;
	PORTC = byte;
	PORTG ^= 0x04;
	_delay_ms(2);
}

void DATA(char byte){
	PORTG = 0xFD;
	PORTC = byte;
	PORTG ^= 0x04;
	_delay_ms(2);
}

void STRING(char font[], int n){
	int i ;
	for(i = 0; i < n; i++) DATA(font[i]);
}

void MOVE(int y, int x){
	if(y == 1) 	COMMAND(0x80 + x-1);
	else		COMMAND(0xc0 + x-1);
}

int READ_ADC(int ads_input){
	ADCSRA = 0x87;
	ADMUX = ads_input;
	ADCSRA |= 0x40;
	while((ADCSRA & 0x10) == 0);
	return ADCL + (ADCH<<8);
}

void LCD_INT_DISPLAY(int val){
	DATA(val/1000%10 + 0x30);
	DATA(val/100%10 + 0x30);
	DATA(val/10%10 + 0x30);
	DATA(val%10 + 0x30);
	DATA(0x20);
}

int main(){
	SREG = 0x80;
	EIMSK = 0xc0;
	EICRB = 0xa0;

	init_SYSTEM();
	init_LCD();

	while(1){
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
			PORTA = 0x55;
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
	sw1 = 1;
}

ISR(INT7_vect){
	sw2 = 1;
}
*/

/*
int i, sw1, sw2 = 0;

void init_SYSTEM(){
	DDRA = 0xff;
	DDRC = 0xff;
	DDRG = 0xff;
	PORTC = 0xff;
	PORTG = 0xff;
}

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

void COMMAND(char byte){
	PORTG = 0xFC;
	PORTC = byte;
	PORTG ^= 0x04;
	_delay_ms(2);
}

void DATA(char byte){
	PORTG = 0xFD;
	PORTC = byte;
	PORTG ^= 0x04;
	_delay_ms(2);
}

void STRING(char font[], int n){
	int i ;
	for(i = 0; i < n; i++) DATA(font[i]);
}

void MOVE(int y, int x){
	if(y == 1) 	COMMAND(0x80 + x-1);
	else		COMMAND(0xc0 + x-1);
}

int READ_ADC(int ads_input){
	ADCSRA = 0x87;
	ADMUX = ads_input;
	ADCSRA |= 0x40;
	while((ADCSRA & 0x10) == 0);
	return ADCL + (ADCH<<8);
}

void LCD_INT_DISPLAY(int val){
	DATA(val/1000%10 + 0x30);
	DATA(val/100%10 + 0x30);
	DATA(val/10%10 + 0x30);
	DATA(val%10 + 0x30);
	DATA(0x20);
}

int main(){
	SREG = 0x80;
	EIMSK = 0xc0;
	EICRB = 0xa0;

	init_SYSTEM();
	init_LCD();
	PORTA = 0xff;
	MOVE(1,4);
	STRING("2020-12-09",10);
	MOVE(2,4);
	STRING("ATmega128",9);
	_delay_ms(3000);
	while(1){
		PORTA = 0xff;
		MOVE(1,4);
		STRING("ADC value =",11);
		MOVE(2,1);
		STRING("VR ",3);
		LCD_INT_DISPLAY(READ_ADC(0));
		STRING("CdS ",4);
		LCD_INT_DISPLAY(READ_ADC(1));

		if(sw1 == 1){
			MOVE(1,4);
			STRING("SW1 Pressed  ",13);
			PORTA = 0x00;
			_delay_ms(250);
			PORTA = 0xff;
			_delay_ms(250);
			PORTA = 0x00;
			_delay_ms(250);
			PORTA = 0xff;
			_delay_ms(250);
			MOVE(1,4);
			STRING("ADC value =  ",13);
			sw1 = 0;
		}
		if(sw2 == 1){
			MOVE(1,4);
			STRING("SW2 Pressed  ",13);
			for(i = 0; i < 3; i++){
				PORTA = 0x0f;
				_delay_ms(500);
				PORTA = 0xf0;
				_delay_ms(500);
			} 
			MOVE(1,4);
			STRING("ADC value =  ",13);
			sw2 = 0;
		}
	}
}

ISR(INT6_vect){
	sw1 = 1;
}

ISR(INT7_vect){
	sw2 = 1;
}

*/

#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

int i, sw1, sw2 = 0;

void init_SYSTEM(){
	DDRG = 0xff;
	DDRC = 0xff;
	DDRA = 0xff;
	PORTG = 0xff;
	PORTC = 0xff;
}

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

void COMMAND(char byte){
	PORTG = 0xFC;
	PORTC = byte;
	PORTG ^= 0x04;
	_delay_ms(2);
}

void DATA(char byte){
	PORTG = 0xFD;
	PORTC = byte;
	PORTG ^= 0x04;
	_delay_ms(2);
}

void STRING(char font[], int n){
	for(i = 0; i < n; i++)DATA(font[i]);
}

void MOVE(int y, int x){
	if(y == 1) COMMAND(0x80 + x-1);
	else COMMAND(0xC0 + x-1);
}

int READ_ADC(int adc_input){
	ADCSRA = 0x87;
	ADMUX = adc_input;
	ADCSRA |= 0x40;
	while((ADCSRA &= 0x10) == 0);
	return ADCL + (ADCH<<8);
}

void INT_LCD_DISPLAY(int val){
	DATA(val/1000%10 + 0x30);
	DATA(val/100%10 + 0x30);
	DATA(val/10%10 + 0x30);
	DATA(val%10 + 0x30);
	DATA(0x20);
}

int main(){
	SREG = 0x80;
	EIMSK = 0xC0;
	EICRB = 0xa0;

	init_SYSTEM();
	init_LCD();

	while(1){
		PORTA = 0xff;
		MOVE(1,4);
		STRING("ADC value =  ", 13);
		MOVE(2,1);
		STRING("VR ",3);
		INT_LCD_DISPLAY(READ_ADC(0));
		STRING("CdS ", 4);
		INT_LCD_DISPLAY(READ_ADC(1));

		if(sw1 == 1){
			PORTA = 0x00;
			MOVE(1,4);
			STRING("SW1 Pressed  ", 13);
			_delay_ms(500);
			MOVE(1,4);
			STRING("ADC value =  ", 13);
			sw1 = 0;
		}
		if(sw2 == 1){
			PORTA = 0x55;
			MOVE(1,4);
			STRING("SW2 Pressed  ", 13);
			_delay_ms(500);
			MOVE(1,4);
			STRING("ADC value =  ", 13);
			sw2 = 0;
		}
	}
}

ISR(INT6_vect){
	sw1 = 1;
}
ISR(INT7_vect){
	sw2 = 1;
}












































