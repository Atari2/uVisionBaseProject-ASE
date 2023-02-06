/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**/
#include "LPC17xx.h"
#include "timer/timer.h"
#include "button/button.h"
#include "LED/led.h"
#include "macros.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

uint8_t VETT[N_V] = {0};
uint8_t CURR_VALUE = 0;

int main(void)
{	
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	init_timer(Timer1, 1000 ms * (2.43*60), SCALE(1), 0);
	BUTTON_init();
	LED_init();
	enable_timer(Timer1);
	while (1) {}
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
