/*
 * File:   battery_display.c
 * Author: bbhuv
 *
 * Created on 5 April, 2025
 */

// PIC16F877A Configuration Bit Settings

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage In-Circuit Serial Programming (RB3 as I/O)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits
#pragma config CP = OFF         // Flash Program Memory Code Protection bit

#include <xc.h>
#define _XTAL_FREQ 6000000

void Lcd_command(unsigned char);
void Lcd_Data(unsigned char);
void Lcd_Output_batt(unsigned int);
void keyscane();
void init();

unsigned char value;
unsigned int batt_volt = 155;  //  15.5V as 155
unsigned int bd1, bd2, bd3, bd4;  // 

void main(){
    init();
    while(1){
        keyscane();
    }
}

void init(){
    TRISC = 0x00;   // PORTC as output
    TRISD = 0x00;   // PORTD as output
    TRISB = 0xF0;   // RB4 to RB7 as input 1111 0000 
    PORTB = 0x00;
    OPTION_REG&=0x7F;//internal pull up 
    // LCD Initialization
    Lcd_command(0x38);
    __delay_ms(10);
    Lcd_command(0x06);
    __delay_ms(10);
    Lcd_command(0x0C);
    __delay_ms(10);
    Lcd_command(0x01);
    __delay_ms(10);}

void keyscane(){
    value = PORTB;
    switch(value){
        case 0xE0:  //show batt volt  //  
            Lcd_Output_batt(batt_volt);
            break;

        case 0xD0:  //inc volt 
            batt_volt++;
            if(batt_volt > 235){
                batt_volt = 235; 
            }
            Lcd_Output_batt(batt_volt);
            break;

        case 0xB0:  //dec volt
            batt_volt--; 
            if(batt_volt < 155){
                batt_volt = 155;
            }
            Lcd_Output_batt(batt_volt);
            break;

        case 0x70:  //reset volt 
            batt_volt = 155;
            Lcd_Output_batt(batt_volt);
            break;
    }
}

void Lcd_command(unsigned char i){
    PORTC &= ~0x08; // RS = 0
    PORTD = i;
    PORTC |= 0x01;  // EN = 1
    PORTC &= ~0x01; // EN = 0
    __delay_ms(10);
}

void Lcd_Data(unsigned char i){
    PORTC |= 0x08;  // RS = 1
    PORTD = i;
    PORTC |= 0x01;  // EN = 1
    PORTC &= ~0x01; // EN = 0
    __delay_ms(10);
}
void Lcd_line(const char*line){
    while(*line){
        Lcd_Data(*line++);
    }
}
void Lcd_Output_batt(unsigned int i){
    bd4 = (unsigned char)(i / 100);      154    //   hundreds  134    134 
    bd3 = (unsigned char)((i - (bd4 * 100)) / 10);      //            
    bd2 = (unsigned char)(i - (bd4 * 100) - (bd3 * 10));        //    

    Lcd_command(0x80);  // 0x80 
    Lcd_Data('B');Lcd_Data('A'); Lcd_Data('T'); Lcd_Data('T');Lcd_Data(':');Lcd_Data(' ');
    Lcd_Data(0x30 + bd4);      //1 
    Lcd_Data(0x30 + bd3);   //5   
    Lcd_Data('.'); //for decimal
    Lcd_Data(0x30 + bd2);    //4
    Lcd_Data(' '); Lcd_Data('V'); //15.4
    
    unsigned char limit;
    if (i >= 155 && i <= 175){
        limit=0;}//for low 
    else if(i >= 176 && i <= 205){
        limit=1;}//medium
    else if(i >= 206 && i <= 235){
        limit=2;}//higher
    Lcd_command(0xC0); 
    Lcd_line("BATTERY:");
    if(limit==0){
        Lcd_line("LOW    ");//left blank spaces for clearing        
    }
    else if(limit==1){
        Lcd_line("MEDIUM");
    }
    else{
         Lcd_line("HIGH  ");//spaces for clearing 
     }
    }
// status 
