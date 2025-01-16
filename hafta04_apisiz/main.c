#include "stdint.h"
#include"inc/tm4c123gh6pm.h"

//apisiz

int main(void)
{
    SYSCTL_RCGCGPIO_R|=0x20; // portf saat aktif

    GPIO_PORTF_LOCK_R = 0x4C4F434B; // commit aç
    GPIO_PORTF_CR_R = 0x01;   // pf0 da artýk konfigurasyn yapýlabilir. 0000 0001
                              // 0000 0001 -> pf0 artýk konfigure edilebilir

    GPIO_PORTF_DIR_R|=0x0E; // 0b 0000 1110 yönlendirme
    GPIO_PORTF_DEN_R|=0x1F; // 0b 0001 1111 pin aktifliði

    GPIO_PORTF_PUR_R = 0x11; // pf0 ve pf4 pull-up aktif 0001 0001

    while(1)
    {
        unsigned int value;
        value=GPIO_PORTF_DATA_R;


        if ((value & 0x10)==0)// pf4 için
        {
            GPIO_PORTF_DATA_R|=0x02;
        }

        if((value & 0x01)==0)// pf0 için
        {
            GPIO_PORTF_DATA_R|=0x04;
        }
    }
}
