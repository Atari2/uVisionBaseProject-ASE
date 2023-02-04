#include "button.h"
#include "lpc17xx.h"

extern volatile uint32_t var1;

void EINT0_IRQHandler (void)	  
{
	// INT0 divides VAR1 by 4
	var1 >>= 2;
  LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}

void EINT1_IRQHandler (void)	  
{
	 // After a KEY1 pressure, the current value of Timer 3 is captured and added to VAR1
	var1 += LPC_TIM3->TC;
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  
{
  LPC_SC->EXTINT &= (1 << 2);     				 /* clear pending interrupt         */    
}
