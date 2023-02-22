/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**/
#include "LPC17xx.h"
#include "joystick/joystick.h"
#include "led/led.h"
#include "RIT/RIT.h"
#include "button/button.h"
#include "macros.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

unsigned char VAR = 0;
unsigned char VETT[N_VETT] = {0};
int main(void)
{	
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	BUTTON_init();
	init_RIT(10 ms, 0);
	joystick_init(JoyUp | JoyLeft | JoySelect);
	LED_init();
	enable_RIT();
	while (1) {}
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
