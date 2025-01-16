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
uint32_t value[1];

void adckesme(){
    ADCIntClear(ADC0_BASE,3); // bayragý temizledik

    ADCSequenceDataGet(ADC0_BASE,3, value);

    ADCProcessorTrigger(ADC0_BASE, 3); // yazýlýmla tetikliyorum
}

int main(void)
{
    SetInitSettings();

    while(1){


    }
}

void SetInitSettings()
{
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); //50mhz
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // SYSCTL_RCGCGPIO_R|=0x20;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0); // ADC HAYAT=1

    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0); /// adc0 kullan ve sequence 1 seç

    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0|ADC_CTL_IE|ADC_CTL_END);

    ADCSequenceEnable(ADC0_BASE, 3); // adc ayarlanmasý bitti
    // daha adc calýþmaya baslamadý

    IntMasterEnable();
    IntEnable(INT_ADC0SS3);

    ADCIntClear(ADC0_BASE, 3);
    ADCIntRegister(ADC0_BASE, 3, adckesme);
    ADCIntEnable(ADC0_BASE, 3);
    ADCProcessorTrigger(ADC0_BASE, 3); // yazýlýmla tetikliyorum

}
