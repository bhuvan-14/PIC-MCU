This project demonstrates the use of external interrupts (INT0 on RB0) in the PIC16F877A microcontroller.

RB0 is connected to a push button to trigger the external interrupt.

RC3 is used to indicate that the interrupt routine is triggered.

RC0 is used in the main loop for conditional blinking.

RD4 blinks only when RC0 is LOW.

Pin Configuration
Pin	Function	Direction	Description
RB0	INT0 (External INT)	Input	Connected to push button
RC0	GPIO	Input	Controls RD4 blinking in thread
RC3	GPIO	Output	Toggles inside ISR
RD4	GPIO	Output	Blinks when RC0 is LOW
Working Logic
Main Thread (Polling Mode):

if ((PORTC & 0x01) == 0)
{
    // RC0 is LOW
    RD4 = ON (500ms)
    RD4 = OFF (500ms)
}
else
{
    RD4 = OFF;
}
 Interrupt Service Routine (ISR):
Triggered on falling edge of RB0 (INT0):


if (RB0 == 1)
{
    Toggle all bits of PORTC (RC3 blinks)
}

Set RC0 = 1;
Blink RC3 = 0x08 (RC3) ON/OFF with 500ms delay
Simulation or Hardware Requirements
PIC16F877A microcontroller

Button connected to RB0

LEDs on RC3, RC0, and RD4

6 MHz crystal (due to _XTAL_FREQ = 6000000)

MPLAB X IDE + XC8 Compiler or Proteus for simulation

 Build & Upload
Open project in MPLAB X IDE.

Ensure XC8 compiler is selected.

Build and upload to PIC16F877A.

Observe blinking LEDs based on button and interrupt.
