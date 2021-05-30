#include <avr/io.h>         // util/delay 헤더파일 포함 
#include <util/delay.h>     // util/delay 헤더파일 포함 

unsigned char num1 = 0xfe; 	//shift 연산을하기 위한 변수 선언
int main(void) {            // main 함수 정의 

	DDRA = 0b11111111;      // 포트A8개 핀을 모두 출력으로
	//unsigned char num2 = 0xf7;
	while (1) {
		for (int i = 0; i < 7; i++) {       // for문 시작 8번만 반복
			PORTA = num1;                   //포트A의 LED를 7부터 0까지 순서로 점등
			num1 = (num1 << 1) + 1;       // 오른쪽으로 비트를 한칸씩 이동하여 점등
			_delay_ms(1000);                //delay 함수 호출(1000ms 지연)
		}
		for (int i = 0;i < 7; i++){
			PORTA = num1;
			num1 = ((num1 >> 1) + 0x80);
			_delay_ms(1000);
		}
	


		/*for (int i = 0; i < 16; i++) {
			
			PORTA = num1;
			
			
			if (i < 8)
				num1 = (num1 << 1);
			else 
				num1 = (num1 >> 1);

			_delay_ms(1000);

		}*/
	
	}
}
