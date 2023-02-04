/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**/
#include "LPC17xx.h"
#include "macros.h"
#include "timer/timer.h"
#include "joystick/joystick.h"
#include "LED/led.h"
#include "button/button.h"
#include "RIT/RIT.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

volatile uint32_t var1 = 9;

int main(void)
{	
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	LED_init();
	BUTTON_init();
	joystick_init(JoyDown);
	init_RIT(50 ms, 1);
	init_timer(Timer3, 60*1.3*1000 ms, SCALE(1), 0);
	enable_timer(Timer3);
	enable_RIT();
	while (1) {}
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
