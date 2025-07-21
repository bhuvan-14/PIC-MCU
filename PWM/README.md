This project demonstrates the use of the Capture/Compare/PWM (CCP) module of the PIC16F877A microcontroller to generate PWM signals with varying duty cycles. The program cycles through three predefined duty cycles: 20%, 60%, and 90%, with a delay between transitions.

The PWM signal is output on the RC2 pin (CCP1), suitable for controlling devices like motors, LEDs, or servos in embedded applications.

Features
Generates a PWM signal on CCP1 (RC2)

Cycles through three duty cycles:

20%
60%
90%

Delay of 3 seconds between each cycle

Uses Timer2 as the time base for PWM generation

Hardware Requirements
PIC16F877A microcontroller

Output device (e.g., oscilloscope, motor, or LED with driver)

Power supply (5V)

Crystal oscillator (6 MHz)

Programming hardware (e.g., PICkit 3)

Pin Configuration
Port	Pin	Function
RC2	17	CCP1 Output

Software Specifications
Language: Embedded C

Compiler: MPLAB XC8

Clock Frequency: 6 MHz

File Description
pwmclass.c
Main source file implementing:

PWM initialization using CCP1 module

Duty cycle control logic with 10-bit resolution

Infinite loop to continuously rotate between the three PWM values

Function Descriptions
pwm_init(): Configures CCP1 for PWM mode, sets up Timer2, and initializes predefined duty cycle values.

pwm_dutycycleupdate(): Sequentially applies 20%, 60%, and 90% duty cycles by setting the appropriate 10-bit values to CCPR1L and CCP1CON<5:4>.

PWM Duty Cycle Calculation
PWM duty cycle in 10-bit mode:

8 MSBs go into CCPR1L

2 LSBs go into CCP1CON<5:4>

Duty cycle formula:
Duty (%) = (PWM_Value / 1023) * 100
PWM_Value = (CCPR1L << 2) | (CCP1CON bits 5 and 4)
PWM Settings Summary
Duty Cycle	CCPR1L	CCP1CON<5:4>	10-bit Value
20%	0x09	0x02	0x24 (36)
60%	0x1C	0x01	0x71 (113)
90%	0x2A	0x00	0xA8 (168)
