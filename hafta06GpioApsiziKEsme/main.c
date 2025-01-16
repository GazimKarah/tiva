#include "stdint.h"
#include"inc/tm4c123gh6pm.h"

//apisiz


void haricikesme(void)
{
    if ((GPIO_PORTF_MIS_R & 0x10))
    {
        GPIO_PORTF_ICR_R=0x10;
        GPIO_PORTF_DATA_R|=0x04;
    }

    if ((GPIO_PORTF_MIS_R & 0x01))
    {
        GPIO_PORTF_ICR_R=0x01;
        GPIO_PORTF_DATA_R|=0x02;
    }
}

int main(void)
{
    // Table 10-6. GPIO Register Map syf 660
    // eski yazim SYSCTL_RCGCGPIO_R|=0x20; // portf saat aktif
    // 00100000
    SYSCTL_RCGCGPIO_R|=(1<<5); //0x20;

    GPIO_PORTF_LOCK_R = 0x4C4F434B; // commit aç
    GPIO_PORTF_CR_R = 0x01;   // pf0 da artýk konfigurasyn yapýlabilir. 0000 0001
                              // 0000 0001 -> pf0 artýk konfigure edilebilir

    // eski yazým GPIO_PORTF_DIR_R|=0x0E; // 0b 0000 1110 yönlendirme
    GPIO_PORTF_DIR_R &= ~(1<<4)|~(1<<0); // pf0 ile pf4 = 0 demek input demek
    GPIO_PORTF_DIR_R |=(1<<3)|(1<<2)|(1<<1); // pf1-2-3 input oldu

    GPIO_PORTF_AFSEL_R=0x00; // kesinlikle i/o

    // eski yazim GPIO_PORTF_DEN_R|=0x1F; // 0b 0001 1111 pin aktifliði
    GPIO_PORTF_DEN_R|=(1<<4)|(1<<3)|(1<<2)|(1<<1)|(1<<0);

    // eski yazým GPIO_PORTF_PUR_R = 0x11; // pf0 ve pf4 pull-up aktif 0001 0001
    GPIO_PORTF_PUR_R =(1<<4)|(1<<0);

    // kesme registerlarý

//    7. Program the GPIOIS, GPIOIBE, GPIOEV, and GPIOIM registers to configure the type, event,
//    and mask of the interrupts for each port.
//    Note: To prevent false interrupts, the following steps should be taken when re-configuring
//    GPIO edge and interrupt sense registers:
//    a. Mask the corresponding port by clearing the IME field in the GPIOIM register.
//    b. Configure the IS field in the GPIOIS register and the IBE field in the GPIOIBE
//    register.
//    c. Clear the GPIORIS register.
//    d. Unmask the port by setting the IME field in the GPIOIM register.

    //a. Mask the corresponding port by clearing the IME field in the GPIOIM register.
       //GPIO_PORTF_IM_R=0x00;

    //b. Configure the IS field in the GPIOIS register and the IBE field in the GPIOIBE
    //register.
        //Register 3: GPIO Interrupt Sense (GPIOIS), offset 0x404 sy 664
        GPIO_PORTF_IS_R &=~(1<<4)|~(1<<0); // edge yaptýk - level yapmadýk pf0 ve pf4

        // Register 4: GPIO Interrupt Both Edges (GPIOIBE), offset 0x408 syf 665
        GPIO_PORTF_IBE_R &=~(1<<4)|~(1<<0); // pf0-pf4 için contolu GPIOIEV registerýna devrettim

        //Register 5: GPIO Interrupt Event (GPIOIEV), offset 0x40Csyf 666
        GPIO_PORTF_IEV_R &=~(1<<4)|~(1<<0);

        GPIO_PORTF_ICR_R |=(1<<4)|(1<<0); // temizledik
        // çalýþtýrýdm bir baktým kesmeye gidiyor.
        // kesmeleri temizleyelim dedik

    //c. Clear the GPIORIS register.
    // Register 7: GPIO Raw Interrupt Status (GPIORIS), offset 0x414 SYF 668
        GPIO_PORTF_RIS_R=0x00;


    //d. Unmask the port by setting the IME field in the GPIOIM register
        GPIO_PORTF_IM_R|=(1<<4)|(1<<0);

        // SETB EX0
     NVIC_EN0_R=0x40000000; // (1<<30)
             //0100 0000 0000 0000 0000 0000 0000 0000

    while(1)
    {

    }
}
