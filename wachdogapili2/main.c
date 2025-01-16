#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/watchdog.h"
#include "driverlib/gpio.h"

void WatchdogIntHandler(void);

bool tetik=false;

int main(void)
{
    //configure system clock
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    //Set Direction for PORTF
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    // Enable the Watchdog 0 peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG0);
    // Wait for the Watchdog 0 module to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_WDOG0))
    {
    }
    // Check to see if the registers are locked, and if so, unlock them.
//    if(WatchdogLockState(WATCHDOG0_BASE) == true)
//    {
//        WatchdogUnlock(WATCHDOG0_BASE);
//    }
    // Initialize the watchdog timer.
    WatchdogReloadSet(WATCHDOG0_BASE, SysCtlClockGet()-1); //500ms approx
    // Enable the reset.
    //WatchdogResetEnable(WATCHDOG0_BASE);
    WatchdogIntRegister(WATCHDOG0_BASE, WatchdogIntHandler);
    // Enable the watchdog timer
    //IntEnable(INT_WATCHDOG);
    WatchdogIntEnable(WATCHDOG0_BASE);
    WatchdogEnable(WATCHDOG0_BASE);
    // Wait for the reset to occur.
    while(1)
    {
        tetik=true;
    }
}

void WatchdogIntHandler(void)
{

    // Clear the watchdog interrupt
    WatchdogIntClear(WATCHDOG0_BASE);
    if (tetik==true)
    {
        // Read the current state of the GPIO pin and
        // toggle the led state with respect to previous state
        if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_3))
        {
            //Green led off
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
        }
        else
        {
            //green led on
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 8);
        }
    }


}
