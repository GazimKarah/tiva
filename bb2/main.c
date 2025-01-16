#include "stdint.h"
#include"inc/tm4c123gh6pm.h"

//apisiz

int main(void)
{
    // default saat ne
    //Register 10: Run-Mode Clock Configuration 2 (RCC2), offset 0x070 syf 260
    // burada 0. bite bak default value 0x01
    // PIOSC

    // sonra 59 sayfaya bak piosc nedir diye
    // – Precision Internal Oscillator (PIOSC) providing a 16-MHz frequency

    SYSCTL_RCGCGPIO_R |= 0x20; // portf saat aktif (1<<5)

    GPIO_PORTF_LOCK_R = 0x4C4F434B; // commit aç
    GPIO_PORTF_CR_R = 0x01;   // pf0 da artýk konfigurasyn yapýlabilir. 0000 0001
                              // 0000 0001 -> pf0 artýk konfigure edilebilir

    GPIO_PORTF_AFSEL_R = 0x00;
    GPIO_PORTF_DIR_R |= 0x0E; // 0b 0000 1110 yönlendirme
    GPIO_PORTF_DEN_R |= 0x1F; // 0b 0001 1111 pin aktifliði
    GPIO_PORTF_PUR_R = 0x11; // pf0 ve pf4 pull-up aktif 0001 0001

//  Table 11-12. Timers Register Map sys 726


    //SYSCTL_RCGC1_TIMER0 |=0x01; // timer0 saat darbesi
    //SYSCTL_RCGCTIMER_R
    SYSCTL_RCGCTIMER_R |= 0x01;
    //1. Ensure the timer is disabled (the TnEN bit in the GPTMCTL register is cleared) before making any changes
    TIMER0_CTL_R &= 0xFE;  //sys 737 Register 4: GPTM Control (GPTMCTL), offset 0x00C
                           // 1111 1110 ile andledik timerA disable

    //2. Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000
                        //Register 1: GPTM Configuration (GPTMCFG), offset 0x000
                        //This register configures the global operation of the GPTM module. The value written to this register
                        //determines whether the GPTM is in 32- or 64-bit mode (concatenated timers) or in 16- or 32-bit
                        //mode (individual, split timers)
    TIMER0_CFG_R = 0x00;  //Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000.

    //    For a 16/32-bit timer, this value selects the 32-bit timer
    //    configuration.
    //    For a 32/64-bit wide timer, this value selects the 64-bit timer
    //    configuration.


    //3. Configure the TnMR field in the GPTM Timer n Mode Register (GPTMTnMR):
    TIMER0_TAMR_R |= 0x02; // periodik- syf 729 Register 2: GPTM Timer A Mode (GPTMTAMR), offset 0x004
    //b. Write a value of 0x2 for Periodic mode.

    //4. Optionally configure the TnSNAPS, TnWOT, TnMTE, and TnCDIR bits in the GPTMTnMR register
    TIMER0_TAMR_R &= 0xEF; ; //tmr 4 bit count down, o zmn 11101111

    //5. Load the start value into the GPTM Timer n Interval Load Register (GPTMTnILR).
    TIMER0_TAILR_R = 0x00F42400; // bu deger 16 000 000

    //7. Set the TnEN bit in the GPTMCTL register to enable the timer and start counting.
    TIMER0_CTL_R |= 0x01;

    while(1)
    {
//      8. Poll the GPTMRIS register or wait for the interrupt to be generated (if enabled). In both cases,
//      the status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear
//      Register (GPTMICR).
        //Register 7: GPTM Raw Interrupt Status (GPTMRIS), offset 0x01C
        if (TIMER0_RIS_R & 0x01 == 1 )
        {
            TIMER0_ICR_R |= 0x01;
            GPIO_PORTF_DATA_R ^= 0x02;
        }


    }
}
