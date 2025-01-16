#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/gpio.c"
#include "inc/hw_memmap.h"

void SetInitSettings();

int main(void)
{
    SetInitSettings();
    // BASE ADRESS + 4*2^b // 4 çarpý 2 üzeri b
    // sadece 1 pin ile ugrasyýroum
    // GPIO_PORTF_BASE+ 4*2^1 = 0x40025008 -> bu bir registerdýr bu register 1 pin ile ugrasýr

    // amacýn 1 ve 3 pin ile ugrasmak isitoyurm
    // baseadress+ 4*(2^1)+ 4* (2^3)= 0x40025000+ 8 + 32 =

//    HWREG(0x40025008)=0x02;
    HWREG(0x40025028)=0x0a;

    // base adress + 4*2^0+4*2^1+4*2^2+4*2^3+4*2^4+4*2^5+4*2^6+4*2^7=40025000+4*255
    HWREG(0x400253FC);

}

void SetInitSettings()
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,255); // pin 123 output
}

