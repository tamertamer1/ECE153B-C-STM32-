/*
 
ECE 153B*
Name(s):
Section:
Lab: 4A
*/


#include "stm32l476xx.h"
#include "LED.h"
#include "SysClock.h"
#include "UART.h"
#include <string.h>
#include <stdio.h>

// Initializes USARTx
// USART2: UART Communication with Termite
// USART1: Bluetooth Communication with Phone
void Init_USARTx(int x) {
    if(x == 1) {
        UART1_Init();
        UART1_GPIO_Init();
        USART_Init(USART1);
    } else if(x == 2) {
        UART2_Init();
        UART2_GPIO_Init();
        USART_Init(USART2);
    } else {
        // Do nothing...
    }
}

int main(void) {
    System_Clock_Init(); // Switch System Clock = 80 MHz
    LED_Init();

    // Initialize UART -- change the argument depending on the part you are working on
    Init_USARTx(1);
		USART_Init(USART1);
		Green_LED_On();
		printf("le the LED o disable it");

    char rxByte;
    while(1) {
        // [TODO]
				
        printf("Enter 'y' or 'Y' to enable the LED or 'n' or 'N' to disable it");
				scanf("%c", &rxByte);
			  
        if (rxByte == 'Y' || rxByte == 'y') {
            Green_LED_On();
            printf("LED On\n");
        } else if (rxByte == 'N' || rxByte == 'n') {
            Green_LED_Off();
            printf("LED Off\n");
        } else {
            printf("UNKNOWN INPUT, PLEASE ENTER 'Y' OR 'N'\n");
        }
				

    }
	}