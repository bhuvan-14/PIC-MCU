This embedded project demonstrates how to monitor a simulated battery voltage using the PIC16F877A microcontroller and display it on a 16x2 character LCD. The voltage value can be adjusted using four buttons connected to PORTB. Based on the voltage range, the system categorizes the battery level into LOW, MEDIUM, or HIGH and displays the status on the second line of the LCD.

Features
Displays battery voltage in XX.X V format
Provides status messages:
LOW for voltages between 15.5V and 17.5V
MEDIUM for voltages between 17.6V and 20.5V
HIGH for voltages between 20.6V and 23.5V

Supports user input via push buttons:

RB4 (0xE0): Display voltage and status

RB5 (0xD0): Increment voltage

RB6 (0xB0): Decrement voltage

RB7 (0x70): Reset voltage to 15.5V

Hardware Requirements
PIC16F877A Microcontroller

16x2 LCD Display

4 Push Buttons (connected to RB4–RB7)

Resistors (for pull-up configuration)

Crystal oscillator (6 MHz, as per _XTAL_FREQ)

Power Supply (5V)

Programming Interface (e.g., PICkit 3)

Pin Configuration
Port	Pin Usage	Description
PORTB	RB4–RB7	Input buttons
PORTC	RC0, RC3	LCD Control Pins (EN, RS)
PORTD	RD0–RD7	LCD Data Pins (D0–D7)

Software Specifications
Language: Embedded C

Compiler: MPLAB XC8

Clock Frequency: 6 MHz

File Description
battery_display.c
Main source code file containing:

LCD initialization and interfacing routines

Logic to simulate battery voltage level

Display formatting functions

Key scanning and status determination

Function Descriptions
init(): Initializes I/O ports and LCD display

keyscane(): Detects button presses and updates the voltage value accordingly

Lcd_command(unsigned char): Sends a command to the LCD

Lcd_Data(unsigned char): Sends data/characters to the LCD

Lcd_line(const char*): Sends a full line of characters to the LCD

Lcd_Output_batt(unsigned int): Displays voltage value and battery status based on predefined ranges

LCD Output Example

Line 1: BATT: 15.4 V
Line 2: BATTERY:LOW
Voltage Range to Status Mapping
Voltage (Simulated)	Status
15.5V – 17.5V	LOW
17.6V – 20.5V	MEDIUM
20.6V – 23.5V	HIGH
