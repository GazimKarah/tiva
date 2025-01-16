#include "stdint.h"
#include"inc/tm4c123gh6pm.h"

//apisiz

void init();
void systicinit();

int main(void)
{
    init();
    systicinit();

    while(1)
    {
        if ((NVIC_ST_CTRL_R & 0x10000)==65536)
        {
            GPIO_PORTF_DATA_R ^=0x04;
        }

    }
}

void init(){

    SYSCTL_RCGCGPIO_R|=0x20; // portf saat aktif

    GPIO_PORTF_LOCK_R = 0x4C4F434B; // commit aç
    GPIO_PORTF_CR_R = 0x01;   // pf0 da artýk konfigurasyn yapýlabilir. 0000 0001
                              // 0000 0001 -> pf0 artýk konfigure edilebilir

    GPIO_PORTF_DIR_R|=0x0E; // 0b 0000 1110 yönlendirme
    GPIO_PORTF_DEN_R|=0x1F; // 0b 0001 1111 pin aktifliði

    GPIO_PORTF_PUR_R = 0x11; // pf0 ve pf4 pull-up aktif 0001 0001
}

void systicinit(){
//    1. Program the value in the STRELOAD register.
//    2. Clear the STCURRENT register by writing to it with any value.
//    3. Configure the STCTRL register for the required operation.
//    Note: When the processor is halted for debugging, the counter does not decrement
    NVIC_ST_CTRL_R = 0x00; // tümünü o yaptý disable
    NVIC_ST_RELOAD_R=16000000-1; // ilk deðer yüklendi
    NVIC_ST_CURRENT_R=0; // sayýcýnýn son deðeri
    NVIC_ST_CTRL_R = (1<<2)|(1<<0) ; // 0x05 start oldu // enable ve system saati

}
