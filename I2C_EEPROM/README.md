This project demonstrates how to interface a 24Cxx series I2C EEPROM with the PIC16F877A microcontroller. It includes both the EEPROM driver (I2C_EEPROM.c) and an example main.c program that performs byte write and read operations to/from EEPROM, displaying data on PORTD.

Hardware Requirements
PIC16F877A

I2C EEPROM (e.g., 24C02/24C04/24C08)

16 MHz Crystal Oscillator

PORTD LEDs (for observing output)

Pull-up resistors (4.7kΩ) on SDA (RC4) and SCL (RC3)

I2C_Master_Init(100000); // Initialize I2C at 100kHz
EEPROM Write & Read

EEPROM_Write(0x0023, 'A'); // Write ASCII 'A' to address 0x0023
PORTD = EEPROM_Read(0x0023); // Read and output on PORTD (0x41)
main.c Overview

#include <xc.h>
#include "config.h"
#include "I2C_EEPROM.h"
#define _XTAL_FREQ 16000000

void main(void) {
    I2C_Master_Init(100000); // Init I2C at 100kHz

     EEPROM Write: 'A' at 0x0023, 'B' at 0x0028, 'C' at 0x0036
    EEPROM_Write(0x0023, 'A'); __delay_ms(10);
    EEPROM_Write(0x0028, 'B'); __delay_ms(10);
    EEPROM_Write(0x0036, 'C'); __delay_ms(10);

    TRISD = 0x00; // Set PORTD as output

     EEPROM Read and Display on PORTD (with 3s delay)
    PORTD = EEPROM_Read(0x0023); // Output 0x41 ('A')
    __delay_ms(3000);

    PORTD = EEPROM_Read(0x0028); // Output 0x42 ('B')
    __delay_ms(3000);

    PORTD = EEPROM_Read(0x0036); // Output 0x43 ('C')
    __delay_ms(3000);

    while (1) { } // Infinite loop
}
 I2C EEPROM Driver Features (I2C_EEPROM.c)
EEPROM_Write(): Write a single byte to a 16-bit address.

EEPROM_Read(): Read a single byte from a 16-bit address.

EEPROM_Write_Page(): Write multiple bytes sequentially.

EEPROM_Read_Page(): Read multiple bytes sequentially.

All I2C low-level functions are custom-implemented (start, stop, ACK, NACK, etc.).

 Configuration (config.h)

#pragma config FOSC = HS        // High-Speed oscillator
#pragma config WDTE = OFF       // Watchdog Timer disabled
#pragma config PWRTE = ON       // Power-up Timer enabled
#pragma config BOREN = ON       // Brown-out Reset enabled
#pragma config LVP = OFF        // Low Voltage ICSP disabled
#pragma config CPD = OFF        // Data EEPROM memory code protection off
#pragma config WRT = OFF        // Flash Program Memory Write Enable off
#pragma config CP = OFF         // Flash Program Memory Code Protection off
 Expected Output
EEPROM Address	Character	PORTD Output
0x0023	'A'	0x41
0x0028	'B'	0x42
0x0036	'C'	0x43

Each character is shown for 3 seconds on the connected PORTD LEDs.

 How to Use
Connect EEPROM (24Cxx) to RC3 (SCL) and RC4 (SDA).

Add pull-up resistors (4.7kΩ) on SCL and SDA lines.

Flash the program to PIC16F877A using MPLAB X and XC8.

Observe PORTD LEDs lighting up as ASCII data from EEPROM is displayed.
