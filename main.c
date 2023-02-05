/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**/
#include "LPC17xx.h"
#include "button/button.h"
#include "joystick/joystick.h"
#include "LED/led.h"
#include "timer/timer.h"
#include "RIT/RIT.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

volatile Mode system_mode = Monitor;

int main(void)
{	
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	LED_init();
	BUTTON_init();
	joystick_init(JoyUp);
	init_RIT(25 ms, 0);
	enable_RIT();
	while (1) {}
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
