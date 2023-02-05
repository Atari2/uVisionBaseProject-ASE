#include "button.h"
#include "lpc17xx.h"
#include "../timer/timer.h"
#include "../RIT/RIT.h"
#include "../led/led.h"

extern volatile Mode system_mode;

void EINT0_IRQHandler (void)	  
{
  LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}

void EINT1_IRQHandler (void)	  
{
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  
{
	// 2)	Alla pressione del tasto KEY2, il sistema passa da modalita' Monitor a modalita' Acquisizione, attivando il TIMER3 in modo aciclico con periodo di 1 secondo
	system_mode = Acquisizione;
	init_timer(Timer3, 1000 ms, SCALE(1), 0);
	reset_timer(Timer3);
	enable_timer(Timer3);
	
	// 5)	In modalita' Acquisizione, i LED devono essere tutti accesi.
	LED_Out(ALL_LEDS);
	
  LPC_SC->EXTINT &= (1 << 2);     				 /* clear pending interrupt         */    
}
