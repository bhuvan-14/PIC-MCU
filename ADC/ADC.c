
#pragma config FOSC = EXTRC
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = OFF
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#include <xc.h>
#define _XTAL_FREQ 6000000

void adc_lcd_init();
void lcd_number_convert_ch1(unsigned int i);
void lcd_number_convert_ch2(unsigned int i);
void lcd_command(unsigned char);
void lcd_data(unsigned char);
unsigned int ch1 = 0xFFFF, ch2 = 0xFFFF;
unsigned char adc_high, adc_low,adc_volt;

void main() 
{
    adc_lcd_init();
    while (1)
    {//for ch1 
        ADCON0 = 0x81 | (1 << 3);// 001
        __delay_ms(5); 
        ADCON0 |= 0x04;
        while (ADCON0 & 0x04);
        unsigned int a_ch1 = ((ADRESH << 8) + ADRESL);
        if (a_ch1 != ch1)
        {
            ch1 = a_ch1;  
            lcd_number_convert_ch1(a_ch1);
        }
        //for ch2 from here 
        ADCON0 = 0x81 | (4 << 3);
        __delay_ms(5); 
        ADCON0 |= 0x04;
        while (ADCON0 & 0x04);
        unsigned int adc_ch2 = ((ADRESH << 8) + ADRESL);//calibrated
        unsigned long scaled = ((unsigned long)adc_ch2 * 135 + 511) / 1023;
        unsigned int new_ch2 = (unsigned int)scaled;
        if (new_ch2 != ch2)
        {
            ch2 = new_ch2;
            lcd_number_convert_ch2(new_ch2);
        }
    }
}
void lcd_number_convert_ch1(unsigned int i)
{
    lcd_command(0x80); // First line
    lcd_data('C');
    lcd_data('H');
    lcd_data('1');
    lcd_data(':');
    lcd_data(' ');
    //sending value by value to lcd 
    unsigned char d[4]; //1023
    d[0] = (i / 1000) % 10;  
    d[1] = (i / 100) % 10;
    d[2] = (i / 10) % 10;
    d[3] = i % 10;
    int start = 0; /// 1023 
    while (start < 3 && d[start] == 0)
    {
        lcd_data(' ');
        start++;
    }
    for (int j = start; j < 4; j++){
        lcd_data(0x30 + d[j]);}
    lcd_data('V');
}

void lcd_number_convert_ch2(unsigned int i)
{
    lcd_command(0xC0); // Move to second line
    lcd_data('C');
    lcd_data('H');
    lcd_data('4');
    lcd_data(':');
    lcd_data(' ');
//sending values of ch2 
    unsigned char d[3];
    d[0] = (i / 100) % 10;  100
    d[1] = (i / 10) % 10;
    d[2] = i % 10;
    if (i < 100)
        lcd_data(' ');
    else
        lcd_data(0x30 + d[0]); //

    if (i < 10)
        lcd_data(' ');
    else
        lcd_data(0x30 + d[1]);

    lcd_data(0x30 + d[2]);
    lcd_data('V');
}
void adc_lcd_init()
{
    TRISC = 0x00;  // Set P
    TRISD = 0x00;  // Set PORTD as output (LCD data pins)
    PORTD = 0x00;
    PORTC = 0x00;
    lcd_command(0x30); 
    __delay_ms(100);
    lcd_command(0x30); 
    __delay_ms(100);
    lcd_command(0x30); 
    __delay_ms(100);
    lcd_command(0x38); //n and f 
    __delay_ms(100); 
    lcd_command(0x06); 
    __delay_ms(100);  
    lcd_command(0x0C); //cursor
    __delay_ms(100); 
    lcd_command(0x01); //clr display
    __delay_ms(100);  
    ADCON1 = 0x8E; 
    ADCON0 = 0x81; 
    __delay_ms(10);
}
void lcd_command(unsigned char i){
    
    PORTC&=~0x08;//RS pin is 0 for command 
    PORTD=i;
    PORTC|=0x01;//enable pin is 1  HIGH
    PORTC&=~0x01;//enable pin is 0 LOW
    __delay_ms(100);

}
void lcd_data(unsigned char i){
    
    PORTC|=0x08;//RS pin is 1 for command 
    PORTD=i;
    PORTC|=0x01;//enable pin is 1  HIGH
    PORTC&=~0x01;//enable pin is 0 LOW
    __delay_ms(100);
}
