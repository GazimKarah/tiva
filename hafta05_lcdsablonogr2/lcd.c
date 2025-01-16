#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"


#include "lcd.h"

void otuzhexgonder()
{
    SysCtlDelay(50000);
    GPIOPinWrite(LCDPORT, d4|d5|d6|d7, 0x30);
    GPIOPinWrite(LCDPORT, E, 0x02); // rs=0
    SysCtlDelay(200);
    GPIOPinWrite(LCDPORT, E, 0x00); // rs=0
}

void lcdilkayarlar(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); // portb aktif
    GPIOPinTypeGPIOOutput(LCDPORT, 0xFF); // butun pinler output

    GPIOPinWrite(LCDPORT, rs, 0x00); // rs=0
    otuzhexgonder();
    otuzhexgonder();
    otuzhexgonder();

    SysCtlDelay(50000);

    GPIOPinWrite(LCDPORT, d4 | d5 | d6 | d7,  0x20 );
    GPIOPinWrite(LCDPORT, E, 0x02);
    SysCtlDelay(200);
    GPIOPinWrite(LCDPORT, E, 0x00);

    SysCtlDelay(50000);

    LcdKomut(0x28); // dl=0 4 bit --- N=1 2 satýr --- F=0 5x7 lcd
    LcdKomut(0x06); // i/d=1 , s=0
    LcdKomut(0x0F); // D=1, C=1, B=1
    LcdKomut(0x01); // ekran sil
}

void LcdKomut (unsigned char c)
{
    GPIOPinWrite(LCDPORT, rs, 0x00); // rs=0
    GPIOPinWrite(LCDPORT, d4|d5|d6|d7, (c & 0xF0));
    GPIOPinWrite(LCDPORT, E, 2); // rs=0
    SysCtlDelay(2000);
    GPIOPinWrite(LCDPORT, E, 0); // rs=0

    SysCtlDelay(20000);

    GPIOPinWrite(LCDPORT, rs, 0x00); // rs=0
    GPIOPinWrite(LCDPORT, d4|d5|d6|d7, (c & 0x0F)<<4);
    GPIOPinWrite(LCDPORT, E, 2); // rs=0
    SysCtlDelay(2000);
    GPIOPinWrite(LCDPORT, E, 0); // rs=0

    SysCtlDelay(20000);


}

void LcdTemizle(void)
{
    LcdKomut(0x01);
}

void lcdfonksiyonayarla( unsigned char dl,unsigned char N,unsigned char F) // dl,N,F
{
    // dl için ya 4 yada 8
    // N için 1 için 1 satýra, 2 gelirse 2 satýr
    // F için 7 gelise 5x7 fontu
       // eðer 10 gelirse de 5x10 fonutunu
}


void lcdyaz(unsigned char c)
{
    GPIOPinWrite(LCDPORT, rs, 0x01); // rs=0
    GPIOPinWrite(LCDPORT, d4|d5|d6|d7, (c & 0xF0));
    GPIOPinWrite(LCDPORT, E, 2); // rs=0
    SysCtlDelay(2000);
    GPIOPinWrite(LCDPORT, E, 0); // rs=0

    SysCtlDelay(50000);

    GPIOPinWrite(LCDPORT, rs, 0x01); // rs=0
    GPIOPinWrite(LCDPORT, d4|d5|d6|d7, (c & 0x0F)<<4);
    GPIOPinWrite(LCDPORT, E, 2); // rs=0
    SysCtlDelay(2000);
    GPIOPinWrite(LCDPORT, E, 0); // rs=0

    SysCtlDelay(50000);

}

void lcdgotoxy(unsigned char x, unsigned char y)
{
    if(x==1)
            LcdKomut(0x80+((y-1)%16));
    else
            LcdKomut(0xC0+((y-1)%16));
}

void LcdMetinYaz( char* s){

        while(*s)
            lcdyaz(*s++);
}

