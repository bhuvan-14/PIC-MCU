/*
 * File:   int_class.c
 * Author: bbhuv
 *
 * Created on 12 June, 2025, 4:40 PM
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

void main(void) {
    TRISB=0x01;//RB0 button is connected
    TRISC=0x00;//keeping all as op 
    TRISD=0x00;//keeping all as op 
    PORTB=0x00;
    PORTC=0x00;
    PORTD=0x00;
    OPTION_REG &=0xBF;// 1011 1111 Faliing edge  // for Rising edge set for 0x40
    INTCON &=~0x02;//INTF clearling this bit 1st bit
    INTCON |=0x90;//INTE -4th bit and GIE- 7th bit are set 
    
    //thread mode
    while(1){
         if ((PORTC & 0x01) == 0) {  
            PORTD = 0x10;          // RD4 ON
            __delay_ms(500);
            PORTD = 0x00;          // RD4 OFF
            __delay_ms(500);
        } else {
            PORTD = 0x00;          //off
        }
    }
}

void __interrupt() _ISR(void){
    //handler mode , if it enters the interrupt mode then rc3 blinks
    if(INTCON&0x02){
        value=PORTB;
        if(value&0x01){
            PORTC=~PORTC;//RC3 blinks 
        }
        PORTC |=0x01;
        INTCON &=~0x02; 
        PORTC=0x08;
        __delay_ms(500);
        PORTC=0x00;
        __delay_ms(500);
        
    }
}

