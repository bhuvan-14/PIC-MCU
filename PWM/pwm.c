/*
 * File:   pwmclass.c
 * Author: bbhuv
 *
 * Created on 13 April, 2025, 11:59 AM
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
unsigned char pwm_20high,pwm_20low;
unsigned char pwm_60high,pwm_60low;
unsigned char pwm_90high,pwm_90low;

void pwm_init(void);
void pwm_dutycycleupdate(void);
void main(void) {
    pwm_init();
    while(1){  
        pwm_dutycycleupdate();}   }
void pwm_init(void){
    TRISC=0xFB; //1111 1011 pin config  rc2 
    CCP1CON=0x0C; //ccp control will be high for 0000 1100 
    PR2=0x2D; //period fixing  0010 1110  
    T2CON=0X06; //tm2on -1 and t2clk-1
    pwm_20high=0x09;  //0000 1001 
    pwm_20low=0x02; //last two bits of 10
    pwm_60high=0x1C;//0001 1100
    pwm_60low=0x01;//01
    pwm_90high=0x2A; //0010 1010
    pwm_90low=0x00;//01
}//10 8msb-ccp1rl 2 con 4,5
void pwm_dutycycleupdate(void){ //10 bit  //ccp1con 4-5 
    CCPR1L=pwm_20high;           //20% high   
    CCP1CON=  (CCP1CON&0xCF)|(pwm_20low<<4);           //20% CCP1CON(5:4)
    __delay_ms(3000);
    CCPR1L=   pwm_60high;           //60%high
    CCP1CON= (CCP1CON&0xCF)|(pwm_60low<<4);            //60% CCP1CON(5:4)
    __delay_ms(3000);
    CCPR1L=    pwm_90high;          //90% high
    CCP1CON=   (CCP1CON&0xCF)|(pwm_90low<<4);          //90% CCP1CON(5:4)
    __delay_ms(3000);}
