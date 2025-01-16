#include "stdint.h"
#include "inc/tm4c123gh6pm.h"
#include "init.h"

int main(void)
{
    bb_GpioPortfEnable();
//    SYSCTL_RCGCGPIO_R|=0x20;
//    // burada biraz beklersen iyi olur
    volatile unsigned long loop;
//
//    loop=SYSCTL_RCGCGPIO_R; // olesine
//
//    GPIO_PORTF_DIR_R|=0x08; // 3. led output
//
//    GPIO_PORTF_DEN_R|=0x08; // enable pin

    while(1)
    {
        GPIO_PORTF_DATA_R|=0x08;

        for(loop=0;loop<200000;loop++)
        {}

        GPIO_PORTF_DATA_R&=~(0x08);

        for(loop=0;loop<200000;loop++)
        {}
    }

}
