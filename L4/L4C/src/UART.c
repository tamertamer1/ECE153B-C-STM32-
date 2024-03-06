#include "UART.h"

void UART2_Init(void)
{
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN; // ENABLE THE USART2 CLOCK IN PERIPHERAL CLOCK REGISTER
	RCC->CCIPR &= ~RCC_CCIPR_USART2SEL;
	RCC->CCIPR |= RCC_CCIPR_USART2SEL_0;
}
void UART2_GPIO_Init(void)
{
	// RX = RECIEVE = PA3
	// TX = TRANSMIT = PA2

	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; // ENABLE CLOCK FOR GPIO PIN A

	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2;
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3; // SETS GPIO PORT A PINS 2 AND 3 TO HIGH SPEED

	GPIOA->OTYPER &= ~GPIO_OTYPER_OT2;
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT3; // SET GPIO PORT A PINS 2 AND 3 TO PUSH-PULL OUPUT TYPE

	GPIOA->PUPDR |= GPIO_PUPDR_PUPD2_0;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD3_0; // SET GPIO PORT A PINS 2 AND 3 TO USE PULL-UP RESISTORS FOR IO

	// MODER//
	GPIOA->MODER &= ~GPIO_MODER_MODE2;	// CLEAR A2
	GPIOA->MODER |= GPIO_MODER_MODE2_1; // SET A2

	GPIOA->MODER &= ~GPIO_MODER_MODE3;	// CLEAR A3
	GPIOA->MODER |= GPIO_MODER_MODE3_1; // SET A3

	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL2;												 // CLEAR
	GPIOA->AFR[0] |= (GPIO_AFRL_AFSEL2_2 | GPIO_AFRL_AFSEL2_1 | GPIO_AFRL_AFSEL2_0); // SET TO ALTERNATIVE FUNCTION

	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL3;												 // CLEAR
	GPIOA->AFR[0] |= (GPIO_AFRL_AFSEL3_2 | GPIO_AFRL_AFSEL3_1 | GPIO_AFRL_AFSEL3_0); // SET TO ALTERNATIVE FUNCTION
}

void USART_Init(USART_TypeDef *USARTx)
{
	USARTx->CR1 &= ~USART_CR1_UE; // 	NEED TO DISABLE BEFORE MODIFYING THE REGISTERS

	USARTx->CR1 &= ~(USART_CR1_M1 | USART_CR1_M0); // CONFIGURE TO 1 START BIT, 8 DATA BITS, STOP BITS
	USARTx->CR1 &= ~USART_CR1_OVER8;			   // OVERSAMPLE BY 16
	USARTx->CR2 &= ~USART_CR2_STOP;				   // 1 STOP BIT

	USARTx->BRR &= ~0xFFFF; // CLEAR
	USARTx->BRR = 8333;		// SYS CLOCK = 80 MHZ SO 80MHZ / 9600 = 8333

	// 3.c enable transmitter and receiver
	USARTx->CR1 |= USART_CR1_TE; // ENABLE TRANSMITTER IN CONTROL REGISTER
	USARTx->CR1 |= USART_CR1_RE; // ENABLE RECIEVIER IN CONTROL REGISTER

	USARTx->CR1 |= USART_CR1_UE; // USART ENABLED IN CONTROL REGISTERS
}

uint8_t USART_Read(USART_TypeDef *USARTx)
{
	// SR_RXNE (Read data register not empty) bit is set by hardware
	while (!(USARTx->ISR & USART_ISR_RXNE))
		; // Wait until RXNE (RX not empty) bit is set
	// USART resets the RXNE flag automatically after reading DR
	return ((uint8_t)(USARTx->RDR & 0xFF));
	// Reading USART_DR automatically clears the RXNE flag
}

void USART_Write(USART_TypeDef *USARTx, uint8_t *buffer, uint32_t nBytes)
{
	int i;
	// TXE is cleared by a write to the USART_DR register.
	// TXE is set by hardware when the content of the TDR
	// register has been transferred into the shift register.
	for (i = 0; i < nBytes; i++)
	{
		while (!(USARTx->ISR & USART_ISR_TXE))
			; // wait until TXE (TX empty) bit is set
		// Writing USART_DR automatically clears the TXE flag
		USARTx->TDR = buffer[i] & 0xFF;
		USART_Delay(300);
	}
	while (!(USARTx->ISR & USART_ISR_TC))
		; // wait until TC bit is set
	USARTx->ISR &= ~USART_ISR_TC;
}

void USART_Delay(uint32_t us)
{
	uint32_t time = 100 * us / 7;
	while (--time)
		;
}