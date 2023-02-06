#include "button.h"
#include "lpc17xx.h"
#include "../macros.h"
#include "../LED/led.h"
#include "../timer/timer.h"

extern uint8_t VETT[N_V];
extern uint8_t CURR_VALUE;
extern unsigned char get_and_sort(unsigned char* VETT, unsigned char VAL, int n);
void EINT0_IRQHandler (void)	  
{
  LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}

void EINT1_IRQHandler (void)	  
{
	// •	La pressione del pulsante KEY1 permette di acquisire un valore leggendo il registro TC dal timer predisposto
	static uint32_t curr_index = 0;
	uint32_t val = LPC_TIM1->TC;
	CURR_VALUE = (uint8_t)((val & 0xFF0000) >> 16);
	uint8_t v = get_and_sort(VETT, CURR_VALUE, N_V);
	curr_index++;
	LED_Out((BitLed)curr_index);
	if (curr_index == N_V) { 
		// 5)	Una volta acquisiti gli N valori in VETT, questi devono essere mostrati in sequenza sui LED con una frequenza di ½ Hz, seguita da LED tutti spenti.
		curr_index = 0; 
		init_timer(Timer0, 2000 ms, SCALE(1), 1);
		enable_timer(Timer0);
		NVIC_DisableIRQ(EINT1_IRQn);	// disable button
	}
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  
{
  LPC_SC->EXTINT &= (1 << 2);     				 /* clear pending interrupt         */    
}
