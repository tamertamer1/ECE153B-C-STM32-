/*
 * ECE 153B
 *
 * Name(s):
 * Section:
 * Lab: 2C
 */
 
#include "stm32l476xx.h"

#include "LED.h"
#include "RTC.h"
#include "SysClock.h"

char strTime[12] = {0};
char strDate[12] = {0};

void RTC_Set_Alarm(void) {
	RTC->CR &= ~(RTC_CR_ALRBE);
	RTC->CR &= ~(RTC_CR_ALRAE);
	RTC_Disable_Write_Protection();
	//RTC->CR &= ~(RTC_CR_ALRAE);
	//RTC->CR &= ~(RTC_CR_ALRBE);
	
	RTC->CR &= ~(RTC_CR_ALRAIE);
	RTC->CR &= ~(RTC_CR_ALRBIE);
	
	while(((RTC_ISR_ALRAWF & RTC->ISR)==0) && ((RTC_ISR_ALRBWF & RTC->ISR)==0)) {
		
	}
	//Set Mask Bits
	//Alarm A (Alarm interrupts whenever = 30 seconds)
	RTC->ALRMAR &= ~RTC_ALRMAR_MSK1;
	RTC->ALRMAR |= RTC_ALRMAR_MSK2;
	RTC->ALRMAR |= RTC_ALRMAR_MSK3;
	RTC->ALRMAR |= RTC_ALRMAR_MSK4;
	//testing
	RTC->ALRMAR |= RTC_ALRMAR_WDSEL;
	RTC->ALRMAR |= RTC_ALRMAR_PM;
	
	RTC->ALRMAR &= ~255UL;
	RTC->ALRMAR |= 3UL<<4;

	//Alarm B
	RTC->ALRMBR |= RTC_ALRMBR_MSK2;
	RTC->ALRMBR |= RTC_ALRMBR_MSK3;
	RTC->ALRMBR |= RTC_ALRMBR_MSK4;
	RTC->ALRMBR |= RTC_ALRMBR_MSK1;
	RTC->CR |= (RTC_CR_ALRAE);
	RTC->CR |= (RTC_CR_ALRAIE);
	//RTC->CR |= (RTC_CR_ALRBIE);
	
	//RTC->CR |= (RTC_CR_ALRBE);
	
	RTC_Enable_Write_Protection();
}

void RTC_Alarm_Enable(void) {
	// [TODO]
	EXTI->RTSR1 |= EXTI_RTSR1_RT18;
	EXTI->FTSR1 &= ~EXTI_FTSR1_FT18;

	EXTI->IMR1 |= EXTI_IMR1_IM18;
	EXTI->EMR1 |= EXTI_EMR1_EM18;
	EXTI->PR1 |= EXTI_PR1_PIF18;
	//test
	//RTC->ISR &= ~RTC_ISR_ALRBF;
	//RTC->ISR &= ~RTC_ISR_ALRAF;
	//endtest
	NVIC_EnableIRQ(RTC_Alarm_IRQn);
	NVIC_SetPriority(RTC_Alarm_IRQn, 0);
	
}

void RTC_Alarm_IRQHandler(void) {
	//Alarm A Disable Alarm B
	//if((RTC->ISR & RTC_ISR_ALRAF)){
		//Green_LED_Toggle();
		
//}
	//RTC->ISR &= ~RTC_ISR_ALRAF;
	//EXTI->PR1 |= EXTI_PR1_PIF18;
	//Alarm B Disable A

	//if((RTC->ISR & RTC_ISR_ALRBF)){
		//Green_LED_Toggle();
	
//}
	//RTC->ISR &= ~RTC_ISR_ALRBF;
	//EXTI->PR1 |= EXTI_PR1_PIF18;
	//RTC->ISR &= ~RTC_ISR_ALRBF;
	
	RTC->ISR &= ~RTC_ISR_ALRAF;
	EXTI->PR1 |= EXTI_PR1_PIF18; //stuck in IRQhandler until bit is reset
	Green_LED_Toggle();

}
int main(void) {	
	System_Clock_Init(); // Switch System Clock = 80 MHz
	
	LED_Init();
	
	RTC_Init();
	RTC_Alarm_Enable();
	RTC_Set_Alarm();
	
	while(1) {
		Get_RTC_Calendar(strTime,strDate);
	}
}
