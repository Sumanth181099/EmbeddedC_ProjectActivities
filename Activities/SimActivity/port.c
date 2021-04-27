
#include <avr/io.h>
#include<avr/interrupt.h>

void port()
{
    DDRB |=(1<<PB0); //Set output for LED
    DDRD &=~(1<<PD2); //Set input(clear bit)
    PORTD |=(1<<PD2); //Set bit
    EICRA |=(1<<ISC00);
    EIMSK |=(1<<INT0);
    sei();
}
