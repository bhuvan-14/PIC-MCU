This embedded systems project demonstrates the use of the internal Analog-to-Digital Converter (ADC) of the PIC16F877A microcontroller to read two analog input channels and display the measured voltages on a 16x2 LCD display. Channel 1 (CH1) shows the raw 10-bit ADC value (scaled as a voltage), and Channel 4 (CH4) is scaled to represent a calibrated voltage level with reduced resolution.

Features
Reads analog signals on:

CH1 (AN0 / RA0)

CH4 (AN3 / RA3)

Displays real-time voltage readings on a 16x2 LCD

Clears leading zeroes for better readability

CH4 voltage is scaled and calibrated (with a maximum mapped value of 135)

Hardware Requirements
PIC16F877A Microcontroller

16x2 LCD Display

Two analog voltage sources (e.g., potentiometers or sensors)

Crystal Oscillator (6 MHz)

Power Supply (5V)

Resistors and connection wires

Programmer (e.g., PICkit 3)

Pin Configuration
Pin	Function
RA0	Analog input CH1
RA3	Analog input CH4
PORTC	LCD Control (RS, EN)
PORTD	LCD Data (D0–D7)

Software Specifications
Language: Embedded C

Compiler: MPLAB XC8

Clock Frequency: 6 MHz

File Description
adc_dual_lcd.c
Main source code file implementing:

ADC channel switching and acquisition

LCD initialization and data display

Voltage formatting and display logic

Function Descriptions
main(): Main loop alternates between CH1 and CH4 ADC readings and updates the LCD if changes are detected.

adc_lcd_init(): Initializes ADC module and LCD interface.

lcd_number_convert_ch1(unsigned int): Converts and displays ADC result from CH1 on line 1 of LCD.

lcd_number_convert_ch2(unsigned int): Converts and displays scaled ADC result from CH4 on line 2 of LCD.

lcd_command(unsigned char): Sends command to LCD.

lcd_data(unsigned char): Sends data/characters to LCD.

LCD Output Example
CH1: 874V
CH4:  92V
CH1: Direct 10-bit ADC reading (0–1023), interpreted as voltage

CH4: Scaled using formula:
scaled_value = ((adc_ch2 * 135) + 511) / 1023
to represent calibration or sensor-mapped voltage (e.g., 0–13.5V range as 0–135 units)
