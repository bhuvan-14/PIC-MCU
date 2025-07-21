#include <xc.h>
#include "config.h"
#include "I2C_EEPROM.h"
#define _XTAL_FREQ 16000000

void main(void) {

    I2C_Master_Init(100000);
    EEPROM_Write(0x0023, 'A');__delay_ms(10);  // Write 'A' at 0x0023
    EEPROM_Write(0x0028, 'B'); __delay_ms(10); // Write 'B' at 0x0028
    EEPROM_Write(0x0036, 'C'); __delay_ms(10); // Write 'C' at 0x0036
    __delay_ms(10);                  
    TRISD=0x00;
     PORTD = EEPROM_Read(0x0023);  //  output 0x41 A
    __delay_ms(3000);             
    PORTD = EEPROM_Read(0x0028);  // output 0x42 B
    __delay_ms(3000);
    PORTD = EEPROM_Read(0x0036);  //  output 0x43 C
    __delay_ms(3000);
    while(1)
    {
    }
    return;
}
