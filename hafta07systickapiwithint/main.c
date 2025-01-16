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

void PortInitSettings();
void SysTickInit();

void systickkesmefonk()
{
    a++;
    if(a==4)
    {
        GPIO_PORTF_DATA_R ^=0x04;
        a=0;
    }
}


int main(void)
{
    PortInitSettings();
    SysTickInit();

    while(1)
    {

    }
}

void PortInitSettings()
{
    //IntMasterEnable();
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); // 40 mhz
    long b=SysCtlClockGet();
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // SYSCTL_RCGCGPIO_R|=0x20;
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); // pin 123 output

    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_4); // pf4 input
    GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_4, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);// pull up için

    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0);
}

void SysTickInit(){
    SysTickDisable();
    SysTickPeriodSet( 10000000); // 0.25 sn
    //SysTickIntRegister(systickkesmefonk);
    SysTickIntEnable();
    SysTickEnable();
}

