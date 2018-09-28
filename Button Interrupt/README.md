# Button Interrupt
## Summary of Code
This code toggles two LEDs by using a button interrupt. When the button is pressed an interrupt is triggered. Whatever LED was on is turned off and the LED that was turned off is turned on.
## Functionality of Code
A majority of this codes functionality lies in the interrupt. In the main function, the code setenable interrupts on Button 1 with a dectection for falling edge. When the button is pressed it is tied to ground. This makes the voltage on the button pin fall from high to low. The MSP detects this and runs the code inside the interrupt. The interrupt is setup y a few important lines of code:
```
// In main function
PxIE |= BITy;
PxIES |= BITy;
PxIFG &= ~BITy;

// Outside main function
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{

  PxIFG &= ~BITy;
}
```
PxIE enable interrupts on a pin x.y and PxIES sets the type of edge that is detected. In the case of this code PxIES is or-equaled to a bit because we want PxIES.y to be 1, which means it is detecting a falling edge like the push of a button. PxIFG is used to clear interrupt flags. If the flags are not cleared a new interrrupt cannot begin.
The ouside the main function is what runs when the interrupt is detected in port 1. After the code is excuted the interrupt flag needs to be cleared again, hence the PxIFG line at the end of the interrupt. Once the flag is cleared the code will return to normal operation.
