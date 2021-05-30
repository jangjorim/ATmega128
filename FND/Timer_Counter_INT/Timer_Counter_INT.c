#include<avr/io.h>
#include<avr/interrupt.h>

unsigned char LED_Data = 0xff;
unsigned char timer0Cnt = 0;

ISR(TIMER0_OVF_vect); //Timer0 Overflow0 ISP

int main(){
    DDRA = 0xFF; 

    TCCR0 = 0x07; // 1024����
    TCNT0 =0xff - 160; 
    TIMSK |=1<<TOIE0; // �����÷ο� ���ͷ�Ʈ ���
    TIFR |=1<<TOV0; // TOV0 Timer/Counter0 overflow flag Ŭ����

    SREG=0x80;

    while(1){
        PORTA = LED_Data; // LED_Data�� ��Ʈ A�� ������.
    }
    return 0;
}

ISR(TIMER0_OVF_vect){
    SREG=0x00; //cli();
    TCNT0=0xff - 160;
    timer0Cnt++;
    if(timer0Cnt == 100){      // 0.01s * 100 = 1s 1�ʸ� ��� ���� ī��Ʈ Ƚ��
        LED_Data--;
        timer0Cnt=0;
    }
    SREG=0x80;
}
