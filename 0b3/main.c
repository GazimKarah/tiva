#include <stdint.h>
#include <stdbool.h>
#include "utils/ustdlib.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/hibernate.h"
#include "driverlib/gpio.h"

void hiberkesme(){
     uint32_t deger = HibernateIntStatus(1);
     HibernateIntClear(deger);
     GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 2);
     SysCtlDelay(20000000);
     GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);

     HibernateRTCMatchSet(0,HibernateRTCGet()+5);
}

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x08);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE);
    HibernateEnableExpClk(SysCtlClockGet());
    HibernateGPIORetentionEnable();
    SysCtlDelay(64000000);
    HibernateRTCSet(0);
    HibernateRTCEnable();
    HibernateRTCMatchSet(0,5);
    HibernateWakeSet(HIBERNATE_WAKE_RTC);
    HibernateIntRegister(hiberkesme);
    HibernateIntEnable(HIBERNATE_INT_RTC_MATCH_0);
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3, 0x00);
    HibernateRequest();


while(1)
{

}
}
