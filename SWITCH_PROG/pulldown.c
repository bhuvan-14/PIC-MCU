/*
 * File:   pulldown1.c
 * Author: bbhuv
 *
 * Created on 2 March, 2025, 4:22 PM
 */
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 6000000

 unsigned char value;

void main() {
    TRISC = 0x0F; // 0000 0000 making RC0-RC3 as switch off that is 0 
    TRISD = 0x00; // 0000 0000 
    
    PORTC=0x00;//keeping all in low 0000 0000
    PORTD=0x00;//keeping all in low 0000 0000 
    
    while(1){
        value=PORTC;
        switch(value){
            case 0x01:PORTD=0x20; //0010 0000 setting RD5 as high for LED blink   
            break;
            
            case 0x02:PORTD=0x08;//0000 1000 setting RD3 as high 
            break;
            
            case 0x04:PORTD=0x28;//0010 1000 setting RD3 and RD5 as high for LED blink
            break;
            
            case 0x08:PORTD=0x00;//0000 0000     
            break;
            
        }
    }
}

