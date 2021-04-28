/*
 */

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{

    TCCR1A |= (1<<COM1A1)|(1<<WGM11)|(1<<WGM10);
    TCCR1B |= (1<<WGM12)|(1<<CS11)|(1<<CS10); //64 prescalar
    DDRB |= (1<<PB1);

    while(1)
    {

        OCR1A = 100;
        _delay_ms(200);
        OCR1A = 250;
        _delay_ms(200);
        OCR1A = 400;
        _delay_ms(200);
        OCR1A = 650;
        _delay_ms(200);
        OCR1A = 900;
        _delay_ms(200);
        OCR1A = 1024;
        _delay_ms(200);

    }

    return 0;
}
