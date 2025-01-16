#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.c"
#include "driverlib/hibernate.h"

void SetInitSettings();
void haricikesme(void)
{

    int a=GPIOIntStatus(GPIO_PORTF_BASE, true); // eðer burdan hangi pinden 1 gelmiþsse kesme oluþmuþtu
    if(a==16) // pf4 basýlmýþtýr
    {
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,2);
    }
    else if (a==1) // pf0 basýlmýþtýr
    {
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,4);
    }

    GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4);

}


int main(void)
{
    SetInitSettings();

    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,8);
    SysCtlDelay(80000000);
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0);

    HibernateRequest();


    while(1)
    {

    }


}

void SetInitSettings()
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // SYSCTL_RCGCGPIO_R|=0x20;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE);

    // 1 saati bilmesi gerekiyor
    HibernateEnableExpClk(SysCtlClockGet());
    HibernateGPIORetentionEnable(); // 2 bu uyudugunda gpio nun yetkilendirilemsi

    SysCtlDelay(1000000*1.33);
    HibernateRTCSet(0);

    HibernateRTCEnable();
    HibernateRTCMatchSet(0, 4); // 6 sn

    HibernateWakeSet(HIBERNATE_WAKE_PIN|HIBERNATE_WAKE_RTC); // 3. nasýl uyanacagým þu anda sabit olarak pf0

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); // pin 123 output

    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_4); // pf4 input
    GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_4, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);// pull up için

    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0);

    // interrupt kesme  gpio
    // 5 tane fonksiyon
    // 2 tane global 3 tane local
    IntMasterEnable(); // setb ea
    IntEnable(INT_GPIOF); // portf kesmesi pin kesmesi yok

    // 3 tane lokal
    GPIOIntTypeSet(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_4, GPIO_FALLING_EDGE); // düþen kenar kesmesi
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4); // pin 4 ile kesme aktif
    GPIOIntRegister(GPIO_PORTF_BASE, haricikesme);
}

