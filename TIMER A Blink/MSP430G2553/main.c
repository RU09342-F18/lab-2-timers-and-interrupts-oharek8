#include <msp430.h> 
// Kevin O'hare
// oharek8@students.rowan.edu

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1DIR |= BIT0;                     // Set pin 1.0 to output
	CCTL0 = CCIE;                      // Enable CCR0 interrupt
	TACTL = TASSEL_2 + MC_1 + ID_3;    // Set Timer A to use smclk/8 on up mode
	CCR0 = 50000;                      // Set CCR0 to 50000
	__bis_SR_register(LPM0_bits + GIE);

	return 0;
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    P1OUT ^= BIT0;                     // Toggle LED at timer interrupt
}
