#include "stdbool.h"
#include "stdint.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

void serikesme(void)
{
     unsigned long kesmeno;
     kesmeno = UARTIntStatus(UART0_BASE, true); 
     UARTIntClear(UART0_BASE, kesmeno);
     if(UARTCharsAvail(UART0_BASE)) 
     {
         UARTCharPut(UART0_BASE, UARTCharGet(UART0_BASE)); 
     }
}

int main(void) {
     SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
     SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
     SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

     GPIOPinConfigure(GPIO_PA0_U0RX);
     GPIOPinConfigure(GPIO_PA1_U0TX);
     GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

     UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 9600,
     (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

     IntMasterEnable(); 
     IntEnable(INT_UART0); 
     UARTIntEnable(UART0_BASE, UART_INT_RX|UART_INT_RT);
     UARTIntRegister(UART0_BASE, serikesme);
     UARTCharPut(UART0_BASE, 'E');


 while (1)
 {

 }
}
