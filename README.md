This repository contains embedded systems projects and programs developed using the PIC16F877A microcontroller. It includes modules and drivers for GPIO, ADC, PWM, Timers, UART, I²C, SPI, and more. The goal is to provide reusable, modular code for academic and prototyping purposes using MPLAB X IDE and the XC8 compiler.

Target Microcontroller: PIC16F877A
The PIC16F877A is an 8-bit RISC microcontroller from Microchip, widely used for control, sensing, and automation applications.

Core Architecture
8-bit Harvard RISC Architecture

14-bit instruction width

Program Memory: 8 KB (Flash)

Data Memory: 368 Bytes (SRAM)

EEPROM: 256 Bytes (on-chip)

Operating Speed: Up to 20 MHz

Instruction Cycle: 4 clock cycles

GPIO Overview
33 Programmable I/O Pins

5 Ports: PORTA, PORTB, PORTC, PORTD, PORTE

PORTA and PORTE support analog input

PORTB supports interrupt-on-change

TRIS registers control direction (input/output)

Capable of sourcing/sinking up to 25 mA per pin

 Configuration Details
Supports High-Speed (HS) or RC Oscillator

Watchdog Timer, Power-up Timer, and Brown-out Reset options

Low-Voltage Programming (LVP) can be disabled

Configuration bits are defined via pragma statements in code

External crystal (commonly 4/8/16 MHz) recommended for stable timing

 Peripheral Modules
GPIO (General Purpose I/O)
Digital input/output control

Pull-up resistors on PORTB

Interrupt-on-change (RB0)

ADC (Analog-to-Digital Converter)
10-bit resolution

8 selectable analog channels

Voltage reference configurable

Used for sensors and analog signal input

PWM (Pulse Width Modulation)
Two PWM modules: CCP1 and CCP2

10-bit resolution

Useful for motor control, LED dimming, etc.

Timer2 is used to generate PWM frequency

Timers
Timer0: 8-bit, used for delays and counters

Timer1: 16-bit, supports external clock

Timer2: 8-bit, used for PWM generation

All timers support interrupts

UART (USART)
Full-duplex asynchronous serial communication

TX and RX available on RC6 and RC7

Configurable baud rate

Used for debugging, serial terminals, and interfacing with modules

I²C (Inter-Integrated Circuit)
Supports Master/Slave mode

SCL (RC3) and SDA (RC4)

Used to interface with EEPROM, RTC, sensors, etc.

SPI (Serial Peripheral Interface)
Full-duplex synchronous communication

Master/Slave operation

SCK, SDI, and SDO on PORTC

Useful for high-speed data transfer with external peripherals
Tools Used
MPLAB X IDE – Project creation and debugging

XC8 Compiler – C language compilation

Proteus / MPLAB SIM – Simulation

PICkit 2/3 or Bootloader – Programming the MCU
Open the desired project in MPLAB X IDE

Select the correct device: PIC16F877A

Verify the configuration settings

Build and program the hex file into your MCU

Use Proteus or real hardware to test the system

