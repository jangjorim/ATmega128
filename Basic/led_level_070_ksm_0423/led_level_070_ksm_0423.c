#include <avr/io.h>         // util/delay ������� ���� 
#include <util/delay.h>     // util/delay ������� ���� 

unsigned char num1 = 0xfe; 	//shift �������ϱ� ���� ���� ����
int main(void) {            // main �Լ� ���� 

	DDRA = 0b11111111;      // ��ƮA8�� ���� ��� �������
	//unsigned char num2 = 0xf7;
	while (1) {
		/*for (int i = 0; i < 8; i++) {       // for�� ���� 8���� �ݺ�
			PORTA = num1;                   //��ƮA�� LED�� 7���� 0���� ������ ����
			num1 = (num1 << 1);       // ���������� ��Ʈ�� ��ĭ�� �̵��Ͽ� ����
			_delay_ms(1000);                //delay �Լ� ȣ��(1000ms ����)
		}
		for (int i = 0;i < 8; i++){
			PORTA = num1;
			num1 = (num1 >> 1)+ 0x80;
			_delay_ms(1000); 
		}*/


		for (int i = 0; i < 14; i++) {
			
			PORTA = num1;
			
			
			if (i < 7)
				num1 <<= 1;
			else 
				num1 = (num1 >> 1) + 128;

			_delay_ms(1000);

		}
	
	}
}
