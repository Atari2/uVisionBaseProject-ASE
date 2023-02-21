/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**/
#include "LPC17xx.h"
#include "macros.h"
#include "timer\timer.h"
#include "RIT\RIT.h"
#include "joystick\joystick.h"
#include "led\led.h"
#include "button\button.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

unsigned char VETT[N_VETT] = {0}; //	Il contenuto iniziale di VETT deve essere 0 per ogni posizione. 
unsigned char VAR = 0;
	
const int secondi = 15;
	
int main(void)
{	
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	// Si programmi il Timer 3 per generare ciclicamente intervalli di 15 secondi. Il Timer 3 scatena interruzioni alla fine del conteggio.
	init_timer(Timer3, secondi * 1000 ms, SCALE(1), 0);
	init_RIT(50 ms, 0);
	BUTTON_init();
	LED_init();
	joystick_init(JoyUp);
	enable_RIT();
	enable_timer(Timer3);
	while (1) {}
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
