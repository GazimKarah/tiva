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
#include "driverlib/pin_map.h"


#include "inc/tm4c123gh6pm.h"

void SetInitSettings();
void timerkesmefonksiyonu();
// api li

int main(void)
{
    SetInitSettings(); // ilk yaaralarmýzý
    int i=0;
    while(1)
    {
        i=TimerValueGet(TIMER2_BASE,TIMER_A);
    }


}

void SetInitSettings()
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); // 40mhz
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // SYSCTL_RCGCGPIO_R|=0x20;
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); // pin 123 output

    // asagidaki 3 kod portf'in 0 nolu pinini lock özelliðini kapatýyor.
    // bu kod olmazsa portf,pin0 okuma fonksiyonu asagiða çalýþmaz.
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;

//    GPIO_PORTF_LOCK_R = 0x4C4F434B; // commit aç
//    GPIO_PORTF_CR_R = 0x01;   // pf0 da artýk konfigurasyn yapýlabilir. 0000 0001
//                              // 0000 0001 -> pf0 artýk konfigure edilebilir

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_4); // pf4 input
    GPIODirModeSet(GPIO_PORTF_BASE,GPIO_PIN_4, GPIO_DIR_MODE_HW);
    //GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_4, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);// pull up için

    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0);

    // timer ayarlarý

    GPIOPinTypeTimer(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPinConfigure(GPIO_PF4_T2CCP0);

    TimerConfigure(TIMER2_BASE, (TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_CAP_COUNT_UP));
    TimerControlEvent(TIMER2_BASE,TIMER_A, TIMER_EVENT_NEG_EDGE);
    TimerLoadSet(TIMER2_BASE, TIMER_A, 3);
    TimerEnable(TIMER2_BASE,TIMER_A);


    //GPIODirModeSet(ui32Port, ui8Pins, ui32PinIO)
}

void timerkesmefonksiyonu()
{

}
