#include <avr/io.h>       // avr/io.h헤더파일 포함
#include <util/delay.h>   // util/delay 헤더파일 포함

int main(void) {          // main 함수 정의
	DDRA = 0b11111111;    // 포트A8개 핀을 모두 출력으로
	while (1) {           // 무한반복
		PORTA = ~0b01010101;  //not 연산자를 이용해서 포트A의 7531번을 소등  6420번을 점등
		_delay_ms(1000);      //delay 함수 호출(1000ms 지연)
		PORTA = ~0b10101010;  //켰던 LED를 다시 소등한다

		PORTA = ~0b10101010;  //not 연산자를 이용해서 포트A의 7531번을 점등  6420번을 소등
		_delay_ms(1000);      //delay 함수 호출(1000ms 지연)
		PORTA = ~0b01010101;  //켰던 LED를 다시 소등한다
	}
}
