/*
 * ECE 153B
 *
 * Name(s):
 * Section:
 * Lab: 2B
 */

#include "EXTI.h"
#include "LED.h"
#include <stdbool.h>

void EXTI_Init(void) { //C13
	// Initialize User Button
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;		
		GPIOC->MODER &= ~GPIO_MODER_MODE13;
		GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD13;
	// [TODO]
	
	// Configure SYSCFG EXTI
		RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
		SYSCFG->EXTICR[3] &= ~SYSCFG_EXTICR4_EXTI13;
		SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;
	// [TODO]
	
	// Configure EXTI Trigger
			EXTI->FTSR1 |= EXTI_FTSR1_FT13;		
	// [TODO]
	
	// Enable EXTI
			EXTI->IMR1 |= EXTI_IMR1_IM13;
	// [TODO]
	
	// Configure and Enable in NVIC
		NVIC_EnableIRQ(EXTI15_10_IRQn);
		NVIC_SetPriority(EXTI15_10_IRQn, 0);		
	// [TODO]
}

// [TODO] Write Interrupt Handlers (look in startup_stm32l476xx.s to find the 
// interrupt handler names that you should use)

void EXTI15_10_IRQHandler(void) {
	// Define behavior that occurs when interrupt occurs
	EXTI->PR1 |= EXTI_PR1_PIF13;
	Green_LED_Toggle();
	// Clear interrupt pending bit
	
}
