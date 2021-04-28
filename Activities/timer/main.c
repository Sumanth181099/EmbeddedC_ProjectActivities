/*
 */

#include <avr/io.h>
#include <avr/interrupt.h>

unsigned volatile overflow;

int main(void)
{
    DDRD |= (1<<PD6);
    PORTD |= (1<<PD6); //LED
    TCCR0B |= (1<<CS02);
    TIMSK0 |= (1<<TOIE0); // Timer mask for interrupt
    TCNT0 = 0;
    overflow =0;
    sei();


    while(1)
    {
        if(overflow>=12)
        {
            if(TCNT0>=52)
            {
                PORTD ^= (1<<PD6);
                TCNT0 = 0;
                overflow = 0;
            }

        }
    }

    return 0;
}

ISR(TIMER0_OVF_vect)
{
    overflow++;
}
