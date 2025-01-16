#include "stdint.h"
#include"inc/tm4c123gh6pm.h"

void init_i2c();


int main()
{
    // topraklar ortak
    init_i2c();
//    8. Specify the slave address of the master and that the next operation is a Transmit by writing the
//    I2CMSA register with a value of 0x0000.0076. This sets the slave address to 0x3B
	I2C0_MSA_R= (0x55<<1)+0; //kölenin adresi=0x55+write yapmak istiyorum; //1010101

//	9. Place data (byte) to be transmitted in the data register by writing the I2CMDR register with the
//	desired data.
	I2C0_MDR_R='w';

//	10. Initiate a single byte transmit of the data from Master to Slave by writing the I2CMCS register
//	with a value of 0x0000.0007 (STOP, START, RUN)
	I2C0_MCS_R=0x07; // haberleþme baþladý

//	11. Wait until the transmission completes by polling the I2CMCS register's BUSBSY bit until it has
//	been cleared
	while(I2C0_MCS_R & 0x01); // busy bekler

//	12. Check the ERROR bit in the I2CMCS register to confirm the transmit was acknowledged.
	if (!(I2C0_MCS_R & 0x02))
	{
	    int x=7;
	}

	// receive
	I2C0_MSA_R= (0x55<<1)+1; // arduino i2c slave - adama cevap vermem lazým
	I2C0_MCS_R=0x07; // haberleþme baþladý
    while(I2C0_MCS_R & 0x01); // busy bekler

    if (!(I2C0_MCS_R & 0x02))
    {
        int x=7;
    }

    uint8_t geleveri=I2C0_MDR_R;
	return 0;
}

void init_i2c()
{
    // hiç bir saat ayarý yapmadýysak 16mhz
//    1. Enable the I2C clock using the RCGCI2C register in the System Control module (see page 348).
    SYSCTL_RCGCI2C_R|=0x01;

//    2. Enable the clock to the appropriate GPIO module via the RCGCGPIO register in the System
//    Control module (see page 340). To find out which GPIO port to enable, refer to Table
//    23-5 on page 1351.
    SYSCTL_RCGCGPIO_R|=0x02;

//    3. In the GPIO module, enable the appropriate pins for their alternate function using the
//    GPIOAFSEL register (see page 671). To determine which GPIOs to configure, see Table
//    23-4 on page 1344.
    GPIO_PORTB_DEN_R |=0x0c;  // pb2 ve pb3 aktif 0000 1100

    GPIO_PORTB_AFSEL_R |=0x0c;

//    4. Enable the I2CSDA pin for open-drain operation. See page 676
    GPIO_PORTB_ODR_R|=0x08;  // sdb için open drain yapýldý

    // 5. Configure the PMCn fields in the GPIOPCTL register to assign the I2C signals to the appropriate
   // pins. See page 688 and Table 23-5 on page 1351.

    GPIO_PORTB_PCTL_R|=0x33; // ??

//    6. Initialize the I2C Master by writing the I2CMCR register with a value of 0x0000.0010.

    I2C0_MCR_R|=0x0010;

//    7. Set the desired SCL clock speed of 100 Kbps by writing the I2CMTPR register with the correct
//    value. The value written to the I2CMTPR register represents the number of system clock periods
//    in one SCL clock period. The TPR value is determined by the following equation:
//    TPR = (System Clock/(2*(SCL_LP + SCL_HP)*SCL_CLK))-1;
//    TPR = (16MHz/(2*(6+4)*100000))-1;
//    TPR = 7
//    Write the I2CMTPR register with the value of 0x0000.0009.
    I2C0_MTPR_R=7; // 100 kbps



}
