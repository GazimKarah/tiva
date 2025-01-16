#define SYSCTL_RCGCGPIO_R       (*((volatile unsigned long *)0x400FE608))
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))

int main(void)
{
    SYSCTL_RCGCGPIO_R|=0x20;
    // burada biraz beklersen iyi olur
    volatile unsigned long loop;

    loop=SYSCTL_RCGCGPIO_R; // olesine

    GPIO_PORTF_DIR_R|=0x08; // 3. led output

    GPIO_PORTF_DEN_R|=0x08; // enable pin

    while(1)
    {
        GPIO_PORTF_DATA_R|=0x08;

        for(loop=0;loop<200000;loop++)
        {}

        GPIO_PORTF_DATA_R&=~(0x08);

        for(loop=0;loop<200000;loop++)
        {}
    }

}