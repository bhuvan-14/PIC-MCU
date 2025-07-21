This project demonstrates the use of Timer1 interrupt on the PIC16F877A microcontroller to control LED blinking on PORTC, while toggling PORTD after a set number of interrupts. Timer1 is configured with a 1:1 prescaler, and the interrupt is used to count intervals and toggle output.

Hardware Requirements
Microcontroller: PIC16F877A

Clock: 6 MHz RC oscillator

LEDs: Connected to PORTC and PORTD

Power Supply: 5V regulated

MPLAB X IDE + XC8 Compiler

 Files
timer_int.c – Main program source file

Key Concepts
Timer1 setup and enabling

Global and peripheral interrupts

LED toggling using PORTC and PORTD

Use of interrupt service routine (ISR)

⚙️ Configuration Bits

#pragma config FOSC = EXTRC     // RC oscillator
#pragma config WDTE = OFF       // Watchdog Timer disabled
#pragma config PWRTE = OFF      // Power-up Timer disabled
#pragma config BOREN = OFF      // Brown-out Reset disabled
#pragma config LVP = OFF        // Low-voltage Programming disabled
#pragma config CPD = OFF        // Data EEPROM protection disabled
#pragma config WRT = OFF        // Flash Program Memory Write Enable off
#pragma config CP = OFF         // Code Protection off
 How It Works
Timer1 is initialized using T1CON = 0x01 (1:1 prescaler, Timer1 enabled).

Interrupts:

GIE and PEIE are enabled in INTCON.

TMR1IE enabled in PIE1.

ISR (Interrupt Service Routine):

Triggered when Timer1 overflows.

A counter increments every interrupt.

On reaching count == 23, PORTD is toggled and counter reset.

PORTC blinks independently every 500ms in main().

Flow Overview


 Notes
#define _XTAL_FREQ 6000000 is required for accurate __delay_ms().

Timer interrupt frequency depends on the instruction cycle and prescaler settings.

Adjust count value depending on desired toggling interval.

Output Behavior
PORTC: All LEDs ON and OFF every 500ms.

PORTD: Toggled every 23 Timer1 interrupts.
