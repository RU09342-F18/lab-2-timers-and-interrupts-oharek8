#include <msp430.h> 
// Kevin O'hare
// oharek8@students.rowan.edu

/*
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//LED Setup
    P1DIR |= BIT0;                     // Set pin 1.0 to output

    //Button 1
    P1DIR &= ~BIT1;                    // Set pin 1.1 to input
    P1IE |=  BIT1;                     // Enable interupt on pin 1.1
    P1IES |= BIT1;                     // Detect falling edge
    P1REN |= BIT1;                     // Disable pullup
    P1OUT |= BIT1;                     // Set resistor to pullup
    P1IFG &= ~BIT1;                    // Clear Flag

    //Button 2
    P2DIR &= ~BIT1;                    // Set pin 2.1 to input
    P2IE |=  BIT1;                     // Enable interupt on pin 2.1
    P2IES |= BIT1;                     // Detect falling edge
    P2REN |= BIT1;                     // Disable pullup
    P2OUT |= BIT1;                     // Set resistor to pullup
    P2IFG &= ~BIT1;                    // Clear Flag

    //Timer A Setup
    TA0CCTL0 = CCIE;                      // Enable CCR0 interrupt
    TA0CTL = TASSEL_1 + MC_1 + ID_3;    // Set Timer A to use aclk/8 on up mode
    TA0CCR0 = 400;

    __bis_SR_register(GIE);
    while(1);
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    P1OUT ^= BIT0;                 // Toggle LED at timer interrupt
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)

{

    if((P1IES & BIT1) != 0) //If its a falling edge
    {
        P1IES &= ~BIT1;                      // Detect Rising Edge

        TA0CTL = TACLR;

        TA0CTL = TASSEL_1 + MC_2 + ID_3;    // Set Timer A to use aclk/8 on cont. mode
    }
    else
    {
        TA0CTL = MC_0;                       // Stop Timer

        TA0CCR0 = TA0R;                         // Set new period

        TA0CTL = TASSEL_1 + MC_1 + ID_3;    // Set Timer A to use aclk/8 on up mode

        P1IES |= BIT1;                      // Detect Falling Edge
    }

    P1IFG &= ~BIT1;                    // Clear Flag
}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)

{
    TA0CCR0 = 400;                        // Reset to 10 Hz

    P2IFG &= ~BIT1;                    // Clear Flag
}
