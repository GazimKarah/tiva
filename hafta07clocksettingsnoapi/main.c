#include "stdint.h"
#include"inc/tm4c123gh6pm.h"

//apisiz

void clockinit();
void clockinit2();

int main(void)
{
    clockinit();
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

void clockinit(){
//    Initialization and Configuration
//    The PLL is configured using direct register writes to the RCC/RCC2 register. If the RCC2 register
//    is being used, the USERCC2 bit must be set and the appropriate RCC2 bit/field is used. The steps
//    required to successfully change the PLL-based system clock are:
//    1. Bypass the PLL and system clock divider by setting the BYPASS bit and clearing the USESYS
//    bit in the RCC register, thereby configuring the microcontroller to run off a "raw" clock source
//    and allowing for the new PLL configuration to be validated before switching the system clock
//    to the PLL.
//    2. Select the crystal value (XTAL) and oscillator source (OSCSRC), and clear the PWRDN bit in
//    RCC/RCC2. Setting the XTAL field automatically pulls valid PLL configuration data for the
//    appropriate crystal, and clearing the PWRDN bit powers and enables the PLL and its output.
//    3. Select the desired system divider (SYSDIV) in RCC/RCC2 and set the USESYS bit in RCC. The
//    SYSDIV field determines the system frequency for the microcontroller.
//    4. Wait for the PLL to lock by polling the PLLLRIS bit in the Raw Interrupt Status (RIS) register.
//    5. Enable use of the PLL by clearing the BYPASS bit in RCC/RCC2.

    // SYSCTL_RCC2_R &= 7FFFFFFF;
    // SYSCTL_RCC2_R & = ~80000000;
    SYSCTL_RCC2_R = ~SYSCTL_RCC2_USERCC2;

    SYSCTL_RCC_R |=  SYSCTL_RCC_BYPASS;
    // 800 -> 1000 0000 0000

    //2.SYSCTL_RCC_R &= 0xFFFFF830
    // SYSCTL_RCC_R + 0x00000540
    SYSCTL_RCC_R = (SYSCTL_RCC_R & ~SYSCTL_RCC_XTAL_M) + SYSCTL_RCC_XTAL_16MHZ;

    //SYSCTL_RCC_R &= 0xCF; //oscscr 00
    SYSCTL_RCC_R &= ~SYSCTL_RCC_OSCSRC_M;
    SYSCTL_RCC_R &= ~SYSCTL_RCC_PWRDN; //pwrdwn o yaptýk artýk pll devrede olacak
    // ilk önce div400 0 yap
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_DIV400;

    //SYSCTL_RCC_R = (SYSCTL_RCC_R & ~0x07800000)+ (4<<22);
    SYSCTL_RCC_R & = ~SYSCTL_RCC_SYSDIV_M;
    SYSCTL_RCC_R |= SYSCTL_RCC_USESYSDIV + (4<<22); // 16 mhz
    //4.
    while ( SYSCTL_RIS_R & SYSCTL_RIS_PLLLRIS==0  );

    SYSCTL_RCC_R &= ~ SYSCTL_RCC_BYPASS;
}

void clockinit2(){
    SYSCTL_RCC2_R = SYSCTL_RCC2_USERCC2; // artik rcc2 registere devrede

    SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;

    //2.SYSCTL_RCC_R &= 0xFFFFF830
    // SYSCTL_RCC_R + 0x00000540
    SYSCTL_RCC_R = (SYSCTL_RCC_R & ~SYSCTL_RCC_XTAL_M) + SYSCTL_RCC_XTAL_16MHZ;

    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;

    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;
    // ilk önce div400 0 yap 2 böl
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_DIV400;



    SYSCTL_RCC2_R = (SYSCTL_RCC2_R &  ~SYSCTL_RCC2_SYSDIV2_M)+(4<<22);


    while ( SYSCTL_RIS_R & SYSCTL_RIS_PLLLRIS==0  );

    SYSCTL_RCC_R &= ~ SYSCTL_RCC_BYPASS;
}


