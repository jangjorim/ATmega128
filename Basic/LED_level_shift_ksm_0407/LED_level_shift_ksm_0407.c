#include <avr/io.h>         // util/delay ������� ���� 
#include <util/delay.h>     // util/delay ������� ���� 

int main(void) {            // main �Լ� ���� 

	DDRA = 0b11111111;        // ��ƮA8�� ���� ��� �������
	unsigned char num1 = 0x7f; //shift �������ϱ� ���� ���� ����

	while (1) {
		
		num1 = 0x7f;

		for (int i = 0; i < 8; i++) {       // for�� ���� 8���� �ݺ�
			PORTA = ~(num1 >> i);
			_delay_ms(1000);                //delay �Լ� ȣ��(1000ms ����)
		}
	}
}
