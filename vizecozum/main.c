#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.c"
#include "math.h"

void SetInitSettings();
void haricikesme(void)
{
    // ÇÖZÜM 3 DEVAMI
    int a=GPIOIntStatus(GPIO_PORTA_BASE, true); // eðer burdan hangi pinden 1 gelmiþsse kesme oluþmuþtu
    if(a==1) // pf4 basýlmýþtýr
    {
        GPIOPinWrite(GPIO_PORTB_BASE, 1|4|16|64, GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_6);
    }
    else if (a==2) // pf0 basýlmýþtýr
    {
        GPIOPinWrite(GPIO_PORTB_BASE, 2|8|32|128, GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_7);
    }


    GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4);

    // ÇÖZÜM 3 BÝTTÝ

}
// api li

int main(void)
{
    SetInitSettings();

    while(1)
    {
        //SSORU 2 ÇÖZÜM

        if (GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_0)==0)
        {
            while(GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_0)==0); // butondan cekme komutu
            GPIOPinWrite(GPIO_PORTB_BASE, 1|4|16|64, GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_6);
            // sýrayla sadece çift numralarý ledleri yakýnýz.
        }
        else if (GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_1)==0){
            while(GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_1)==0); // butondan cekme komutu
            GPIOPinWrite(GPIO_PORTB_BASE, 2|8|32|128, GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_7);
            // sýrayla sadece çift numralarý ledleri yakýnýz.
        }
        //SORU 2 BÝTTÝ

        // SORU 4
        if ( HWREG(GPIO_PORTA_BASE+4*1)==0)
        {
            while(HWREG(GPIO_PORTA_BASE+4*1)==0); // butondan cekme komutu
            HWREG(GPIO_PORTA_BASE+4*(1|4|16|64))==85;
            // sýrayla sadece çift numralarý ledleri yakýnýz.
        }
        else if (HWREG(GPIO_PORTA_BASE+4*2)==0){
            while(HWREG(GPIO_PORTA_BASE+4*1)==0); // butondan cekme komutu
            HWREG(GPIO_PORTB_BASE+4*(2|8|32|128))=170;
            // sýrayla sadece çift numralarý ledleri yakýnýz.
        }
        //SORU 4 ÜN BÝTTÝ

    }


}

void SetInitSettings()
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    //SORU 1 ÇÖZÜM
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,255);
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE,GPIO_PIN_0|GPIO_PIN_1);
    GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_1, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);// pull up için
    // SORU 1 ÇÖZÜM BÝTTÝ

    // SORU 3 ÇÖZÜM
    // interrupt kesme  gpio
    IntMasterEnable(); // setb ea
    IntEnable(INT_GPIOA); // portf kesmesi pin kesmesi yok
//    portfkesmeaktifhale();
//
//    // 3 tane lokal
    GPIOIntTypeSet(GPIO_PORTA_BASE,GPIO_PIN_0|GPIO_PIN_1, GPIO_FALLING_EDGE); // düþen kenar kesmesi
    GPIOIntEnable(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1); // pin 4 ile kesme aktif
    GPIOIntRegister(GPIO_PORTA_BASE, haricikesme);
    // SORU 3 ÇÖZÜM
}

void portfkesmeaktifhale(){


}
