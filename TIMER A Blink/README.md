# TIMER A Blink
## Summary of Code
This program utilizes a capture compare register (CCR) and a timer module to blink an LED at a specific rate. When the timer reaches the value stored in the capture compare register, an interrupt is triggered. It is within this interrupt that the LED is toggled on or off.

## Functionality of Code
This code uses a Timer A module. Since we are only required to blink the LED at a specific rate I have chosen to set the module to up mode. This means that the timer will only count as high as the value in the CCR befor resetting. When the CCR value is reached, the interrupt begins and the LED is toggled. Since the timer is set to up mode, there is no need to reset the CCR or restart the timer: it will begin to count from zero after the interrupt has ended.

## Interrupt Logic
The interrupt code used for the G2553 is as follows:
```
CCTL0 = CCIE;                      // Enable CCR0 interrupt
TACTL = TASSEL_2 + MC_1 + ID_2;    // Set Timer A to use smclk/8 on up mode
CCR0 = 50000;                      // Set CCR0 to 50000
__bis_SR_register(LPM0_bits + GIE);

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
}
```
CCTL0 is the control register for the CCR0. Setting CCTL equal to CCIE enables the CCR interrupt. TACTL0 is the control register for the Timer A module. TASSEL controls which clock is used by the timer. ID is a clock divider and MC controls the timer mode. In this case we are using the SMCLK divided by 8 with the timer in up mode.

The interrupt code for the P401R behaves similarly, but requires much more complicated code that is unlike anything needed for the other boards.

```
    TA0CCTL0 = CCIE; // TACCR0 interrupt enabled
    TA0CCR0 = 400;
    TA0CTL = TIMER_A_CTL_SSEL__ACLK |
             TIMER_A_CTL_MC__UP | TIMER_A_CTL_ID_3; // ACLK/8, up mode

    SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;    // Enable sleep on exit from ISR

    // Ensures SLEEPONEXIT takes effect immediately
    __DSB();

    // Enable global interrupt
    __enable_irq();

    NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31);
    while (1)
    {
        __sleep();

    __no_operation();                   // For debugger
    }
    
void TA0_0_IRQHandler(void)
{
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG; // Turn off Interrupt Flag
}
```

The timer setup is the most similar, aside from a few macros. The main differences in macros is seen in the TA0CTL line. In the MSP430's it is possible to a macro and a number, such as "MC_2". For this board however the macros are extended to something like TIMER_A_CTL_MC_UP. Also different from the MSP430's is the need for sleep logic. Without it the code does not operate. Finally the interrupt is carried out by the statement enable_irq(); and a void statement, rather than a #pragma statement.
