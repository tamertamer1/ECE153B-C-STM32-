
/*
 * ECE 153B
 *
 * Name(s):
 * Section:
 * Lab: 2A
 */

#include "stm32l476xx.h"

void GPIO_Init(void){    
    //RCC ENABLE
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

    //Sets Pins 5,6,8,9 to Output
    GPIOC->MODER &= ~GPIO_MODER_MODER5_1;
    GPIOC->MODER &= ~GPIO_MODER_MODER6_1;
    GPIOC->MODER &= ~GPIO_MODER_MODER8_1;
    GPIOC->MODER &= ~GPIO_MODER_MODER9_1;

    //Set the output speed of the pins to fast (10 i think ??
    GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED5_1;
    GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED6_1;
    GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED8_1;
    GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED9_1;

    //Set pins to push pull
    GPIOC->OTYPER &= ~GPIO_OTYPER_OT5;
    GPIOC->OTYPER &= ~GPIO_OTYPER_OT6;
    GPIOC->OTYPER &= ~GPIO_OTYPER_OT8;
    GPIOC->OTYPER &= ~GPIO_OTYPER_OT9;

    //Sets Pins 5,6,8,9 to no pull up, no pull down
    GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD5;
    GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD6;
    GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD8;
    GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD9;
}


#define DELAY 1000    // delay between steps of the sequences

void Full_Stepping_CounterClockwise(void){
	  int t=512;
    while (t>0){
			GPIOC->ODR |= 1UL<<5;
			GPIOC->ODR |= 1UL <<9;
			GPIOC->ODR &= ~(1UL<<8);
			GPIOC->ODR &= ~(1UL<<6);
			for (int i=0;i<DELAY;i++){
			}
			GPIOC->ODR |= 1UL<<5;
			GPIOC->ODR |= 1UL <<8;
			GPIOC->ODR &= ~(1UL<<6);
			GPIOC->ODR &= ~(1UL<<9);
			for (int i=0;i<DELAY;i++){
			}
			GPIOC->ODR |= 1UL<<6;
			GPIOC->ODR |= 1UL <<8;
			GPIOC->ODR &= ~(1UL<<5);
			GPIOC->ODR &= ~(1UL<<9);
			for (int i=0;i<DELAY;i++){
			}
			GPIOC->ODR |= 1UL<<6;
			GPIOC->ODR |= 1UL <<9;
			GPIOC->ODR &= ~(1UL<<5);
			GPIOC->ODR &= ~(1UL<<8);
			for (int i=0;i<DELAY;i++){
			}
     t--;			
    }
}


void Full_Stepping_Clockwise(void){
    // [TODO]
		int t=512;
    while (t>0){
			GPIOC->ODR |= 1UL<<6;
			GPIOC->ODR |= 1UL <<9;
			GPIOC->ODR &= ~(1UL<<5);
			GPIOC->ODR &= ~(1UL<<8);
			for (int i=0;i<DELAY;i++){
			}
			GPIOC->ODR |= 1UL<<6;
			GPIOC->ODR |= 1UL <<8;
			GPIOC->ODR &= ~(1UL<<5);
			GPIOC->ODR &= ~(1UL<<9);
			for (int i=0;i<DELAY;i++){
			}
			GPIOC->ODR |= 1UL<<5;
			GPIOC->ODR |= 1UL <<8;
			GPIOC->ODR &= ~(1UL<<6);
			GPIOC->ODR &= ~(1UL<<9);
			for (int i=0;i<DELAY;i++){
			}
			GPIOC->ODR |= 1UL<<5;
			GPIOC->ODR |= 1UL <<9;
			GPIOC->ODR &= ~(1UL<<8);
			GPIOC->ODR &= ~(1UL<<6);
			for (int i=0;i<DELAY;i++){
			}
     t--;			
    }
}

void Half_Stepping_Clockwise(void){ //acts like counter clockwise
    // [TODO]
		int t=512;
    while (t>0){
			GPIOC->ODR |= 1UL<<9;
			GPIOC->ODR &= ~(1UL<<8);
			GPIOC->ODR &= ~(1UL<<6);
			GPIOC->ODR &= ~(1UL<<5);
			for (int i=0;i<DELAY;i++){
			}
			GPIOC->ODR |= 1UL<<6;
			GPIOC->ODR |= 1UL <<9;
			GPIOC->ODR &= ~(1UL<<8);
			GPIOC->ODR &= ~(1UL<<5);
			for (int i=0;i<DELAY;i++){
			}
			GPIOC->ODR |= 1UL<<6;
			GPIOC->ODR &= ~(1UL<<9);
			GPIOC->ODR &= ~(1UL<<5);
			GPIOC->ODR &= ~(1UL<<8);
			for (int i=0;i<DELAY;i++){
			}
			GPIOC->ODR |= 1UL<<6;
			GPIOC->ODR |= 1UL <<8;
			GPIOC->ODR &= ~(1UL<<5);
			GPIOC->ODR &= ~(1UL<<9);
			for (int i=0;i<DELAY;i++){
			}
			GPIOC->ODR &= ~(1UL<<9);
			GPIOC->ODR |= 1UL <<8;
			GPIOC->ODR &= ~(1UL<<5);
			GPIOC->ODR &= ~(1UL<<6);
			for (int i=0;i<DELAY;i++){
			}
			GPIOC->ODR |= 1UL<<5;
			GPIOC->ODR |= 1UL <<8;
			GPIOC->ODR &= ~(1UL<<6);
			GPIOC->ODR &= ~(1UL<<9);
			for (int i=0;i<DELAY;i++){
			}
			GPIOC->ODR |= 1UL<<5;
			GPIOC->ODR &= ~(1UL<<9);
			GPIOC->ODR &= ~(1UL<<6);
			GPIOC->ODR &= ~(1UL<<8);
			for (int i=0;i<DELAY;i++){
			}
			GPIOC->ODR |= 1UL<<5;
			GPIOC->ODR |= 1UL <<9;
			GPIOC->ODR &= ~(1UL<<6);
			GPIOC->ODR &= ~(1UL<<8);
			for (int i=0;i<DELAY;i++){
			}
     t--;			
    }
}

void Half_Stepping_CounterClockwise(void){
    int t=512;
    while (t>0){
      GPIOC->ODR |= 1UL<<5;
			GPIOC->ODR |= 1UL <<9;
			GPIOC->ODR &= ~(1UL<<6);
			GPIOC->ODR &= ~(1UL<<8);
			for (int i=0;i<DELAY;i++){
			}
			GPIOC->ODR |= 1UL<<5;
			GPIOC->ODR &= ~(1UL<<9);
			GPIOC->ODR &= ~(1UL<<6);
			GPIOC->ODR &= ~(1UL<<8);
			for (int i=0;i<DELAY;i++){
			}
			GPIOC->ODR |= 1UL<<5;
			GPIOC->ODR |= 1UL <<8;
			GPIOC->ODR &= ~(1UL<<6);
			GPIOC->ODR &= ~(1UL<<9);
			for (int i=0;i<DELAY;i++){
			}
			GPIOC->ODR &= ~(1UL<<9);
			GPIOC->ODR |= 1UL <<8;
			GPIOC->ODR &= ~(1UL<<5);
			GPIOC->ODR &= ~(1UL<<6);
			for (int i=0;i<DELAY;i++){
			}
			GPIOC->ODR |= 1UL<<6;
			GPIOC->ODR |= 1UL <<8;
			GPIOC->ODR &= ~(1UL<<5);
			GPIOC->ODR &= ~(1UL<<9);
			for (int i=0;i<DELAY;i++){
			}
			GPIOC->ODR |= 1UL<<6;
			GPIOC->ODR &= ~(1UL<<9);
			GPIOC->ODR &= ~(1UL<<5);
			GPIOC->ODR &= ~(1UL<<8);
			for (int i=0;i<DELAY;i++){
			}
			GPIOC->ODR |= 1UL<<6;
			GPIOC->ODR |= 1UL <<9;
			GPIOC->ODR &= ~(1UL<<8);
			GPIOC->ODR &= ~(1UL<<5);
			for (int i=0;i<DELAY;i++){
			}
			GPIOC->ODR |= 1UL<<9;
			GPIOC->ODR &= ~(1UL<<8);
			GPIOC->ODR &= ~(1UL<<6);
			GPIOC->ODR &= ~(1UL<<5);
			t--;			
    }
}


int main(void){
    GPIO_Init();
     Half_Stepping_CounterClockwise();
    // Rotate 360 degrees either clockwise or counter-clockwise
    // [TODO]
}
