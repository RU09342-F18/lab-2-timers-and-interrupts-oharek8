#include <msp430.h> 

/**
 * main.c
 */

int numb = 0; //Tracks number of times button has been pressed

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1DIR |= BIT0;                     // Set pin 1.0 to output

	P1DIR &= ~BIT3;                    // Set pin 1.3 to input
	P1IE |=  BIT3;                     // Enable interupt on pin 1.3
	P1IES |= BIT3;                     // Detect falling edge
    P1REN |= BIT3;                     // Enable pullup
	P1IFG &= ~BIT3;                    // Clear Flag

	P2DIR &= ~BIT5;                    // Set pin 2.5 to input
	P2IE |=  BIT5;                     // Enable interupt on pin 2.5
	P2IES |= BIT5;                     // Detect falling edge
	P2REN |= BIT5;                     // Enable pullup
	P2IFG &= ~BIT5;                    // Clear Flag

	CCTL0 = CCIE;                      // Enable CCR0 interrupt
	TACTL = TASSEL_1 + MC_1 + ID_3;    // Set Timer A to use aclk/8 on up mode
	TACCR0 = 400;

	//Button Speed Logic



	__bis_SR_register(LPM0_bits + GIE);

	return 0;
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    P1OUT ^= BIT0;                 // Toggle LED at timer interrupt
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)

{
    numb++;

    TACCR0 = 4000/ numb;       // After first press, CCR0 is determined by number of button presses

    P1IFG &= ~BIT3;                    // Clear Flag
}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)

{
    TACCR0 = 400;                        // Reset to 10 Hz

    numb = 0;

    P2IFG &= ~BIT5;                    // Clear Flag
}
