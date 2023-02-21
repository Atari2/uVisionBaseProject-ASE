#include "button.h"
#include "lpc17xx.h"

void EINT0_IRQHandler (void)	  
{
  LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}

void EINT1_IRQHandler (void)	  
{
	button_set_debouncing_once(BTN1_ID);
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  
{
  LPC_SC->EXTINT &= (1 << 2);     				 /* clear pending interrupt         */    
}
