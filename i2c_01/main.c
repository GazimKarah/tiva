#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/sysctl.c"
#include "driverlib/gpio.h"
#include "driverlib/gpio.c"
#include "inc/hw_gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/i2c.c"
#include "driverlib/pin_map.h"
#include "inc/tm4c123gh6pm.h"

void init();

int device_address=0x55;

int main(void)
{

    init();

	while(1)
	{
	    I2CMasterSlaveAddrSet(I2C0_BASE, 0x55, false); // master gönderiyor
	    I2CMasterDataPut(I2C0_BASE, 'B'); // registera yazdýk daha göndermedik.
	    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);

	    //wait for MCU to finish transaction
	    while(I2CMasterBusy(I2C0_BASE));
        //I2CMasterControl(I2C0_BASE,I2C_MASTER_CMD_BURST_SEND_FINISH);

        //read from the specified slave device
        I2CMasterSlaveAddrSet(I2C0_BASE, 0x55, true);
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);

        while(I2CMasterBusy(I2C0_BASE));
        int xx= I2CMasterDataGet(I2C0_BASE);

        xx=4;

	}
}


void init(){
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    // asagidaki 3 kod portf'in 0 nolu pinini lock özelliðini kapatýyor.
    // bu kod olmazsa portf,pin0 okuma fonksiyonu asagiða çalýþmaz.
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    //HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4); //pin0 ve pin4 input
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU); // pin0 ve pin4 pull-up

    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);

    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C0));


    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false); // yavaþ
    I2CMasterSlaveAddrSet(I2C0_BASE, 0x55, false); // master gönderiyor

}
