#include <avr/io.h>         // util/delay ������� ���� 
#include <util/delay.h>     // util/delay ������� ���� 

int main(void) {            // main �Լ� ����

	DDRA = 0xFF;              // ��ƮA8�� ���� ��� �������
	unsigned char num1 = 254; //shift �������ϱ� ���� ���� ����
	
	for (int i = 0; i < 8; i++) { // for�� ���� 8���� �ݺ�
		PORTA = num1;             // ��ƮA�� LED�� 0��°�� �ҵ��Ű�� ���� �������� ��ĭ�� �̵��ϸ� �̵��� ���� �ҵ� ��Ų��.
		num1 <<= 1;               // ��Ʈ�� �������� ��ĭ �̵��Ѵ�
		num1 = num1 | 1;          // ��Ʈ�� �̵��ѵ� 1�� ���� ������ �ҵ�Ȱ��� �����Ѵ�
		_delay_ms(1000);          // delay �Լ� ȣ��(1000ms ����)
	}
}
