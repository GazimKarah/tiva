#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.c"
#include "driverlib/adc.h"
#include "inc/tm4c123gh6pm.h"

void SetInitSettings();


int main(void)
{
    SetInitSettings();
    uint32_t temp;
    while(1){
        ADCProcessorTrigger(ADC0_BASE, 1); // yazýlýmla tetikliyorum
        // adc örnkeleri almaya basladý

        //ADCIntStatus(ADC0_BASE, 1, true)=1 gelirse adc çevrim iþlemini bitirmiþ olur

         while(!ADCIntStatus(ADC0_BASE, 1, false)){} // burada bekliyoruz

         uint32_t gelendata[4];
         // buraya gelmiþse sequence 1 den 4 kanaldan bilgi gelmiþ olur
         ADCSequenceDataGet(ADC0_BASE, 1, gelendata);

         uint32_t ortalamadeger=(gelendata[0]+gelendata[1]+gelendata[2]+gelendata[3])/4;

         temp=(1475-((2475*ortalamadeger)/4096))/10;
    }
}

void SetInitSettings()
{
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); //50mhz
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // SYSCTL_RCGCGPIO_R|=0x20;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0); // ADC HAYAT=1

    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0); /// adc0 kullan ve sequence 1 seç

    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_TS); // sýcaklýk sensörü seçildi
    ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_TS);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_TS);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 3, ADC_CTL_TS|ADC_CTL_IE|ADC_CTL_END);

    ADCSequenceEnable(ADC0_BASE, 1); // adc ayarlanmasý bitti
    // daha adc calýþmaya baslamadý

}
