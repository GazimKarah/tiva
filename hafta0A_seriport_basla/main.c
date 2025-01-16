#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/sysctl.c"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "inc/tm4c123gh6pm.h"

void ilkayarlar();

int main(void)
{

	SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	ilkayarlar();

    UARTCharPut(UART0_BASE, '-');
	UARTCharPut(UART0_BASE, 'v');
    UARTCharPut(UART0_BASE, 'E');
    UARTCharPut(UART0_BASE, 'R');
    UARTCharPut(UART0_BASE, 'i');
    UARTCharPut(UART0_BASE, ' ');
    UARTCharPut(UART0_BASE, 'G');
    UARTCharPut(UART0_BASE, 'i');
    UARTCharPut(UART0_BASE, 'r');
    UARTCharPut(UART0_BASE, '!');



	while(1)
	{
	   char gelenveri;
	   if( UARTCharsAvail(UART0_BASE)){
	       gelenveri=UARTCharGet(UART0_BASE);
	       UARTCharPut(UART0_BASE,gelenveri);
	   }

	   if(pf4 basýlmýþsa){
	        UARTCharPut(UART0_BASE, '#');
	        UARTCharPut(UART0_BASE, 'm');
	        // merhaba gönderilecek
	   }
	}
}

void ilkayarlar(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // sadece hangi pinleri uart olarak kullanacagýz
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1);

    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                        UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);

    UARTEnable(UART0_BASE);

}
