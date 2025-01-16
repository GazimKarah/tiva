#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.c"
#include "driverlib/timer.h"
#include "driverlib/timer.c"
#include "driverlib/interrupt.h"

#include "inc/tm4c123gh6pm.h"

int a=0;

void SetInitSettings();
void timerkesmefonksiyonu();
void timeraktifhalegetir(){
    SYSCTL_RCGCTIMER_R |=0x01; //(1<<0)
}

// api li

int main(void)
{
    SetInitSettings(); // ilk yaaralarmýzý

    while(1)
    {

    }


}

void SetInitSettings()
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); // 40mhz

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // SYSCTL_RCGCGPIO_R|=0x20;
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); // pin 123 output

    // asagidaki 3 kod portf'in 0 nolu pinini lock özelliðini kapatýyor.
    // bu kod olmazsa portf,pin0 okuma fonksiyonu asagiða çalýþmaz.
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;

//    GPIO_PORTF_LOCK_R = 0x4C4F434B; // commit aç
//    GPIO_PORTF_CR_R = 0x01;   // pf0 da artýk konfigurasyn yapýlabilir. 0000 0001
//                              // 0000 0001 -> pf0 artýk konfigure edilebilir

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_4); // pf4 input
    GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_4, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);// pull up için

    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0);

    // timer ayarlarý
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_PERIODIC); // 16 bitlik sayýcý
    TimerLoadSet(TIMER0_BASE, TIMER_A, 25000-1); // 40 000 000 1 sn için

    // 2 global
    IntMasterEnable();
    IntEnable(INT_TIMER0A);

    // 3yerel interrupt ayarlari
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT); // bayrak temizlendi
    TimerIntRegister(TIMER0_BASE, TIMER_A, timerkesmefonksiyonu);

    TimerEnable(TIMER0_BASE, TIMER_A); // setb tr0
}

void timerkesmefonksiyonu()
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT); // bayrak temizlendi
    a++;

    if (a==800)
    {
        if (GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_2))
        {
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,0);
        }
        else
        {
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,4);
        }
        a=0;
    }

}
