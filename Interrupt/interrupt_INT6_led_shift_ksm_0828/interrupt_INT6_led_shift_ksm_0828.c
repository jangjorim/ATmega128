#include <avr/io.h>
#include <avr/interrupt.h>

int shift=0;

int main(){
	DDRA = 0xff;
	PORTA = 0xff;
	SREG = 0x80;
	EIMSK = 0x40;
	EICRB = 0x30;
	
	while(1);
}

ISR(INT6_vect){
		PORTA = ~(0x01 << shift++);
		if(shift>=8) shift = 0;
}

/*

// �ǽ�����
// INT6�� ��ġ�� ����ġ�� ���� ��  led�� 1���� shift ���ѹݺ�
// Ʈ���� ��� : rising edge ���
// �ʱⰪ : LED�� ��� OFF


#include <avr/io.h>
#include <avr/interrupt.h>

int shift=0;

int main(void) {
// ��Ʈ �ʱ�ȭ
DDRA = 0xff;    // ��Ʈ A ��¹��⼳��
PORTA = 0xff;  // ��Ʈ A �ʱⰪ ��� , LED ��� �ҵ�
// ���ͷ�Ʈ �ʱ�ȭ
SREG = 0x80;  // ��ü ���ͷ�Ʈ ���
EIMSK = 0x40;   // INT 6 ���ͷ�Ʈ ���
EICRB = 0x30;  // INT 6 rising edge ����
while(1);   // ���α׷� ��� 
}

// �ܺ� ���ͷ�Ʈ6 ���� ��ƾ , ISR(���ͷ�Ʈ ���� ��ƾ��)
ISR(INT6_vect)  // �ܺ����ͷ�Ʈ6 ���� ��ƾ
{  // ISR ����
         PORTA = ~(0x01<<shift++);  // LED�� 0������ 7������ ��Ʈ �̵�
         if(shift>=8) shift=0;  // LED ���� shift�� 8�� �Ǹ� 0���� �ʱ�ȭ
}  // ISR  ��


*/
