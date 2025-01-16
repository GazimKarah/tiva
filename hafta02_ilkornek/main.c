#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/gpio.c"
#include "inc/hw_memmap.h"
#include "math.h"

// deklarasyon
void SetInitSettings();
double ustal(int p1, int p2);
double IkininUssuAl(int p2);
void PortFninXPiniEnerjilendir(int pin);
void PortXPiniSet(double port, int pin,int value);

int ilkSayi=0;

void main(void)
{
    //ilk ayarlar
    SetInitSettings();

    while(1) // ana döngü
    {

        int k=2; // baþlangýç deðeri
        while(0) // þart
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,k);
            k=k*2; // artým
            if (k==16)
            {
                k=2;
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,2);
            }
        }

        while(0)
        {
            int x;
            for (x=1;x<4;x++)
            {
                int pins=pow(2,x);
                int value=pow(2,x);

                GPIOPinWrite(GPIO_PORTF_BASE, pins ,value);
                SysCtlDelay(20000000);
                GPIOPinWrite(GPIO_PORTF_BASE, ustal(2,x) ,0);
                SysCtlDelay(20000000);
            }
        }

        while(1)
        {
            PortXPiniSet(GPIO_PORTF_BASE, 2, 4); // 2. pini
        }
    }
}

void SetInitSettings()
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); // pin 123 output
}

double ustal(int p1, int p2)
{
    double carpim=1;
    int i;
    for (i=1;i<p2+1;i++)
    {
        carpim=carpim*p1;
    }
    return carpim;
}

double IkininUssuAl(int p2)
{
    double carpim=1;
    int i;
    for (i=1;i<p2+1;i++)
    {
        carpim=carpim*2;
    }

    return carpim;
}


void PortfBirinciLediniSondur()
{
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
}

void PortFninXPiniEnerjilendir(int pin)
{
    GPIOPinWrite(GPIO_PORTF_BASE, pow(2,pin), pow(2,pin));
}

void PortFninXPiniSet(int pin,int value)
{
    GPIOPinWrite(GPIO_PORTF_BASE, pow(2,pin), value);
}

void PortXPiniSet(double port, int pin,int value)
{
    GPIOPinWrite(port, pow(2,pin), value);
}
