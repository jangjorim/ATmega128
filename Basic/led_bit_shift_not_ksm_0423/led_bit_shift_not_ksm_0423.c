#include <avr/io.h>         // util/delay 헤더파일 포함 
#include <util/delay.h>     // util/delay 헤더파일 포함 

int main(void) {            // main 함수 정의

	DDRA = 0xFF;              // 포트A8개 핀을 모두 출력으로
	unsigned char num1 = 0x01; //shift 연산을하기 위한 변수 선언
	while(1){
		for (int i = 0; i < 8; i++) { // for문 시작 8번만 반복
			PORTA = ~num1;             // 포트A의 LED중 0번째만 소등시키고 점점 왼쪽으로 한칸씩 이동하며 이동된 곳만 소등 시킨다.
			num1 <<= 1;               // 비트를 왼쪽으로 한칸 이동한다
			num1 = num1 | 0x00;          // 비트로 이동한뒤 1를 더해 이전에 소등된곳을 점등한다
			_delay_ms(1000);          // delay 함수 호출(1000ms 지연)
		}
		num1 = 0x01;
	}
}
