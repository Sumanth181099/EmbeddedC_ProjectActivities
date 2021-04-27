#include <avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include"port.h"

unsigned volatile FLAG = 0;

void InitADC()
{
    ADMUX = (1<<REFS0);
    ADCSRA = (1<<ADEN)|(7<<ADPS0);
}

uint16_t ReadADC(uint8_t ch)
{
    ADMUX&=0xf8;
    ch=ch&0b00000111;
    ADMUX|=ch;

    ADCSRA|=(1<<ADSC);

    while(!(ADCSRA & (1<<ADIF)));

    ADCSRA|=(1<<ADIF);
    return(ADC);
}

int main(void)
{
    port();
    InitADC();
    uint16_t temp;

    while(1)
    {
        // Can turn on/off any device connected to port B0 based on interrupt generated
        if(FLAG == 1) //Switch pressed (default set to 1)
        {
            PORTB |=(1<<PB0);
            _delay_ms(2000);
            FLAG = 0;
            temp = ReadADC(0); //Read the temperature from sensor
            _delay_ms(200);
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
