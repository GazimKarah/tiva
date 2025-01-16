#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.c"

#include "inc/tm4c123gh6pm.h"

#include "lcd.h"

int main(void)
{
   SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ| SYSCTL_OSC_MAIN);
   lcdilkayarlar();
   lcdgotoxy(1,1);
   lcdyaz('+');

	return 0;
}
