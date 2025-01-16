#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.c"
#include "driverlib/timer.h"
#include "driverlib/timer.c"
#include "driverlib/interrupt.h"
#include "driverlib/adc.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "inc/tm4c123gh6pm.h"

void SetInitSettings();
void saatkontrol();
void PCyesaatgonder();
void PCyeistediginbirmesaj();
void adcseridengonder(int deger);
uint32_t kesme;
uint32_t a;

/* sadizisi=*/
int saatdizi[8]={1, 2,10 ,3, 4, 10, 5, 6};
uint32_t adcdata[4];

int gelenveri;
bool saatmi=false;
int gelensaatno;

int main(void)
{
    SetInitSettings(); // ilk yaaralarmýzý

    int a=2;

    while(1)
    {
        kesme=TimerIntStatus(TIMER0_BASE, true);
        if (kesme!=0){
            TimerIntClear(TIMER0_BASE, kesme);

            if (GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_1))
            {
                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0);
            } else
            {
                GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,2);
            }
            saatkontrol();
            PCyesaatgonder();
            ADCProcessorTrigger(ADC0_BASE, 1); // her 1 sn de basladý
        }

        if (GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4)==0){
           // while(GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4)==0);
            PCyeistediginbirmesaj();
        }

        if(ADCIntStatus(ADC0_BASE, 1, false)){
            ADCIntClear(ADC0_BASE, 1);
            ADCSequenceDataGet(ADC0_BASE, 1, adcdata);

            uint32_t ortalamadeger=(adcdata[0]+adcdata[1]+adcdata[2]+adcdata[3])/4;
            adcseridengonder(ortalamadeger);
        }

        if (UARTCharsAvail(UART0_BASE)){
            gelenveri=UARTCharGet(UART0_BASE);
            if (gelenveri=='%'){
                saatmi=true;
                gelensaatno=0;
                TimerDisable(TIMER0_BASE, TIMER_A);
            }
            else if (saatmi==true){
                saatdizi[gelensaatno]=gelenveri-48;
                gelensaatno++;
                if (gelensaatno==7){
                    saatmi=false;
                    gelensaatno=0;
                    TimerEnable(TIMER0_BASE, TIMER_A);
                }
            }

        }

    }
}

void adcseridengonder(deger){
    char hane3;
    char hane2;
    char hane1;
    char hane0;
    if(deger<10)
    {
        hane3=0; hane2=0; hane1=0; hane0=deger;
    }
    else if(deger<100)
    {
        hane3=0; hane2=0; hane0=(deger % 10); hane1=((deger-hane0)/10);
    }
    else if(deger<1000)
    {
        hane3='0'; hane0=(deger%10); hane1=((deger-hane0)/10) % 10; hane2=(deger-10*hane1-1*hane0) / 100;
    }
    else
    {
        hane0=(deger%10); hane1=((deger-hane0)/10) % 10; hane2=(deger-10*hane1-1*hane0)%100;
        hane3=(deger-100*hane2-10*hane1-1*hane0)/1000;
    }

    UARTCharPut(UART0_BASE,'(');
    UARTCharPut(UART0_BASE,hane3+48);
    UARTCharPut(UART0_BASE,hane2+48);
    UARTCharPut(UART0_BASE,hane1+48);
    UARTCharPut(UART0_BASE,hane0+48);
    UARTCharPut(UART0_BASE,')');
    UARTCharPut(UART0_BASE,'\n');


}

void SetInitSettings()
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); // 40mhz

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // SYSCTL_RCGCGPIO_R|=0x20;
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); // pin 123 output

    // asagidaki 3 kod portf'in 0 nolu pinini lock özelliðini kapatýyor.
    // bu kod olmazsa portf,pin0 okuma fonksiyonu asagiða çalýþmaz.
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_4); // pf4 input
    GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_4, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);// pull up için

    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0);

    // timer ayarlarý
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC); // down sayýcý
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()); // 40 000 000 1 sn için

    // 2 global
//    IntMasterEnable();
//    IntEnable(INT_TIMER0A);
//
//     //3yerel interrupt ayarlari
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT); // bayrak temizlendi
//    TimerIntRegister(TIMER0_BASE, TIMER_A, timerkesmefonksiyonu);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0); // ADC HAYAT=1

    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0); /// adc0 kullan ve sequence 1 seç

    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_TS); // sýcaklýk sensörü seçildi
    ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_TS);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_TS);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 3, ADC_CTL_TS|ADC_CTL_IE|ADC_CTL_END);

    ADCSequenceEnable(ADC0_BASE, 1); // adc ayarlanmasý bitti

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // sadece hangi pinleri uart olarak kullanacagýz
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1);

    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                        UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);

    UARTEnable(UART0_BASE);
    TimerEnable(TIMER0_BASE, TIMER_A); // setb tr0
}

void saatkontrol(){
     int sa=saatdizi[0]*10+saatdizi[1];
     int dk=saatdizi[3]*10+saatdizi[4];
     int sn=saatdizi[6]*10+saatdizi[7];

     sn++;
     if (sn==60){
         sn=0;
         dk++;
         if (dk==60){
             dk=0;
             sa++;
             if(sa==24){
                 sa=0;
             }
         }
     }

     saatdizi[1]=sa % 10;
     saatdizi[0]=(sa-saatdizi[1])/10;

     saatdizi[4]=dk % 10;
     saatdizi[3]=(dk-saatdizi[4])/10;

     saatdizi[7]=sn % 10;
     saatdizi[6]=(sn-saatdizi[7])/10;
}

void PCyeistediginbirmesaj(){
    UARTCharPut(UART0_BASE,'{');
    UARTCharPut(UART0_BASE,'h');
    UARTCharPut(UART0_BASE,'e');
    UARTCharPut(UART0_BASE,'e');
    UARTCharPut(UART0_BASE,'l');
    UARTCharPut(UART0_BASE,'l');
    UARTCharPut(UART0_BASE,'l');
    UARTCharPut(UART0_BASE,'l');
    UARTCharPut(UART0_BASE,'o');
    UARTCharPut(UART0_BASE,'}');
    UARTCharPut(UART0_BASE,'\n');
}

void PCyesaatgonder(){
    int i;
    UARTCharPut(UART0_BASE,'['); // saat gidecek
    for (i=0;i<8;i++){
        UARTCharPut(UART0_BASE, saatdizi[i]+48);
    }
    UARTCharPut(UART0_BASE,'\n');
}
