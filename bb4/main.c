#include "stdbool.h"
#include "stdint.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/timer.c"

void Timer0IntHandler(void);

int main(void)
{
  unsigned long ulPeriod;
  int counter;
  SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
  TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC);

  ulPeriod = (SysCtlClockGet());
  TimerLoadSet(TIMER0_BASE, TIMER_A, ulPeriod-1);

  TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
  IntMasterEnable();
  TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0IntHandler);
  TimerIntClear(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
  IntEnable(INT_TIMER0A);
  TimerEnable(TIMER0_BASE, TIMER_A);

  while(1)
  {
      counter=TimerValueGet(TIMER0_BASE,TIMER_A);
  }
}

void Timer0IntHandler(void)
{
    // Clear the timer interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    // Read the current state of the GPIO pin and
    // write back the opposite state
    if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2))
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
    }
    else
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 4);
    }
}
