#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	PM5CTL0 &= ~LOCKLPM5; //Unlocks GPIO pins

    P1DIR &= ~BIT1;                           //Sets Switch pin 1.1 to Input
    P1REN |= BIT1;                            //Enables pullup/pulldown resistors
    P1OUT |=  BIT1;                           //Set the resistor to be a pullup resistor



	P1DIR |= BIT0;                            // Set pin 1.0 to output
	P2DIR |= BIT0;                            // Set pin 2.0 to output
    P1OUT &= ~BIT0;                           // Initialize pin 1.0 as on
    P2OUT |= BIT0;                            // Initialize pin 2.0 as off

	P1IE |=  BIT1;                            // Enable interrupt on pin 1.1
    P1IES |= BIT1;                            // Detect falling edge
	P1IFG &= ~BIT1;                           // Clear Flag



	_BIS_SR(LPM4_bits + GIE);                 // Enter LPM4 w/interrupt
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  P2OUT ^= BIT0;                              // Toggle LED on pin 2.0
  P1OUT ^= BIT0;                              // Toggle LED on pin 1.0
  P1IFG &= ~BIT1;                             // Clear flag
}
