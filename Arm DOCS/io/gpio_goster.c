/* Read a switch and write it to the LED */
/* This program reads SW1 of Tiva LaunchPad and writes the inverse of the value to the green
   LED. SW1 is low when pressed (Normally High). LED is ON when high.
*/

#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

int main(void)
{

    unsigned int value;

    SYSCTL_RCGC2_R |= 0x00000020;

    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R = 0x01;
    GPIO_PORTF_AMSEL_R = 0x00;
    GPIO_PORTF_PCTL_R = 0x00;

    GPIO_PORTF_DIR_R = 0x0E;
    GPIO_PORTF_DEN_R = 0x1F;
    GPIO_PORTF_PUR_R = 0x11;


    while(1)
    {
        value=GPIO_PORTF_DATA_R;
        // burada ne yapılabilir.
        // pf0'a tıklanmış ise kırmızı yak

//        if (value==0x10)
//        {
//            GPIO_PORTF_DATA_R|=0x02;
//        }
        
        // bunu ikinci kez koşturunca dikkat et bakalım neler oluyor
        

        // bunun yerine bu daha mantıklı gibi
//        if ((value & 0x01)==0)
//        {
//            GPIO_PORTF_DATA_R|=0x02;
//        }

        
        
    }
}
