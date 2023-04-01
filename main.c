/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**/
#include "LPC17xx.h"
#include "RIT/RIT.h"
#include "button/button.h"
#include "led/led.h"
#include "macros.h"
#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

unsigned char VAR = 0;

int main(void)
{	
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	LED_init();
	BUTTON_init();
	init_RIT(25 ms, 0);
	enable_RIT();
	while (1) {}
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
