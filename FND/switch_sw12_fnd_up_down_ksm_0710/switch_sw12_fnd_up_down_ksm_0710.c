#include <avr/io.h>
#include <util/delay.h>
unsigned char digit[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
int count=0;

int main(void) {
    DDRD = 0xff;
    DDRE = 0x0f;
    PORTE = 0x01;
    PORTD = digit[0];
    while (1){
        if(!(PINE & 0x40)) {
            if(count==9) count=-1;
            PORTD=digit[++count], _delay_ms(5);
            while(!(PINE & 0x40));      
        }
        if(!(PINE & 0x80)){          
            if(count==0) count=10;
            PORTD=digit[--count], _delay_ms(5);
            while(!(PINE & 0x80));      
        }          
    }
}
