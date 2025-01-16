#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.c"
#include "driverlib/systick.h"
#include "driverlib/systick.c"
#include "inc/tm4c123gh6pm.h"

int a=0;

void SetInitSettings();
void SysTickInit();
void SysTick_IntHandler(){
     a++;
     if (a==4)
     {
         GPIO_PORTF_DATA_R ^=0x08;
         a=0;
     }
}

bool systicintcontrol();
// api li

int main(void)
{
    SetInitSettings();
    SysTickInit();

    while(1)
    {

    }


}

void SetInitSettings()
{
    IntMasterEnable();
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    //SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |SYSCTL_XTAL_16MHZ);
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
}

void SysTickInit(){
    SysTickDisable();
    SysTickPeriodSet(5000000);
    SysTickIntRegister(SysTick_IntHandler);
    SysTickIntEnable();
    SysTickEnable();
}

bool systicintcontrol(){
    return (NVIC_ST_CTRL_R & 0x10000);
}
