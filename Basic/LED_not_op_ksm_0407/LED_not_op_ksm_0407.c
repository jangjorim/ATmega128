#include <avr/io.h>       // avr/io.h������� ����
#include <util/delay.h>   // util/delay ������� ����

int main(void) {          // main �Լ� ����
	DDRA = 0b11111111;    // ��ƮA8�� ���� ��� �������
	while (1) {           // ���ѹݺ�
		PORTA = ~0b01010101;  //not �����ڸ� �̿��ؼ� ��ƮA�� 7531���� �ҵ�  6420���� ����
		_delay_ms(1000);      //delay �Լ� ȣ��(1000ms ����)
		PORTA = ~0b10101010;  //�״� LED�� �ٽ� �ҵ��Ѵ�

		PORTA = ~0b10101010;  //not �����ڸ� �̿��ؼ� ��ƮA�� 7531���� ����  6420���� �ҵ�
		_delay_ms(1000);      //delay �Լ� ȣ��(1000ms ����)
		PORTA = ~0b01010101;  //�״� LED�� �ٽ� �ҵ��Ѵ�
	}
}
