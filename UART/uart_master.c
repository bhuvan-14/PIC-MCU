/*
 * File:   uart_task_master.c
 * Author: bbhuv
 *
 * Created on 28 May, 2025, 11:01 AM
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

void uart_init();
unsigned char value, rx_char;

void main() {
    uart_init();
    while (1) {
        value = PORTB;
        switch (value) {
            case 0xE0: // case when button is pressed
                TXREG = 'A'; // A is sent 
                __delay_ms(1);
                while (!(PIR1 & 0x20));
                rx_char = RCREG;
                if (rx_char == 'a')
                    PORTD = 0x60; // in return 'a' is sent back 
                break;
            case 0xD0:
                TXREG = 'B'; // same as A does when B sis send from master to slave , b is send slave to master
                __delay_ms(1);
                while (!(PIR1 & 0x20));
                rx_char = RCREG;
                if (rx_char == 'b')
                    PORTD = 0x02;
                break;
            case 0xB0:
                TXREG = 'C';
                __delay_ms(1);
                while (!(PIR1 & 0x20));
                rx_char = RCREG;
                if (rx_char == 'c')
                    PORTD = 0x00;
                break;
            case 0x70:
                TXREG = 'D';
                __delay_ms(1);
                while (!(PIR1 & 0x20));
                rx_char = RCREG;
                if (rx_char == 'd')
                    PORTD = 0x42;
                break;
        }
    }
}

void uart_init() {
    TRISB = 0xF0;
    PORTB = 0x00;
    TRISD = 0x00;
    PORTD = 0x00;
    OPTION_REG &= 0x7F; // option reg when 7th bit is enable
    TRISC = 0xC0; //1100 0000 to enable uart bit7-6 shld be enable 
    TXSTA = 0x20;// 0010 0000 5th bit is enable  2nd bit we need to chk for baud rate whether low or high 
    SPBRG = 0x09;//X=(6000000/64(9600))-1 9600 is baud rate 
    RCSTA = 0x90;//1001 0000  as bit 7 is tx and rx enable and bit 4 is continous serial ommunication   
}
