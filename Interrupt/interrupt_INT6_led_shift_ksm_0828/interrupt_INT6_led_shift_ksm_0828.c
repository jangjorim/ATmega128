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

// 실습내용
// INT6에 위치한 스위치를 누를 때  led가 1개씩 shift 무한반복
// 트리거 방식 : rising edge 사용
// 초기값 : LED가 모두 OFF


#include <avr/io.h>
#include <avr/interrupt.h>

int shift=0;

int main(void) {
// 포트 초기화
DDRA = 0xff;    // 포트 A 출력방향설정
PORTA = 0xff;  // 포트 A 초기값 출력 , LED 모두 소등
// 인터럽트 초기화
SREG = 0x80;  // 전체 인터럽트 허용
EIMSK = 0x40;   // INT 6 인터럽트 허용
EICRB = 0x30;  // INT 6 rising edge 설정
while(1);   // 프로그램 대기 
}

// 외부 인터럽트6 서비스 루틴 , ISR(인터럽트 서비스 루틴명)
ISR(INT6_vect)  // 외부인터럽트6 서비스 루틴
{  // ISR 시작
         PORTA = ~(0x01<<shift++);  // LED가 0번부터 7번까지 비트 이동
         if(shift>=8) shift=0;  // LED 변수 shift가 8이 되면 0으로 초기화
}  // ISR  끝


*/
