#include <avr/io.h>         // util/delay 헤더파일 포함 
#include <util/delay.h>     // util/delay 헤더파일 포함 

int main(void) {            // main 함수 정의 

	DDRA = 0b11111111;        // 포트A8개 핀을 모두 출력으로
	unsigned char num1 = 0x7f; //shift 연산을하기 위한 변수 선언

	while (1) {
		
		num1 = 0x7f;

		for (int i = 0; i < 8; i++) {       // for문 시작 8번만 반복
			PORTA = ~(num1 >> i);
			_delay_ms(1000);                //delay 함수 호출(1000ms 지연)
		}
	}
}
