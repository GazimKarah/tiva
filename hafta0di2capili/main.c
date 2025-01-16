#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/sysctl.c"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/i2c.c"
#include "driverlib/pin_map.h"
#include "inc/tm4c123gh6pm.h"


int main(void)
{

	SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);

	GPIOPinConfigure(GPIO_PB2_I2C0SCL);
	GPIOPinConfigure(GPIO_PB3_I2C0SDA);
	GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
	GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3); // sda

	I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);
	I2CMasterSlaveAddrSet(I2C0_BASE, 0x55, 0);// gönderirici

	while(1)
	{
	    I2CMasterDataPut(I2C0_BASE, 'f');
	    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND );

	    while(I2CMasterBusy(I2C0_BASE));

	    I2CMasterSlaveAddrSet(I2C0_BASE, 0x55, 1);// alcýcý
	    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE );
	    uint8_t gv=I2CMasterDataGet(I2C0_BASE);


	}
}
