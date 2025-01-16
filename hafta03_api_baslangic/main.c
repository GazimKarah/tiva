#include "stdint.h"
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_types.h"

int main(void)
{
    SYSCTL_RCGCGPIO_R|=0x20; // portf aktif perihpahrableenable(portf) A=A|0x20
    GPIO_PORTF_DIR_R|=0x0E; // potf nin yönlendirimesi
    GPIO_PORTF_DEN_R|=0x1f; // bütün prtf pinleri pad enable

    while(1)
    {
        long i;
        GPIO_PORTF_DATA_R|=0x02;// 1. pini enerjilendirmek demek 00010
        for (i=0;i<2000000;i++){}
        GPIO_PORTF_DATA_R=0x00;// 1. pini enerjilendirmek demek 00010
        for (i=0;i<2000000;i++){}
    }
}
