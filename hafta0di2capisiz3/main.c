#include "stdint.h"
#include "stdio.h"
#include"inc/tm4c123gh6pm.h"

char data[]={65,66,'D','E'};

void init_i2c();

int Writei2c(uint32_t adress,uint8_t data){
    I2C0_MSA_R= (adress<<1)+0; // write modu adres seçimi
    I2C0_MDR_R=data;
    I2C0_MCS_R=0x07; // start, transmit,stop
    while(I2C0_MCS_R & 0x40); // busy bekler
    if (!(I2C0_MCS_R & 0x02))
    {
        return 0; // hata yok
    } else {
        return 1; // hata var
    }
}

void WriteMulti(uint32_t adress,char datam[], int count){
    I2C0_MSA_R= (adress<<1)+0; // write modu adres seçimi
    I2C0_MDR_R='O'; // karşı taraftaki adamin ram adresi
    I2C0_MCS_R=0x03; // start, transmit
    while((I2C0_MCS_R &=0x40)==1); // busy bekler

    int i=0;
    while(i<count){
        if((count==1) || (i==count-1)){
            I2C0_MDR_R=datam[i];
            I2C0_MCS_R=0x07;
            while((I2C0_MCS_R &=0x40)==1); // busy bekler
            break;
        } else {
            I2C0_MDR_R=datam[i];
            I2C0_MCS_R=0x01;
            while((I2C0_MCS_R &=0x40)==1); // busy bekler
            i++;
        }
    }
}

uint8_t Readmulti(uint32_t adress, int count){
    I2C0_MSA_R= (adress<<1)+0; // write modu adres seçimi
    I2C0_MDR_R='O'; // karşı taraftaki adamin ram adresi
    I2C0_MCS_R=0x03; // start, transmit
    while((I2C0_MCS_R &=0x40)==1); // busy bekler

    I2C0_MSA_R= (adress<<1)+1; // write modu adres seçimi

    I2C0_MCS_R = 0x0b;
    while((I2C0_MCS_R &=0x40)==1);
    data[0]=I2C0_MDR_R;

    int i=1;
    while(i<count){
        if((count==1) || (i==count-1)){
            I2C0_MCS_R=0x05;
            data[i]=I2C0_MDR_R;
            while((I2C0_MCS_R &=0x40)==1); // busy bekler
        } else {
            I2C0_MCS_R=0x09;
            data[i]=I2C0_MDR_R;
            while((I2C0_MCS_R &=0x40)==1); // busy bekler
            i++;
        }
    }
}

void WriteMulti2(uint32_t adress,char datam[],int count){
    //int count=// dizinin boyutu
    I2C0_MSA_R= (adress<<1)+0; // write modu adres seçimi
    I2C0_MDR_R='O'; // karşı taraftaki adamin ram adresi
    I2C0_MCS_R=0x03; // start, transmit
    while((I2C0_MCS_R &=0x40)==1); // busy bekler

    int i=0;
    while(i<count){
        if((count==1) || (i==count-1)){
            I2C0_MDR_R=datam[i];
            I2C0_MCS_R=0x07;
            while((I2C0_MCS_R &=0x40)==1); // busy bekler
        } else {
            I2C0_MDR_R=datam[i];
            I2C0_MCS_R=0x01;
            while((I2C0_MCS_R &=0x40)==1); // busy bekler
            i++;
        }

    }
}

uint8_t Readi2c(int32_t adress){
    // receive
    I2C0_MSA_R= (adress<<1)+1; // arduino i2c slave - adama cevap vermem lazım
    I2C0_MCS_R=0x07; // haberleşme başladı
    while(I2C0_MCS_R & 0x40); // busy bekler

    uint8_t geleveri=I2C0_MDR_R;

    return geleveri;
}

int main()
{

    init_i2c();

    //int error=Writei2c(0x55,'T');
    WriteMulti(0x55,data, 3);
    Readmulti(0x55, 3);
    uint8_t gelenver=Readi2c(0x55);

	return 0;
}

void init_i2c()
{
    // i2c0 aktif
    SYSCTL_RCGCI2C_R|=0x01;
    // portb aktif
    SYSCTL_RCGCGPIO_R|=0x02;
    GPIO_PORTB_DEN_R |=0x0c;  // pb2 ve pb3 aktif 0000 1100
    //alternatif fonksiyon
    GPIO_PORTB_AFSEL_R |=0x0c;
    // open drain pull up
    GPIO_PORTB_ODR_R|=0x08;  // sda için open drain yapıldı
    GPIO_PORTB_PCTL_R|=0x03;
    I2C0_MCR_R|=0x0010; // master
    I2C0_MTPR_R=7; // 100 kbps
}
