#include "stdint.h"
#include"inc/tm4c123gh6pm.h"

void I2C0_Init ( void );

int main(void)
{
    I2C0_Init();
    //slave adress
//    8. Specify the slave address of the master and that the next operation is a Transmit by w
//    I2CMSA register with a value of 0x0000.0076. This sets the slave address to 0x3B
    I2C0_MSA_R=0x55<<1+0; // slave adress

//    9. Place data (byte) to be transmitted in the data register by writing the I2CMDR register with the
//    desired data.
    I2C0_MDR_R='v';

//    10. Initiate a single byte transmit of the data from Master to Slave by writing the I2CMCS register
//    with a value of 0x0000.0007 (STOP, START, RUN)
    I2C0_MCS_R=0x07;

//    11. Wait until the transmission completes by polling the I2CMCS register's BUSBSY bit until it has
//    been cleared.
    while(I2C0_MCS_R & 0x01); // busy bekler

//    12. Check the ERROR bit in the I2CMCS register to confirm the transmit was acknowledged
    if (! (I2C0_MCS_R & 0x02)){
        int k=0;
    }

    //Receive
    I2C0_MSA_R=0x55<<1 | 1; // slave adress
    I2C0_MCS_R=0x07;

    while(I2C0_MCS_R & 0x01); // busy bekler

    if (! (I2C0_MCS_R & 0x0e)){
        int k=0;
    }

    uint8_t gelenveri=I2C0_MDR_R;


	return 0;
}

void I2C0_Init ( void ){
//    1. Enable the I2C clock using the RCGCI2C register in the System Control module (see page 348)
    SYSCTL_RCGCI2C_R|=0x01;

//    2. Enable the clock to the appropriate GPIO module via the RCGCGPIO register in the System
//    Control module (see page 340). To find out which GPIO port to enable, refer to Table
//    23-5 on page 1351
    SYSCTL_RCGCGPIO_R|=0x02;

    GPIO_PORTB_DEN_R|=0X0c; // 2 VE 3 PÝN AKTÝF

//    3. In the GPIO module, enable the appropriate pins for their alternate function using the
//    GPIOAFSEL register (see page 671). To determine which GPIOs to configure, see Table
//    23-4 on page 1344
    GPIO_PORTB_AFSEL_R|=0X0C;

//    4. Enable the I2CSDA pin for open-drain operation. See page 676.
    GPIO_PORTB_ODR_R|=0X08;

//    5. Configure the PMCn fields in the GPIOPCTL register to assign the I2C signals to the appropriate
//    pins. See page 688 and Table 23-5 on page 1351
    GPIO_PORTB_PCTL_R|=0X33;

//    6. Initialize the I2C Master by writing the I2CMCR register with a value of 0x0000.0010.
    I2C0_MCR_R=0x0010;

//    7. Set the desired SCL clock speed of 100 Kbps by writing the I2CMTPR register with the correct
//    value. The value written to the I2CMTPR register represents the number of system clock periods
//    in one SCL clock period. The TPR value is determined by the following equation:
//    TPR = (System Clock/(2*(SCL_LP + SCL_HP)*SCL_CLK))-1;
//    TPR = (20MHz/(2*(6+4)*100000))-1;
//    TPR = 9
//    Write the I2CMTPR register with the value of 0x0000.0009

    //DEGER = 16 ,000 ,000/(2(6+4) *100000) - 1 = 7 */
    I2C0_MTPR_R=7;

}
