This project demonstrates switch-controlled LED blinking using the PIC16F877A microcontroller. It contains two programs:

Pull-Down Configuration
Pull-Up Configuration

Both use PORTC for switch input and PORTD for LED output.

Pull-Down Configuration
File: pulldown.c
Description:
Switches are connected to RC0 to RC3.

Pull-down resistors ensure logic LOW when switches are not pressed.

When a switch is pressed, it pulls the pin HIGH.

Depending on the input, LEDs connected to RD3 and RD5 are controlled.

Key Code Logic:
TRISC = 0x0F;  // RC0-RC3 as input (switches)
TRISD = 0x00;  // RD0-RD7 as output (LEDs)

PORTC = 0x00;  // Initialize PORTC to low
PORTD = 0x00;  // Initialize PORTD to low

value = PORTC; // Read switch input

switch(value) {
    case 0x01: PORTD = 0x20; break;  // Switch 1 → RD5 ON
    case 0x02: PORTD = 0x08; break;  // Switch 2 → RD3 ON
    case 0x04: PORTD = 0x28; break;  // Switch 3 → RD3 and RD5 ON
    case 0x08: PORTD = 0x00; break;  // Switch 4 → All OFF
}
Pull-Up Configuration
File: pullup.c

Description:
Switches are connected to RC0 to RC3.

Internal or external pull-up resistors ensure logic HIGH when switches are not pressed.

Pressing a switch pulls the pin LOW.

The logic is inverted compared to pull-down. Active switch = LOW input.

Key Code Logic:
TRISC = 0x0F;  // RC0-RC3 as input (switches)
TRISD = 0x00;  // RD0-RD7 as output (LEDs)

PORTC = 0x0F;  // Enable pull-up logic
PORTD = 0x00;  // Initialize PORTD to low

value = PORTC; // Read switch input

switch(value) {
    case 0x0E: PORTD = 0x20; break;  // RC0 pressed → RD5 ON
    case 0x0D: PORTD = 0x08; break;  // RC1 pressed → RD3 ON
    case 0x0B: PORTD = 0x28; break;  // RC2 pressed → RD3 and RD5 ON
    case 0x07: PORTD = 0x00; break;  // RC3 pressed → All OFF
}
