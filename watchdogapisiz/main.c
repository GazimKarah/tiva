#include "stdint.h"
#include"inc/tm4c123gh6pm.h"

//apisiz

void wdt(void){
    GPIO_PORTF_DATA_R ^=0x04;
    WATCHDOG0_ICR_R=0x01;
    WATCHDOG0_LOAD_R =16000000-1;
}

int main(void)
{
    SYSCTL_RCGCGPIO_R|=0x20; // portf saat aktif

    GPIO_PORTF_LOCK_R = 0x4C4F434B; // commit aç
    GPIO_PORTF_CR_R = 0x01;   // pf0 da artýk konfigurasyn yapýlabilir. 0000 0001
                              // 0000 0001 -> pf0 artýk konfigure edilebilir

    GPIO_PORTF_DIR_R|=0x0E; // 0b 0000 1110 yönlendirme
    GPIO_PORTF_DEN_R|=0x1F; // 0b 0001 1111 pin aktifliði

    GPIO_PORTF_PUR_R = 0x11; // pf0 ve pf4 pull-up aktif 0001 0001
//    12.3 Initialization and Configuration
//    To use the WDT, its peripheral clock must be enabled by setting the Rn bit in the Watchdog Timer
//    Run Mode Clock Gating Control (RCGCWD) register, see page 337.
//    The Watchdog Timer is configured using the following sequence:
//    1. Load the WDTLOAD register with the desired timer load value.
//    2. If WDT1, wait for the WRC bit in the WDTCTL register to be set.
//    3. If the Watchdog is configured to trigger system resets, set the RESEN bit in the WDTCTL register.
//    4. If WDT1, wait for the WRC bit in the WDTCTL register to be set.
//    5. Set the INTEN bit in the WDTCTL register to enable the Watchdog, enable interrupts, and lock
//    the control register.
//    If software requires that all of the watchdog registers are locked, the Watchdog Timer module can
//    be fully locked by writing any value to the WDTLOCK register. To unlock the Watchdog Timer, write
//    a value of 0x1ACC.E551.
//    To service the watchdog, periodically reload the count value into the WDTLOAD register to restart
//    the count. The interrupt can be enabled using the INTEN bit in the WDTCTL register to allow the
//    processor to attempt corrective action if the watchdog is not serviced often enough. The RESEN bit
//    in WDTCTL can be set so that the system resets if the failure is not recoverable using the ISR.

    // 0. enerji wathdog
    SYSCTL_RCGCWD_R |=0x01;



    // 1. Load the WDTLOAD register with the desired timer load value.
    WATCHDOG0_LOAD_R=16000000-1;

    //    2. If WDT1, wait for the WRC bit in the WDTCTL register to be set.

    //    3. If the Watchdog is configured to trigger system resets, set the RESEN bit in the WDTCTL register.
    WATCHDOG0_CTL_R |=0x02; //WDT_CTL_RESEN

    //    4. If WDT1, wait for the WRC bit in the WDTCTL register to be set.

    //    5. Set the INTEN bit in the WDTCTL register to enable the Watchdog, enable interrupts, and lock
    //    the control register.

    WATCHDOG0_CTL_R |=0x01;
    WATCHDOG0_LOCK_R = 0x1ACCE551 ;
    int a=5;
    a=6;



    // syf 104
    NVIC_EN0_R|=(1<<18);

    while(1)
    {
        unsigned int value;
        value=GPIO_PORTF_DATA_R;


        if ((value & 0x10)==0)// pf4 için
        {
            while((GPIO_PORTF_DATA_R & 0x10)==0);

                GPIO_PORTF_DATA_R ^=0x08;

        }

        while ((value & 0x01)==0){}
    }
}
