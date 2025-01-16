/*
 * lcd.c
 *
 *  Created on: 3 Kas 2020
 *      Author: bb
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/gpio.c"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.c"
#include "lcd.h"

void otuzhexgonder()
{
    SysCtlDelay(100000);
    // rs=0
    GPIOPinWrite(LCDPORT, RS, 0);
    //ayar yazýldý
    GPIOPinWrite(LCDPORT, D4|D5|D6|D7, 0X30);
    // en ac kapa
    GPIOPinWrite(LCDPORT, E, 2);
    SysCtlDelay(1000);
    GPIOPinWrite(LCDPORT, E, 0);
    // 3 kez 30h gönder
}

void lcdkomut(unsigned char c) //0x47
{
    GPIOPinWrite(LCDPORT, RS, 0);
    GPIOPinWrite(LCDPORT, D4|D5|D6|D7, (c & 0xf0));
    GPIOPinWrite(LCDPORT, E, 2);
    SysCtlDelay(1000);
    GPIOPinWrite(LCDPORT, E, 0);

    SysCtlDelay(1000);

    GPIOPinWrite(LCDPORT, RS, 0);
    GPIOPinWrite(LCDPORT, D4|D5|D6|D7, (c & 0x0f)<<4);
    GPIOPinWrite(LCDPORT, E, 2);
    SysCtlDelay(1000);
    GPIOPinWrite(LCDPORT, E, 0);

    SysCtlDelay(1000);

}

void LCDilkayarlar()
{
    //portf_base_enable
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinTypeGPIOOutput(LCDPORT, 0xFF); // hepsi out

    otuzhexgonder();
    otuzhexgonder();
    otuzhexgonder();

    // ayarlar devam
    //lcd komut kullan
    lcdkomut(0x07); // giriþ kipi
}

void lcdfonksiyonayarla( unsigned char DL,unsigned char N,unsigned char F)
{

}

void lcdkarakteryaz(unsigned char c)
{


}

