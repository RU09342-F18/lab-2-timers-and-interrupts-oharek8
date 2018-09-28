# Button Based Delay
## Summary of Code
This program sets the period of the LED blink however a button was held down for. It does this by using two interrupts: a timer and a button. A third interrupt is used for a reset button that resets the blink rate to 10 Hz.

## Functionality of Code
This code uses interrupts from the Button Interrupt and TIMER A assignmnets. The LED initially blinks at 10 Hz until the button is pressed. When the button is pressed and the interrupt is entered, the timer will stop and enter continuous mode. In countinuous mode the timer will keep going until the button is released or the Timer A register rolls over. In out case the clock is fairly slow, so the button can be held for a few seconds before the register hits its max. When the button is released, the current value in the Timer A register is stored in the capture compare register (CCR) and the timer is set back to normal operation. After the button interrupt has ended, the timer will use the new value in the CCR to determine its period.
