/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include <stdlib.h>
#include "../joystick/joystick.h"
#include "../LED/led.h"
#include "../timer/timer.h"
#include "../macros.h"
/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

extern volatile uint32_t var1;
int hold_counter = 0;
unsigned int count_bits_to_1 (unsigned int VAR1);
void RIT_IRQHandler (void)
{
	const int hold_counter_req = 3000 / 50;
	
	if (poll_joystick(JoyDown)) {
		hold_counter++;
	} else {
		hold_counter = 0;
	}
	
	if (hold_counter >= hold_counter_req) {
		// joystick held for 3 sec, number is finished
		uint32_t n_bits = count_bits_to_1(var1);
		var1 = 9;
		reset_timer(Timer0);
		disable_timer(Timer0);
		if (n_bits <= 3) {
			LED_Out(0);
		} else if (BETWEEN(n_bits, 4, 11)) {
			const uint8_t led_no = (LED_NUM-1)-(n_bits - 4);
			LED_Out(1<<led_no);
		} else if (BETWEEN(n_bits, 12, 31)) {
			//  all leds are blinking with a period of 1.2 seconds (half time on, half time off)
			init_timer(Timer0, 600 ms, SCALE(1), 2);
			enable_timer(Timer0);
		}
		hold_counter = 0;
	}

	
	reset_RIT();
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
}

/******************************************************************************
**                            End Of File
******************************************************************************/
