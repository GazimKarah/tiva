#include "stdint.h"
#include"inc/tm4c123gh6pm.h"

void I2C0_Init ( void );
int i2c_bekle(void);
// Receive one byte of data from I2C slave device
char I2C0_Write_Multiple(int slave_address, char slave_memory_address, int bytes_count, char* data);
char I2C3_read_Multiple(int slave_address, char slave_memory_address, int bytes_count, char* data);

int main(void)
{
    char data[2] = {65,66};
    I2C0_Init();

    I2C0_Write_Multiple(0x55, 0, 1, &data[0]);
    //I2C3_Write_Multiple(0x55, 0, 1, &data[1]);
    I2C3_read_Multiple(0x55, 0, 1, &data[1]);
"       while(1);


	return 0;
}

char I2C3_read_Multiple(int slave_address, char slave_memory_address, int bytes_count, char* data){
    char error;
    if (bytes_count <=0 ){
        return -1;
    }
    I2C0_MSA_R=slave_address<<1; //& 0xFE; // slave adress yazma modu
    I2C0_MDR_R=slave_memory_address;
    I2C0_MCS_R=0x03; // start run

    error=i2c_bekle();
    if (error) return error;

    I2C0_MSA_R=(slave_address<<1)|1; //& 0xFE; // slave adress okuma modu

    if (bytes_count==1){ /* if last byte, don't ack */
        I2C0_MCS_R=0x07; /* -data-NACK-P */
    } else {
        I2C0_MCS_R=0x0b; //Repeated START condition followed by RECEIVE
                        //(master goes to Master Receive state
    }
    error=i2c_bekle();
    if (error) return error;

    *data++=I2C0_MDR_R; /* store the data received */

    if (--bytes_count==0)  /* if single byte read, done */
    {
        while(I2C0_MCS_R & 0x40);  /* wait until bus is not busy */
        return 0;       /* no error */
    }

    /* read the rest of the bytes */
    while(bytes_count>1){
        I2C0_MCS_R=9;  /* -data-ACK- */ // receive operatiýon
        error=i2c_bekle();
        if (error) return error;

        bytes_count--;
        *data++=I2C0_MDR_R;
    }

    I2C0_MCS_R=5; /* -data-NACK-P */ //RECEIVE followed by STOP condition (master goes to
                                       //                                  Idle state)
    error=i2c_bekle();
    if (error) return error;

    *data=I2C0_MDR_R;
    while(I2C0_MCS_R & 0x40);  /* wait until bus is not busy */

    return 0;       /* no error */

}
char I2C0_Write_Multiple(int slave_address, char slave_memory_address, int bytes_count, char* data){
    char error;
    if (bytes_count <=0 ){
        return -1;
    }
    I2C0_MSA_R=slave_address<<1; //& 0xFE; // slave adress
    I2C0_MDR_R=slave_memory_address;
    I2C0_MCS_R=0x03; // start run

    error=i2c_bekle();

    if (error) return error;

    while(bytes_count>1){
        I2C0_MDR_R=*data++;
        I2C0_MCS_R=1; /* -data-ACK- */
        error=i2c_bekle();
        if (error) return error;
        bytes_count--;
    }

    /* send last byte and a STOP */
    I2C0_MDR_R=*data++;
    I2C0_MCS_R=5; /* -data-ACK-P */
    error=i2c_bekle();

    while(I2C0_MCS_R & 0x40 ); // stop condition oluþtumu

    if (error) return error;
    return 0;


}
int i2c_bekle(void){
    while(I2C0_MCS_R & 0x01); // busy bekler
    return (I2C0_MCS_R & 0x0e);
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
