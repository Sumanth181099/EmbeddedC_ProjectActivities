/*
 */

#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

int main(void)
{

    USARTInit(103);

    while(1)
    {
        USARTWriteChar('S');
    }

    return 0;
}
