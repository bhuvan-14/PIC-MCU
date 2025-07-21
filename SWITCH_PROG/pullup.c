/*
 * File:   pullup1.c
 * Author: bbhuv
 *
 * Created on 2 March, 2025, 4:22 PM
 */
// PIC16F877A Configuration Bit Settings

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define _XTAL_FREQ 6000000

unsigned char value;

void main() {
    TRISC = 0x0F;   // RC0–RC3 as input
    TRISD = 0x00;   // PORTD as output

    PORTC = 0xFF;   // Enable pull-ups manually via external resistors (or use PORTB if internal pull-ups are needed)
    PORTD = 0x00;

    while(1){
        value = PORTC & 0x0F; // Masking only RC0–RC3
        switch(value){
            case 0x0E: PORTD = 0x20; // RC0 pressed (0000 1110)
            break;
            
            case 0x0D: PORTD = 0x08; // RC1 pressed (0000 1101)
            break;
            
            case 0x0B: PORTD = 0x28; // RC2 pressed (0000 1011)
            break;
            
            case 0x07: PORTD = 0x00; // RC3 pressed (0000 0111)
            break;
        }
    }
}
