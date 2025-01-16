#include "stdint.h"
#include"inc/tm4c123gh6pm.h"

void PortF_Init(void);

int main(void)
{
    PortF_Init();    // make PF3-1 out (PF3-1 built-in LEDs)

    while(0){
//
//      In = GPIO_PORTF_DATA_R&0x10;   // read PF4 into Sw1
//      In = In>>2;                    // shift into position PF2
//      Out = GPIO_PORTF_DATA_R;
//      Out = Out&0xFB;
//      Out = Out|In;
//      GPIO_PORTF_DATA_R = Out;        // output
    }

    while(1){
        unsigned long In;  // input from PF4
        unsigned long Out; // output to PF2 (blue LED)
        In=GPIO_PORTF_DATA_R;
        char c1=In&0x10;//sw1 pf4
        char c2=In&0x01;
        int a=3;
        if (c2==0){
            GPIO_PORTF_DATA_R|=0x02;
        }

    }
}


void PortF_Init(void){

  volatile unsigned long delay;

  SYSCTL_RCGC2_R |= 0x00000020;     // 1) activate clock for Port F
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
  // only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 in, PF3-1 out
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
  GPIO_PORTF_PUR_R = 0x11;          // enable pull-up on PF0 and PF4
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital I/O on PF4-0

}
