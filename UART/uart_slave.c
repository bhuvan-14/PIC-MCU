/*
 * File:   uart_slave_1_task.c
 * Author: bbhuv
 *
 * Created on 28 May, 2025, 11:35 AM
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

void uart_init(void);//init function 
void Lcd_Command(unsigned char); //command function
void Lcd_Data(unsigned char);//data function
void Lcd_Init(void);//lcd init function

unsigned char rx_input; // receiver fn
unsigned char trans_data; // transmit data fn 

void main(void) {
    uart_init();//calling
    Lcd_Init();//calling
    //command for each word
    Lcd_Command(0x80); 
    Lcd_Data('R');
    Lcd_Command(0x81); 
    Lcd_Data('E');
    Lcd_Command(0x82); 
    Lcd_Data('C');
    Lcd_Command(0x83); 
    Lcd_Data('E');
    Lcd_Command(0x84); 
    Lcd_Data('I');
    Lcd_Command(0x85); 
    Lcd_Data('V');
    Lcd_Command(0x86); 
    Lcd_Data('E');
    Lcd_Command(0x87); 
    Lcd_Data('D');
    Lcd_Command(0x89); 
    Lcd_Data('D');
    Lcd_Command(0x8A); 
    Lcd_Data('A');
    Lcd_Command(0x8B); 
    Lcd_Data('T');
    Lcd_Command(0x8C); 
    Lcd_Data('A');
    Lcd_Command(0x8D); 
    Lcd_Data(':');
    
    //transmit

    Lcd_Command(0xC0); 
    Lcd_Data('T');
    Lcd_Command(0xC1); 
    Lcd_Data('R');
    Lcd_Command(0xC2); 
    Lcd_Data('A');
    Lcd_Command(0xC3); 
    Lcd_Data('N');
    Lcd_Command(0xC4); 
    Lcd_Data('S');
    Lcd_Command(0xC5); 
    Lcd_Data('M');
    Lcd_Command(0xC6); 
    Lcd_Data('I');
    Lcd_Command(0xC7); 
    Lcd_Data('T');
    Lcd_Command(0xC9); 
    Lcd_Data('D');
    Lcd_Command(0xCA); 
    Lcd_Data('A');
    Lcd_Command(0xCB); 
    Lcd_Data('T');
    Lcd_Command(0xCC); 
    Lcd_Data('A');
    Lcd_Command(0xCD); 
    Lcd_Data(':');
    

    while (1) {

        if (PIR1 & 0x20) {
            rx_input = RCREG;
            Lcd_Command(0x8E); //start from 8E 
            Lcd_Data(rx_input);
            //switch case implementation for rx data and tx data
            switch(rx_input) {
                case 'A': trans_data = 'a'; break;
                case 'B': trans_data = 'b'; break;
                case 'C': trans_data = 'c'; break;
                case 'D': trans_data = 'd'; break;
                
            }
            //tx stored data
            TXREG = trans_data;
            Lcd_Command(0xCE); //started from CE
            Lcd_Data(trans_data);
        }
    }
}

void uart_init(void) {
    TRISD = 0x00;
    TRISB = 0x00;
    TRISC = 0xC0;//1100 0000 to enable uart bit7-6 shld be enable 
    TXSTA = 0x20;// 0010 0000 5th bit is enable  2nd bit we need to chk for baud rate whether low or high 
    SPBRG = 0x09;//X=(6000000/64(9600))-1 9600 is baud rate 
    RCSTA = 0x90;//1001 0000  as bit 7 is tx and rx enable and bit 4 is continous serial ommunication 
}
//initialization
void Lcd_Init(void) {
    Lcd_Command(0x30); //0x30
    __delay_ms(100);
    Lcd_Command(0x30); 
    __delay_ms(100);
    Lcd_Command(0x30); 
    __delay_ms(100);
    Lcd_Command(0x38); //n and f 
    __delay_ms(100);
    Lcd_Command(0x0C); 
    __delay_ms(100);
    Lcd_Command(0x01); 
    __delay_ms(100);
}

void Lcd_Command(unsigned char i) {
    PORTB &= ~0x08;   // RS = 0
    PORTD = i;
    PORTB |= 0x01;    // EN = 1
    __delay_ms(10);
    PORTB &= ~0x01;   // EN = 0
}

void Lcd_Data(unsigned char i) {
    PORTB |= 0x08;    // RS = 1
    PORTD = i;
    PORTB |= 0x01;    // EN = 1
    __delay_ms(10);
    PORTB &= ~0x01;   // EN = 0
}

