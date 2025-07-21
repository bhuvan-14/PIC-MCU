This project demonstrates UART-based serial communication between two PIC16F877A microcontrollers configured in master-slave architecture. The master sends a command when specific button combinations are pressed, and the slave receives, decodes, and sends a response back. The slave also displays the received and transmitted data on an LCD.

Hardware Requirements
2x PIC16F877A microcontrollers

16x2 LCD (connected to the slave)

Tactile push buttons (connected to PORTB of master)

UART (TX/RX cross-connected between Master ↔ Slave)

6 MHz crystal oscillator

Resistors, breadboard, jumper wires

Power Supply (5V)

PIC Programmer (e.g., PICkit3)

 Communication Protocol
Master Device
Monitors button status using PORTB.

Sends command bytes 'A', 'B', 'C', 'D' when specific button patterns are detected.

Waits for slave’s response via UART.

If correct response is received ('a', 'b', 'c', 'd'), updates PORTD accordingly (e.g., to control LEDs).

Slave Device
Receives UART data using RCREG.

Displays received character on LCD ("RECEIVED DATA").

Sends back the lowercase equivalent of the received character ('a' to 'd').

Displays the transmitted response on LCD ("TRANSMIT DATA").

 Pin Configuration
Function	Master (PIC1)	Slave (PIC2)
TX	RC6	RC6
RX	RC7	RC7
LCD Data	N/A	PORTD
LCD Control	N/A	PORTB.3(RS), B0(EN)
Buttons	PORTB (Upper)	N/A
Output Display	PORTD	LCD

Note: TX of master connects to RX of slave and vice versa.

File Descriptions
uart_master.c
Implements the master logic:

UART initialization at 9600 baud

Button detection via PORTB

Sends 'A', 'B', 'C', 'D' and waits for reply

Validates response ('a'-'d') and updates PORTD

uart_slave.c
Implements the slave logic:

Initializes UART and LCD

Continuously listens for data on RX

Displays received char and sends mapped response

Displays both received and transmitted chars on LCD

Example Operation
Master Button Pattern	Master Sends	Slave Responds	Master Action (PORTD)	Slave LCD Output
0xE0	'A'	'a'	PORTD = 0x60	RECEIVED DATA: A
TRANSMIT DATA: a
0xD0	'B'	'b'	PORTD = 0x02	RECEIVED DATA: B
TRANSMIT DATA: b
0xB0	'C'	'c'	PORTD = 0x00	RECEIVED DATA: C
TRANSMIT DATA: c
0x70	'D'	'd'	PORTD = 0x42	RECEIVED DATA: D
TRANSMIT DATA: d

UART Configuration
Baud Rate: 9600

Formula: SPBRG = (Fosc / (64 * Baud)) - 1
With Fosc = 6 MHz → SPBRG = 9

TXSTA = 0x20: Enable transmitter

RCSTA = 0x90: Enable serial port and receiver

LCD Connection (Slave)
Data lines: PORTD

RS: PORTB.3 (bit 3)

EN: PORTB.0 (bit 0)

LCD displays:
RECEIVED DATA: X
TRANSMIT DATA: x
Where X is the received uppercase command and x is the returned response.
