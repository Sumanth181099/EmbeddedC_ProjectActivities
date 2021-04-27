/*
 */

#include <avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

unsigned volatile FLAG = 0;

int main(void)
{
    port();

    while(1)
    {
        if(FLAG == 1) //Switch pressed (default set to 1)
        {
            PORTB |=(1<<PB0);
            _delay_ms(2000);
            FLAG = 0;
        }
        else
        {
            PORTB &=~(1<<PB0);
            _delay_ms(2000);
        }

    }


    return 0;
}

ISR(INT0_vect)
{
    FLAG = 1;
}
