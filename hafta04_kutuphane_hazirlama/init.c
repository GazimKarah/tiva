
#include "stdint.h"
#include "inc/tm4c123gh6pm.h"
#include "init.h"

void bb_GpioPortfEnable(void){
    SYSCTL_RCGCGPIO_R|=0x20;
    // burada biraz beklersen iyi olur
    volatile unsigned long loop;

    loop=SYSCTL_RCGCGPIO_R; // olesine

    GPIO_PORTF_DIR_R|=0x08; // 3. led output

    GPIO_PORTF_DEN_R|=0x08; // enable pin
}

