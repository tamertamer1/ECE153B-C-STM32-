/*
 * ECE 153B - Winter 2024
 *
 * Name(s):
 * Section:
 * Lab: 1
 */
#include "stm32l476xx.h"
#include <stdbool.h>
void Init(){
    // Enable HSI
    RCC->CR |= ((uint32_t)RCC_CR_HSION);
    while ( (RCC->CR & (uint32_t) RCC_CR_HSIRDY) == 0 );

    // Select HSI as system clock source
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSI;
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) == 0 );

    // Enable GPIO Clock
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
    // [TODO]

    // Initialize Green LED
		GPIOA->MODER &= ~GPIO_MODER_MODE5_1;
		GPIOA->OTYPER &= ~GPIO_OTYPER_OT5;
		GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5;
    // [TODO]

    // Initialize User Button
		GPIOC->MODER &= ~GPIO_MODER_MODE13;
		GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD13;
    // [TODO]
}

int main(void){
    // Initialization
    Init();

    // Polling to Check for User Button Presses
		bool counter = true;
	  int i;
	  while (true){
			for (i = 0; i<12000;i++){
			}
				
		if ((GPIO_IDR_ID13 & GPIOC->IDR) == 0)
		{
			if (counter)
			{counter = false;
				GPIOA->ODR |= GPIO_ODR_OD5;
				
			}
			else
			{counter = true;
				GPIOA->ODR &= ~GPIO_ODR_OD5;
			}
		}

    // [TODO]
	}
    return 0;
}
