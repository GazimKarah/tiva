#include "stdint.h"
#include"inc/tm4c123gh6pm.h"

//apisiz

long a=0;

int main(void)
{
    SYSCTL_RCGCGPIO_R|=0x20; // portf saat aktif

    GPIO_PORTF_LOCK_R = 0x4C4F434B; // commit aç
    GPIO_PORTF_CR_R = 0x01;   // pf0 da artýk konfigurasyn yapýlabilir. 0000 0001
                              // 0000 0001 -> pf0 artýk konfigure edilebilir

    GPIO_PORTF_DIR_R |=0x0E; // 0b 0000 1110 yönlendirme
    GPIO_PORTF_DEN_R |=0x1F; // 0b 0001 1111 pin aktifliði

    GPIO_PORTF_PUR_R = 0x11; // pf0 he pf4 pull-up aktif 0001 0001

    //Table 11-12. Timers Register Map syf 736


    // To use a GPTM, the appropriate TIMERn bit must be set in the RCGCTIMER
//    Register 59: 16/32-Bit General-Purpose Timer Run Mode Clock Gating Control
//    (RCGCTIMER), offset 0x604
    SYSCTL_RCGCTIMER_R |=0x01; //(1<<0)
    //SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

//    1. Ensure the timer is disabled (the TnEN bit in the GPTMCTL register is cleared) before making
//    any changes

    TIMER0_CTL_R &=0xFE; // 1
    //TIMER0_CTL_R = ~(1<<0); //
    // alt + 0126

    //2. Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000
    TIMER0_CFG_R=0x04; // 16bit


//    3. Configure the TnMR field in the GPTM Timer n Mode Register (GPTMTnMR):
//    a. Write a value of 0x1 for One-Shot mode.
//    b. Write a value of 0x2 for Periodic mode.
    TIMER0_TAMR_R |=0x02; // 0000 0010 |(1<<1)  PERÝODÝK


//    4. Optionally configure the TnSNAPS, TnWOT, TnMTE, and TnCDIR bits in the GPTMTnMR register
//    to select whether to capture the value of the free-running timer at time-out, use an external
//    trigger to start counting, configure an additional trigger or interrupt, and count up or down.
    TIMER0_TAMR_R &=0xEF;// 1110 1111   ~(1<<4) COUNT DOWN


    // 5. Load the start value into the GPTM Timer n Interval Load Register (GPTMTnILR)
    // Peki bizim saatimiz þu anda kaç mhz 16 000 000

    TIMER0_TAILR_R= 49999; // 16000000 1 sn istedim // ilk deger

    //7. Set the TnEN bit in the GPTMCTL register to enable the timer and start counting.
    TIMER0_CTL_R |=0x01; // zamanlayýcý baþladý

    while(1)
    {
//        Poll the GPTMRIS register or wait for the interrupt to be generated (if enabled). In both cases,
//        the status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear
//        Register (GPTMICR).
        if ((TIMER0_RIS_R & 0x01)==1)
        {
            a++;
            TIMER0_ICR_R |=0x01; // clear flag
            if(a==320)//320 kez taþýnca 1 sn
            {
                // buraya girmiþse timeout olmuþtur

                GPIO_PORTF_DATA_R ^=0x02; // toggle
                GPIO_PORTF_DATA_R ^=0x04; // toggle
                a=0;
            }
        }
    }
}
