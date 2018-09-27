#include <msp430.h> 

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
    //LED Setup
	P1DIR |= BIT0;                     // Set pin 1.0 to output

    //Button 1
	P1DIR &= ~BIT3;                    // Set pin 1.3 to input
	P1IE |=  BIT3;                     // Enable interupt on pin 1.3
	P1IES |= BIT3;                     // Detect falling edge
    P1REN &= ~BIT3;                     // Disable pullup
	P1IFG &= ~BIT3;                    // Clear Flag

    //Button 2
	P2DIR &= ~BIT5;                    // Set pin 2.5 to input
	P2IE |=  BIT5;                     // Enable interupt on pin 2.5
	P2IES |= BIT5;                     // Detect falling edge
	P2REN &= ~BIT5;                     // Disable pullup
	P2IFG &= ~BIT5;                    // Clear Flag

    //Timer A Setup
	CCTL0 = CCIE;                      // Enable CCR0 interrupt
	TACTL = TASSEL_1 + MC_1 + ID_3;    // Set Timer A to use aclk/8 on up mode
	TACCR0 = 400;





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

    if((P1IES & BIT3) != 0) //If its a falling edge
    {
        P1IES &= ~BIT3;                      // Detect Rising Edge

        TACTL = TACLR;

        TACTL = TASSEL_1 + MC_2 + ID_3;    // Set Timer A to use aclk/8 on cont. mode
    }
    else
    {
        TACTL = MC_0;                       // Stop Timer

        CCR0 = TAR;                         // Set new period

        TACTL = TASSEL_1 + MC_1 + ID_3;    // Set Timer A to use aclk/8 on up mode

        P1IES |= BIT3;                      // Detect Falling Edge
    }

    P1IFG &= ~BIT3;                    // Clear Flag
}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)

{
    TACCR0 = 400;                        // Reset to 10 Hz

    P2IFG &= ~BIT5;                    // Clear Flag
}
