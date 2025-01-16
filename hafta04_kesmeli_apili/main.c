#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.c"

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
// api li

int main(void)
{
    SetInitSettings();

    while(1)
    {

    }


}

void SetInitSettings()
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // SYSCTL_RCGCGPIO_R|=0x20;
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
    portfkesmeaktifhale();

    // 3 tane lokal
    GPIOIntTypeSet(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_4, GPIO_FALLING_EDGE); // düþen kenar kesmesi
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4); // pin 4 ile kesme aktif
    GPIOIntRegister(GPIO_PORTF_BASE, haricikesme);
}

void portfkesmeaktifhale(){

    NVIC_EN0_R=0x40000000;
}
