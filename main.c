/*
 */

#include <avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include"port.h"
#include"usart.h"

unsigned volatile FLAG = 0;
unsigned volatile overflow;

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
    USARTInit(103);
    uint16_t temp;
    DDRB |=(1<<PB1);

    //PWM
    TCCR1A |= (1<<COM1A1)|(1<<WGM11)|(1<<WGM10);
    TCCR1B |= (1<<WGM12)|(1<<CS11)|(1<<CS10);
    DDRB |= (1<<PB1);

    //Timer
    DDRD |= (1<<PD6);
    PORTD |= (1<<PD6);
    TCCR0B |= (1<<CS02);
    TIMSK0 |= (1<<TOIE0);
    TCNT0 = 0;
    overflow =0;
    sei();

    while(1)
    {

        if(FLAG == 1) //Switch pressed
        {
            PORTB |=(1<<PB0);
            _delay_ms(2000);
            FLAG = 0;
            temp = ReadADC(0); //Read the temperature from sensor
            USARTWriteChar(temp);
            _delay_ms(200);
        }
        else
        {
            PORTB &=~(1<<PB0);
            _delay_ms(2000);
        }

        if(overflow>=12)
        {
            if(TCNT0>=52)
            {
                PORTD ^= (1<<PD6);
                TCNT0 = 0;
                overflow = 0;
            }

        }

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

ISR(INT0_vect)
{
    FLAG = 1;
}

ISR(TIMER0_OVF_vect)
{
    overflow++;
}
