#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.c"
#include "driverlib/interrupt.h"

#include "inc/tm4c123gh6pm.h"
#include "inc/hw_ints.h"

#include "driverlib/watchdog.h"

bool wcd=false;
int a=4;
void wdtkesme()
{
    if(wcd)
    {
        wcd=false;
        WatchdogIntClear(WATCHDOG0_BASE);
        WatchdogReloadSet(WATCHDOG0_BASE, SysCtlClockGet()-1);
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,a);
    }
}
void SetInitSettings();
// api li

int main(void)
 {

    SetInitSettings();

    while(1)
    {
         wcd=true;

//        while(!GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4))
//        {
//            wcd=true;
//        }
    }


}

void SetInitSettings()
{
    //IntMasterEnable();
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // SYSCTL_RCGCGPIO_R|=0x20;
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); // pin 123 output

    // asagidaki 3 kod portf'in 0 nolu pinini lock özelliðini kapatýyor.
    // bu kod olmazsa portf,pin0 okuma fonksiyonu asagiða çalýþmaz.
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;

//    GPIO_PORTF_LOCK_R = 0x4C4F434B; // commit aç
//    GPIO_PORTF_CR_R = 0x01;   // pf0 da artýk konfigurasyn yapýlabilir. 0000 0001
//                              // 0000 0001 -> pf0 artýk konfigure edilebilir

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_4); // pf4 input
    GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_4, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);// pull up için

    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_WDOG0))
    {
    }
    // Unlock Watchdog
//    if(WatchdogLockState(WATCHDOG0_BASE) == true){
//        WatchdogUnlock(WATCHDOG0_BASE);
//    }
   // IntEnable (INT_WATCHDOG);
    WatchdogReloadSet(WATCHDOG0_BASE, SysCtlClockGet());

    //WatchdogResetEnable(WATCHDOG0_BASE);
    WatchdogIntRegister(WATCHDOG0_BASE, wdtkesme);

    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,8);
    WatchdogIntEnable(WATCHDOG0_BASE);
    WatchdogEnable(WATCHDOG0_BASE);
    //WatchdogIntTypeSet(WATCHDOG0_BASE, WATCHDOG_INT_TYPE_INT);

    //WatchdogIntClear(WATCHDOG0_BASE);
}
