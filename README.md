# Embedded C on ARM Cortex-M · STM32L4

Bare-metal firmware for the STM32L476 (ARM Cortex-M4), written in C directly against the hardware registers, with no HAL or vendor driver library. Built for UCSB's ECE 153B.

![C](https://img.shields.io/badge/C-A8B9CC?logo=c&logoColor=black)
![ARM](https://img.shields.io/badge/ARM_Cortex--M4-0091BD?logo=arm&logoColor=white)
![STM32](https://img.shields.io/badge/STM32L4-03234B?logo=stmicroelectronics&logoColor=white)
![Keil](https://img.shields.io/badge/Keil_µVision-394049)

## What's inside

Each lab builds a peripheral driver from the reference manual up, then uses it in a small application.

| Lab | Peripherals | What it does |
|---|---|---|
| [`153B L1`](153B%20L1) | RCC, GPIO | Clock setup and GPIO configuration from scratch to drive LEDs and read a button |
| [`153B L2/2A`](153B%20L2/2A) | GPIO | Multi-pin output control: mode, speed and push-pull configuration |
| [`153B L2/2B`](153B%20L2/2B) | EXTI, NVIC | Interrupt-driven input instead of polling |
| [`153B L2/2C`](153B%20L2/2C) | RTC | Real-time clock with alarm interrupts |
| [`L4/L4A`](L4/L4A) | USART | UART to a PC terminal and **Bluetooth to a phone**, with `printf` retargeted over serial |
| [`L4/L4B`](L4/L4B) | I²C | Talking to a sensor over I²C (7-bit addressing, read/write transactions) |
| [`L4/L4C`](L4/L4C) | SPI, SysTick | Reading an **accelerometer** over SPI and streaming X/Y/Z acceleration to the terminal |

## Driver files

```
SysClock.c      system clock to 80 MHz
LED.c           GPIO output
EXTI.c          external interrupts
RTC.c           real-time clock and alarms
SysTimer.c      SysTick millisecond timer
UART.c          USART init and transmit/receive
UART_printf.c   printf over serial
I2C.c           I²C master
SPI.c           SPI master
accelerometer.c accelerometer register access over SPI
```

## Building

Open a lab's `project.uvprojx` in Keil µVision, build, and flash to an STM32L476 board (e.g. the NUCLEO-L476RG).
