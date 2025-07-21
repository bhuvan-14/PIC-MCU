This project blinks an LED connected to pin RD4 of the PIC16F877A microcontroller. The LED turns ON for 2 seconds and then OFF for 2 seconds in a loop.

Requirements
PIC16F877A
MPLAB X IDE
XC8 Compiler
Breadboard, LED, Resistor
Power Supply (5V)

Code Summary
Sets PORTD as output.

Blinks RD4 ON and OFF every 2 seconds.
TRISD = 0x00;       // Set PORTD as output
PORTD = 0x10;       // RD4 HIGH
__delay_ms(2000);   // Wait 2 sec
PORTD = 0x00;       // All PORTD LOW
__delay_ms(2000);   // Wait 2 sec
How to Use
Open project in MPLAB X IDE.
Connect LED to RD4 via resistor.
Build and upload code to PIC16F877A.
See LED blinking every 2 seconds.

