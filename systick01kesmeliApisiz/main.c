#include "stdint.h"
#include"inc/tm4c123gh6pm.h"

void portinit();
void systickinit();
void SysTick_Handler(void);
//void enable_irq(void);

int main(void)
{
    portinit();
    systickinit();
    //enable_irq();

    while(1){

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
    NVIC_ST_RELOAD_R=15999999; // başlangıç değeri
    NVIC_ST_CURRENT_R=0; // sayıcının değeri
    NVIC_ST_CTRL_R=(1<<2)|(1<<1)|(1<<0); // saat sectik ve enable aktif
}

void SysTick_Handler(void){
    GPIO_PORTF_DATA_R ^=0x04;
}

/* global enable interrupts */
//void inline enable_irq(void)
//{
//    __asm  ("    CPSIE  I\n");
//}
//System Timer (SysTick)
//Cortex-M4 includes an integrated system timer, SysTick, which provides a simple, 24-bit
//clear-on-write, decrementing, wrap-on-zero counter with a flexible control mechanism. The counter
//can be used in several different ways


//16.777.216 = 24bit

//The timer consists of three registers:
//■ SysTick Control and Status (STCTRL): A control and status counter to configure its clock,
//enable the counter, enable the SysTick interrupt, and determine counter status.

//■ SysTick Reload Value (STRELOAD): The reload value for the counter, used to provide the
//counter's wrap value.

//■ SysTick Current Value (STCURRENT): The current value of the counter.


//When enabled, the timer counts down on each clock from the reload value to zero, reloads (wraps)
//to the value in the STRELOAD register on the next clock edge, then decrements on subsequent
//clocks. Clearing the STRELOAD register disables the counter on the next wrap. When the counter
//reaches zero, the COUNT status bit is set. The COUNT bit clears on reads.

//Writing to the STCURRENT register clears the register and the COUNT status bit. The write does
//not trigger the SysTick exception logic. On a read, the current value is the value of the register at
//the time the register is accessed.
//The SysTick counter runs on either the system clock or the precision internal oscillator (PIOSC)
//divided by 4. If this clock signal is stopped for low power mode, the SysTick counter stops. SysTick
//can be kept running during Deep-sleep mode by setting the CLK_SRC bit in the SysTick Control
//and Status Register (STCTRL) register and ensuring that the PIOSCPD bit in the Deep Sleep
//Clock Configuration (DSLPCLKCFG) register is clear. Ensure software uses aligned word accesses
//to access the SysTick registers.

//The SysTick counter reload and current value are undefined at reset; the correct initialization
//sequence for the SysTick counter is:

//1. Program the value in the STRELOAD register.
//2. Clear the STCURRENT register by writing to it with any value.
//3. Configure the STCTRL register for the required operation.
//Note: When the processor is halted for debugging, the counter does not decrement.
