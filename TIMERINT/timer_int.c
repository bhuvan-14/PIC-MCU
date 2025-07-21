/*
 * File:   timer_int.c
 * Author: bbhuv
 *
 * Created on 18 June, 2025, 4:29 PM
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
unsigned char count=0; 

void _timer1_init(void);

void main() {
    _timer1_init();
    while(1){
        PORTC=0xFF;
        __delay_ms(500);
        PORTC=0x00;
        __delay_ms(500);
    }
}
void _timer1_init(){
    TRISC=0x00;
    TRISD=0x00;
    PORTD=0x00;
    PORTC=0x00;
    
    T1CON=0x01;//1:1 prescalar 0th bit is on as to on the timer
    INTCON |=(3<<6);//GIE and PIE
    PIE1 |=(1<<0) ;//TMR1IE enable
    PIR1&=~(1<<0); // TRM1IF clr flag   
}
void __interrupt()_ISR(void){
    if(PIR1 & 0x01){
        count++;
        if(count==23){
            PORTD=~PORTD;// if entered in the inteerupt the portc is low 
            count=0; 
        }
        PIR1&=~(1<<0); // TRM1IF clr flag 
        
    }
}


