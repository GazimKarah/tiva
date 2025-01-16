#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_sysctl.h"


void portfkesmesifonksiyonu()
{
	int a;
	a=GPIOIntStatus(GPIO_PORTF_BASE,false); //hangi pinden kesme geliyor. bunu belirler. burada simdilik 16 olacak
    GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 2);
    SysCtlDelay(2000000);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
}

int main(void)
 {
	IntMasterEnable();
	SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);


	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
	GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);
	GPIOIntRegister(GPIO_PORTF_BASE,portfkesmesifonksiyonu);
	GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4,GPIO_FALLING_EDGE);

	GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);
	GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4);
	IntEnable(INT_GPIOF);

	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);

	while(1)
	{

	}
}