#include "stdint.h"
#include"inc/tm4c123gh6pm.h"

void Delay_ms(int time_ms)
{
    int i, j;
    for(i = 0 ; i < time_ms; i++)
        for(j = 0; j < 3180; j++)
            {}  /* excute NOP for 1ms */
}

int main(void)
{
    volatile unsigned long delay;
//    The following example shows how to initialize PWM Generator 0 with a 25-kHz frequency, a 25%
//    duty cycle on the MnPWM0 pin, and a 75% duty cycle on the MnPWM1 pin. This example assumes
//    the system clock is 20 MHz.

//    1. Enable the PWM clock by writing a value of 0x0010.0000 to
//    the RCGC0 register in the System
//    Control module (see page 456).
    SYSCTL_RCGC0_R|=0X00100000; // SYSCTL_RCGC0_PWM0;
    delay = SYSCTL_RCGC0_R;
//
//    2. Enable the clock to the appropriate GPIO module via the RCGC2 register in the System Control
//    module (see page 464)
    SYSCTL_RCGC2_R|=0x00000002 ; //SYSCTL_RCGC2_GPIOB;
    delay = SYSCTL_RCGC2_R;

//    3. In the GPIO module, enable the appropriate pins for their alternate function using the
//    GPIOAFSEL register. To determine which GPIOs to configure, see Table 23-4 on page 1344
    GPIO_PORTB_AFSEL_R= 0xc0;

    GPIO_PORTB_DEN_R |= 0xc0;             // Enable digital on PB6/7
    GPIO_PORTB_AMSEL_R &= 0x00;           // Disable analog function on all PB pins

//    4. Configure the PMCn fields in the GPIOPCTL register to assign the PWM signals to the appropriate
//    pins (see page 688 and Table 23-5 on page 1351).

    GPIO_PORTB_PCTL_R |= 0x44000000;  // Set Port control to select PWM as the Alt function
    //GPIO_PORTB_PCTL_R |=GPIO_PCTL_PB6_M0PWM0|GPIO_PCTL_PB7_M0PWM1;
    //GPIO_PCTL_PB6_M0PWM0

//    5. Configure the Run-Mode Clock Configuration (RCC) register in
    //the System Control module to use the PWM divide (USEPWMDIV) and
    //set the divider (PWMDIV) to divide by 2 (000).
    //20.bit =1

    //17:18:19 =0 divisor =2

    SYSCTL_RCC_R |=0x00100000;  //SYSCTL_RCC_USEPWMDIV // enable pwm clok divisor
    SYSCTL_RCC_R &=~0x000E0000;

//    6. Configure the PWM generator for countdown mode with immediate updates to the parameters.
//    Write the PWM0CTL register with a value of 0x0000.0000.
//    Write the PWM0GENA register with a value of 0x0000.008C.
//    Write the PWM0GENB register with a value of 0x0000.080C.

    PWM0_0_CTL_R = 0x00000000;
            // PWM Register control UPDATE Immediate Local Sync
            // Counter counts Down PWM Disable
    PWM0_0_GENA_R |= 0x0000008C;      // Settings for pwmA 10001100
    PWM0_0_GENB_R |= 0x0000080C;      // Settings for pwmB 1000 0000 1100
//    7. Set the period. For a 25-KHz frequency, the period = 1/25,000, or 40 microseconds. The PWM
//    clock source is 10 MHz; the system clock divided by 2. Thus there are 400 clock ticks per period.
//    Use this value to set the PWM0LOAD register. In Count-Down mode, set the LOAD field in the
//    PWM0LOAD register to the requested period minus one.
//    Write the PWM0LOAD register with a value of 0x0000.018F.

    PWM0_0_LOAD_R = 320-1;
//    8. Set the pulse width of the MnPWM0 pin for a 25% duty cycle.
//    Write the PWM0CMPA register with a value of 0x0000.012B.
    PWM0_0_CMPA_R = 240-1;
//    9. Set the pulse width of the MnPWM1 pin for a 75% duty cycle.
//    Write the PWM0CMPB register with a value of 0x0000.0063
    uint32_t a= 80-1;
    PWM0_0_CMPB_R = 80-1;

//    10. Start the timers in PWM generator 0.
//    Write the PWM0CTL register with a value of 0x0000.0001

    PWM0_0_CTL_R = 0x00000001;

//    11. Enable PWM outputs.
//    Write the PWMENABLE register with a value of 0x0000.0003

    PWM0_ENABLE_R=0x03; // PWM_ENABLE_PWM0EN|PWM_ENABLE_PWM1EN

    while(1){
//        Delay_ms(10);
//        a-=5;
//        PWM0_0_CMPB_R=a;
//        if (a<=0){
//            a=320-1;
//        }
    }

    return 0;
}
