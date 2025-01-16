#include "stdint.h"
#include"inc/tm4c123gh6pm.h"

void portinit();
void systickinit();
void saatayar(); // rcc
void saatayar2(); //rcc2 kullanarak
void PLL_Init(void); //volvano nun
void saatayar3direkt();

int main(void)
{
    //PLL_Init();
    saatayar();
    saatayar3direkt();
    portinit();
    systickinit();
    int a=0;
    while(1){
        if (NVIC_ST_CTRL_R & 0x10000)
        {
            a++;
            if (a==8)
            {
                GPIO_PORTF_DATA_R ^=0x04;
                a=0;
            }
        }
    }
}

void portinit(){
    SYSCTL_RCGCGPIO_R|=0x20; // portf saat aktif

    GPIO_PORTF_LOCK_R = 0x4C4F434B; // commit aç
    GPIO_PORTF_CR_R = 0x01;   // pf0 da artık konfigurasyn yapılabilir. 0000 0001
                              // 0000 0001 -> pf0 artık konfigure edilebilir

    GPIO_PORTF_DIR_R|=0x0E; // 0b 0000 1110 yönlendirme
    GPIO_PORTF_DEN_R|=0x1F; // 0b 0001 1111 pin aktifliği

    GPIO_PORTF_PUR_R = 0x11; // pf0 ve pf4 pull-up aktif 0001 0001
}

void systickinit(){
    NVIC_ST_CTRL_R=0;  // ilk biti=0 yaparsak disable
    NVIC_ST_RELOAD_R=10000000-1; // başlangıç değeri
    NVIC_ST_CURRENT_R=0; // sayıcının değeri
    NVIC_ST_CTRL_R=(1<<2)|(1<<0); // saat sectik ve enable aktif
}

void PLL_Init(void){

  // 0) Use RCC2

  SYSCTL_RCC2_R |=  0x80000000;  // USERCC2
  SYSCTL_RCC2_R |=  0x00000800;  // BYPASS2, PLL bypass
  SYSCTL_RCC_R = (SYSCTL_RCC_R &~0x000007C0)   // clear XTAL field, bits 10-6
                 + 0x00000540;   // 10101, configure for 16 MHz crystal
  SYSCTL_RCC2_R &= ~0x00000070;  // configure for main oscillator source
  SYSCTL_RCC2_R &= ~0x00002000;
  SYSCTL_RCC2_R |= 0x40000000;   // use 400 MHz PLL
  SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~ 0x1FC00000)  // clear system clock divider
                  + (4<<22);      // configure for 80 MHz clock
  while((SYSCTL_RIS_R&0x00000040)==0){};  // wait for PLLRIS bit
  SYSCTL_RCC2_R &= ~0x00000800;

}

void saatayar2(){ // syf 231
    // 5.2.5.5 Main PLL Frequency Configuration syf 225
    //The modes are programmed using the RCC/RCC2 register fields (see page 254 and page 260).
    // 0) Set USERCC2 bit in order to use RCC2,
    // 0) use RCC2 because it provides for more options.
    SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2; //0x80000000

    // 1) Set the BYPASS bit to bypass PLL while initializing.
    // 1) The first step is to set BYPASS2 (bit 11).
    // At this point the PLL is bypassed and there is no system clock divider.
    SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2; //0x00000800

    // 2) Clear and set the XTAL bits to 16MHz
    // 2) select the crystal value and oscillator source

    //SYSCTL_RCC_R = (SYSCTL_RCC_R &~0x000007C0)   // clear XTAL field, bits 10-6
    //               + 0x00000540;   // 10101, configure for 16 MHz crystal
    SYSCTL_RCC_R = ((SYSCTL_RCC_R & ~SYSCTL_RCC_XTAL_M) + SYSCTL_RCC_XTAL_16MHZ);

    // 3)   Clear the OSCSRC2 bits to configure for Main OSC
    //SYSCTL_RCC2_R &= ~0x00000070;  // configure for main oscillator source
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;

    // 4) Activate PLL by clearing PWRDN.
    // this step is to clear PWRDN2 (bit 13) to activate the PLL.
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;

    // 5) Use 400 MHz PLL - div400 =1 oldu
    SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400 ;

    // 6) Clear the SYSDIV2 bits and set to 0x4 = 80MHz
//    SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~ 0x1FC00000)  // clear system clock divider
//                    + (4<<22);      // configure for 80 MHz clock
    SYSCTL_RCC2_R = (SYSCTL_RCC2_R & ~(SYSCTL_RCC2_SYSDIV2_M | SYSCTL_RCC2_SYSDIV2LSB)) + (4 << 22);

    // 7) Wait for the PLL to lock ,   wait for the PLL to lock by polling PLLLRIS
    while ((SYSCTL_RIS_R & SYSCTL_RIS_PLLLRIS) == 0)
    {
    }

    // 8) Clear BYPASS to enable PLL.
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;
}
void saatayar(){
    // 0)
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_USERCC2; //0x80000000

    // 1) Set the BYPASS bit to bypass PLL while initializing.
    // 1) The first step is to set BYPASS2 (bit 11).
    // At this point the PLL is bypassed and there is no system clock divider.
    SYSCTL_RCC_R |= SYSCTL_RCC_BYPASS; //0x00000800

    // 2) Clear and set the XTAL bits to 16MHz
    // 2) select the crystal value and oscillator source

    //SYSCTL_RCC_R = (SYSCTL_RCC_R &~0x000007C0)   // clear XTAL field, bits 10-6
    //               + 0x00000540;   // 10101, configure for 16 MHz crystal
    SYSCTL_RCC_R = ((SYSCTL_RCC_R & ~SYSCTL_RCC_XTAL_M) | SYSCTL_RCC_XTAL_16MHZ);

    // 3)   Clear the OSCSRC2 bits to configure for Main OSC
    //SYSCTL_RCC_R &= ~0x00000030;  // configure for main oscillator source
    SYSCTL_RCC_R &= ~SYSCTL_RCC_OSCSRC_M;

    // 4) Activate PLL by clearing PWRDN.
    // this step is to clear PWRDN (bit 13) to activate the PLL. 0x00002000
    SYSCTL_RCC_R &= ~SYSCTL_RCC_PWRDN;

    // 5) Use 400 MHz PLL - div400 =0 oldu
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_DIV400 ;


    // 6) Clear the SYSDIV2 bits and set to 0x4 = 40MHz
//    SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~ 0x07800000)  // clear system clock divider
//                    + (4<<22);      // configure for 40 MHz clock
    //SYSCTL_RCC_R = (SYSCTL_RCC_R & ~((SYSCTL_RCC_SYSDIV_M) | SYSCTL_RCC_USESYSDIV)) + (4 << 22);
    SYSCTL_RCC_R &=~SYSCTL_RCC_SYSDIV_M; //07800000 clear yaptım sysdiv bölgesinin
    SYSCTL_RCC_R |=SYSCTL_RCC_USESYSDIV + (4 << 22); // div var

    // 7) Wait for the PLL to lock ,   wait for the PLL to lock by polling PLLLRIS
    while ((SYSCTL_RIS_R & SYSCTL_RIS_PLLLRIS) == 0)
    {
    }

    // 8) Clear BYPASS to enable PLL.
    SYSCTL_RCC_R &= ~SYSCTL_RCC_BYPASS;

}

void saatayar3direkt(){
    SYSCTL_RCC2_R &= ~0xC0000000;   // usercc2=0 yani rcc registerı kullanılacak
                                    // div400=0 yani 2 ye  bölünecek
    SYSCTL_RCC_R &= 0xF83FD00F;
    SYSCTL_RCC_R |= 0X02400D40;

    SYSCTL_RCC_R &= ~0x00000800;
}
