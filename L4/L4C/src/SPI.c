#include "SPI.h"
#include "SysTimer.h"

void SPI1_GPIO_Init(void)
{
	// Part 2
	//  Enable the GPIO Clock for pins A and B
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN;

	// Set PA4, PB3, PB4, and PB5 to Alternative Functions, and configure their AFR to SPI1

	// Set PA4 to Alternate function mode
	GPIOA->MODER &= ~(GPIO_MODER_MODE4);
	GPIOA->MODER |= GPIO_MODER_MODE4_1;
	// Configure PA4 AFR to SPI1_NSS
	GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL4);
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL4_0 | GPIO_AFRL_AFSEL4_2;

	// Set PB3 to Alternate function mode
	GPIOB->MODER &= ~(GPIO_MODER_MODE3);
	GPIOB->MODER |= GPIO_MODER_MODE3_1;
	// Configure PB3 AFR to SPI1_SCK
	GPIOB->AFR[0] &= ~(GPIO_AFRL_AFSEL3);
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL3_0 | GPIO_AFRL_AFSEL3_2;

	// Set PB4 to Alternate function mode
	GPIOB->MODER &= ~(GPIO_MODER_MODE4);
	GPIOB->MODER |= GPIO_MODER_MODE4_1;
	// Configure PB4 AFR to SPI1_MISO
	GPIOB->AFR[0] &= ~(GPIO_AFRL_AFSEL4);
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL4_0 | GPIO_AFRL_AFSEL4_2;

	// Set PB5 to Alternate function mode
	GPIOB->MODER &= ~(GPIO_MODER_MODE5);
	GPIOB->MODER |= GPIO_MODER_MODE5_1;
	// Configure PB5 AFR to SPI1_MOSI
	GPIOB->AFR[0] &= ~(GPIO_AFRL_AFSEL5);
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL5_0 | GPIO_AFRL_AFSEL5_2;

	// Set GPIO Pins to: Very High Output speed, Output Type Push-Pull, and No Pull-Up/Down

	// Set PA4 to very high output speed
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED4;
	// Set PA4 to output type push-pull
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT4);
	// Set PA4 to No Pull-Up/Down
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD4);

	// Set PB3, PB4, PB5 to very high output speed
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED3 | GPIO_OSPEEDR_OSPEED4 | GPIO_OSPEEDR_OSPEED5;
	// Set PB3, PB4, PB5 to output type push-pull
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT3 | GPIO_OTYPER_OT4 | GPIO_OTYPER_OT5);
	// Set PB3, PB4, PB5 to No Pull-up/Down
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD3 | GPIO_PUPDR_PUPD4 | GPIO_PUPDR_PUPD5);
}

void SPI1_Init(void)
{
	// Enable SPI1 clock in peripheral clock enable register
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

	// Reset SPI
	RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST;	  // Set RCC SPI reset bit
	RCC->APB2RSTR &= ~(RCC_APB2RSTR_SPI1RST); // clear it to reset SPI1 peripheral

	// Disable SPI enable bit
	SPI1->CR1 &= ~(SPI_CR1_SPE); // peripheral must be configured while it is disabled

	// Configure for Full Duplex Communication
	SPI1->CR1 &= ~(SPI_CR1_RXONLY);

	// Configure for 2-line Unidirectional Data Mode
	SPI1->CR1 &= ~(SPI_CR1_BIDIMODE);

	// Disable Output in Bidirectional Mode
	SPI1->CR1 &= ~(SPI_CR1_BIDIOE);

	// Set Frame Format: MSB First
	SPI1->CR1 &= ~(SPI_CR1_LSBFIRST);

	// Set Frame Format: 16-bit mode
	SPI1->CR2 |= SPI_CR2_DS;

	// Use Motorola SPI Mode
	SPI1->CR2 &= ~(SPI_CR2_FRF);

	// Configure Clock. Read DataSheet for required value
	SPI1->CR1 |= SPI_CR1_CPOL;
	SPI1->CR1 |= SPI_CR1_CPHA;

	// Set Baud Rate Prescaler to 16
	SPI1->CR1 &= ~(SPI_CR1_BR);
	SPI1->CR1 |= SPI_CR1_BR_0 | SPI_CR1_BR_1;

	// Disable Hardware CRC Calculation
	SPI1->CR1 &= ~(SPI_CR1_CRCEN);

	// Set as Master
	SPI1->CR1 |= SPI_CR1_MSTR;

	// Disable Software Slave Management
	SPI1->CR1 &= ~(SPI_CR1_SSM);

	// Enable NSS Pulse Management
	SPI1->CR2 |= SPI_CR2_NSSP;

	// Enable Output
	SPI1->CR2 |= SPI_CR2_SSOE;

	// Set FIFO Reception Threshold to 1/2 (16-bit mode)
	SPI1->CR2 &= ~(SPI_CR2_FRXTH);

	// Enable SPI
	SPI1->CR1 |= SPI_CR1_SPE;
}

uint16_t SPI_Transfer_Data(uint16_t write_data)
{
	// Wait for TXE (Transmit buffer empty)
	while ((SPI1->SR & SPI_SR_TXE) == 0)
		;

	// Write data to SPI data register to begin transmission
	SPI1->DR = write_data;

	// Wait for not busy
	while ((SPI1->SR & SPI_SR_BSY) == SPI_SR_BSY)
		;

	// Wait for RXNE (Receive buffer not empty)
	while ((SPI1->SR & SPI_SR_RXNE) == 0)
		;

	// Read received data from SPI1 Data register
	return (uint16_t)SPI1->DR; // TODO
}