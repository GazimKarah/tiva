#include "stdint.h"
#include"inc/tm4c123gh6pm.h"

//apisiz

void PortFKesmesi(void);

int main(void)
{
    // gecen hafta SYSCTL_RCGCGPIO_R|=0x20; // portf saat aktif
    SYSCTL_RCGCGPIO_R|=(1<<5);

    GPIO_PORTF_LOCK_R = 0x4C4F434B; // commit aç
    GPIO_PORTF_CR_R = 0x01;   // pf0 da artýk konfigurasyn yapýlabilir. 0000 0001
                              // 0000 0001 -> pf0 artýk konfigure edilebilir

    // gecen hafta GPIO_PORTF_DIR_R|=0x0E; // 0b 0000 1110 yönlendirme
    GPIO_PORTF_DIR_R &=~(1<<4)|~(1<<0); // pf4 ve 0 =0 yani input
    GPIO_PORTF_DIR_R |= (1<<3)|(1<<2)|(1<<1); // pf 123 output

    // gecen hafta GPIO_PORTF_DEN_R|=0x1F; // 0b 0001 1111 pin aktifliði
    GPIO_PORTF_DEN_R|=(1<<4)|(1<<3)|(1<<2)|(1<<1)|(1<<0);


    // gecen hafta GPIO_PORTF_PUR_R = 0x11; // pf0 ve pf4 pull-up aktif 0001 0001
    GPIO_PORTF_PUR_R|=(1<<4)|(1<<0);

//######################################################################################
    // Gpio interrup ayarlarý
//    7. Program the GPIOIS, GPIOIBE, GPIOEV, and GPIOIM registers to configure the type, event,
//    and mask of the interrupts for each port.
//    Note: To prevent false interrupts, the following steps should be taken when re-configuring
//    GPIO edge and interrupt sense registers:
//    a. Mask the corresponding port by clearing the IME field in the GPIOIM register.
//    b. Configure the IS field in the GPIOIS register and the IBE field in the GPIOIBE
//    register.
//    c. Clear the GPIORIS register.
//    d. Unmask the port by setting the IME field in the GPIOIM register.

    // Table 10-6. GPIO Register Map syf 660
//######################################################################################

    //a.
//*************************************************************************************
    //b. Configure the IS field in the GPIOIS register
    //Register 3: GPIO Interrupt Sense (GPIOIS), offset 0x404 syf 664
//    The GPIOIS register is the interrupt sense register. Setting a bit in the GPIOIS register configures
//    the corresponding pin to detect levels, while clearing a bit configures the corresponding pin to detect
//    edges. All bits are cleared by a reset.

    // 1 ve 4 ü sýfýrlamak istiyoruz
    // eski versiyon yazým GPIO_PORTF_IS_R &= 0xEE //11101110;
    // yeni version yazim
    GPIO_PORTF_IS_R  &= ~(1<<4)|~(1<<0);
//*************************************************************************************

//*************************************************************************************
    // b'nin devamithe IBE field in the GPIOIBE register.
//    Register 4: GPIO Interrupt Both Edges (GPIOIBE), offset 0x408
//    The GPIOIBE register allows both edges to cause interrupts. When the corresponding bit in the
//    GPIO Interrupt Sense (GPIOIS) register (see page 664) is set to detect edges, setting a bit in the
//    GPIOIBE register configures the corresponding pin to detect both rising and falling edges, regardless
//    of the corresponding bit in the GPIO Interrupt Event (GPIOIEV) register (see page 666). Clearing
//    a bit configures the pin to be controlled by the GPIOIEV register. All bits are cleared by a reset.

//    Value Description
//    0--> Interrupt generation is controlled by the GPIO Interrupt Event
//                                      (GPIOIEV) register (see page 666).
//    1--> Both edges on the corresponding pin trigger an interrupt.

    // eski tip yazým GPIO_PORTF_IBE_R &=0xEE; //11101110
    GPIO_PORTF_IBE_R &=~(1<<4)|~(1<<0); //~0x11 // IEV registeri ile ayarlayacagimizi soyledik

//    Register 5: GPIO Interrupt Event (GPIOIEV), offset 0x40C
//    The GPIOIEV register is the interrupt event register. Setting a bit in the GPIOIEV register configures
//    the corresponding pin to detect rising edges or high levels, depending on the corresponding bit
//    value in the GPIO Interrupt Sense (GPIOIS) register (see page 664). Clearing a bit configures the
//    pin to detect falling edges or low levels, depending on the corresponding bit value in the GPIOIS
//    register. All bits are cleared by a reset.

//    Value Description
//    0-->A falling edge or a Low level on the corresponding pin triggers
//    an interrupt.
//
//    1-->A rising edge or a High level on the corresponding pin triggers
//    an interrupt.

    // yine 0 layacagýz
    //eski tip yazim GPIO_PORTF_IEV_R=&=0xEE;
    GPIO_PORTF_IEV_R &=~(1<<4)|~(1<<0);  //~0x11
 //***************************************************************************************
    //c.  Clear the GPIORIS register.
//    Register 7: GPIO Raw Interrupt Status (GPIORIS), offset 0x414
//    The GPIORIS register is the raw interrupt status register. A bit in this register is set when an interrupt
//    condition occurs on the corresponding GPIO pin. If the corresponding bit in the GPIO Interrupt
//    Mask (GPIOIM) register (see page 667) is set, the interrupt is sent to the interrupt controller. Bits
//    read as zero indicate that corresponding input pins have not initiated an interrupt. For a GPIO
//    level-detect interrupt, the interrupt signal generating the interrupt must be held until serviced. Once
//    the input signal deasserts from the interrupt generating logical sense, the corresponding RIS bit in
//    the GPIORIS register clears.

//    For a GPIO edge-detect interrupt, the RIS bit in the GPIORIS register
//    is cleared by writing a ‘1’ to the corresponding bit in the GPIO Interrupt Clear (GPIOICR) register.
//    The corresponding GPIOMIS bit reflects the masked value of the RIS bit.


    // maalesef devam
//    Register 9: GPIO Interrupt Clear (GPIOICR), offset 0x41C
//    The GPIOICR register is the interrupt clear register. For edge-detect interrupts, writing a 1 to the
//    IC bit in the GPIOICR register clears the corresponding bit in the GPIORIS and GPIOMIS registers.
//    If the interrupt is a level-detect, the IC bit in this register has no effect. In addition, writing a 0 to any
//    of the bits in the GPIOICR register has no effect.
    // eski tip yazim GPIO_PORTF_ICR_R |= 0x11;// 00010001
    GPIO_PORTF_ICR_R |=(1<<4)|(1<<0);
//*************************************************************************************

//**************************************************************************************

    //d. Unmask the port by setting the IME field in the GPIOIM register.
//    Register 6: GPIO Interrupt Mask (GPIOIM), offset 0x410
//    The GPIOIM register is the interrupt mask register. Setting a bit in the GPIOIM register allows
//    interrupts that are generated by the corresponding pin to be sent to the interrupt controller on the
//    combined interrupt signal. Clearing a bit prevents an interrupt on the corresponding pin from being
//    sent to the interrupt controller. All bits are cleared by a reset.

//    Value Description
//    0 The interrupt from the corresponding pin is masked.
//    1 The interrupt from the corresponding pin is sent to the interrupt
//      controller.
    GPIO_PORTF_IM_R |=(1<<4)|(1<<0); // maskeleme yapma - combined


//**************************************************************************************
    // syf 124
    //3.1.2 Nested Vectored Interrupt Controller (NVIC)

    // syf 134
    // Nested Vectored Interrupt Controller (NVIC) Registers

    // SYF 101 2.5 Exception Model
    // SYF 104 Table 2-9. Interrupts BURDAN noyu öðren

    // portf kismi
//    Vector Number Interrupt Number (Bit
//    45              29                      0x0000.00B4 Flash Memory Control and EEPROM Control
//    46              30                      0x0000.00B8 GPIO Port F


//    Nested Vectored Interrupt Controller (NVIC) Registers
//                      0x100 EN0 RW 0x0000.0000 Interrupt 0-31 Set Enable 142
    NVIC_EN0_R = 0x40000000;  // 30. su portf enable interrupt


    // burada bir de priority kýsmý olmasý gerekir
//********************************************************************************


    while(1)
    {

    }
}

void PortFKesmesi(void){
    // hangi pinden kesme geldiðini belirtir.
//    Register 6: GPIO Interrupt Mask (GPIOIM), offset 0x410
//    The GPIOIM register is the interrupt mask register. Setting a bit in the GPIOIM register allows
//    interrupts that are generated by the corresponding pin to be sent to the interrupt controller on the
//    combined interrupt signal. Clearing a bit prevents an interrupt on the corresponding pin from being
//    sent to the interrupt controller. All bits are cleared by a reset.

    if(GPIO_PORTF_MIS_R&0x01){  // SW2 touch

      GPIO_PORTF_ICR_R = 0x01;  // acknowledge flag0 // yukarýda anlatýlmýþtý
      GPIO_PORTF_DATA_R=0x02;


    }

    if(GPIO_PORTF_MIS_R&0x10){  // SW1 touch

      GPIO_PORTF_ICR_R = 0x10;  // acknowledge flag4
      GPIO_PORTF_DATA_R=0x04;


    }
}
