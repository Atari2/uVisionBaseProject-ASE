/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**/
#include "LPC17xx.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

int main(void)
{	
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	while (1) {}
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
