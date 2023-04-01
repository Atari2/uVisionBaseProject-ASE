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
#include "../button/button.h"
#include "../led/led.h"
#include "../timer/timer.h"
#include <string.h>
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
extern unsigned char VAR;
extern char fibonacci(char VAR);
extern volatile int btnPressed[3]; // declared in button.c - how much time the button has been pressed
unsigned char result = 0;
const int btnPressedForHalfSecond = 20;
int viewingResult = -1;
void key1Handler(void) {
	// Quando viene premuto KEY1, VAR viene incrementata di +1 (fino al valore massimo rappresentabile)
	if (VAR < 0xFF) {
		VAR++;
	}
}
void key2Handler(void) {
	// Quando viene premuto KEY2, VAR viene decrementata di -1 (fino al valore minimo rappresentabile)
	if (VAR > 0) {
		VAR--;
	}
}
btn_handler_t myHandlers[3] = {NULL, key1Handler, key2Handler};
void RIT_IRQHandler (void)
{
	static int timer_enabled = 0;
	const int threeSeconds = 3000 / 25;
	if (viewingResult != -1) {
		viewingResult++;
		// 4)	Il valore risultato deve essere presentato usando tutti i LED. 
		if (result == 0xFF) {
			// Se il valore restituito è 0xFF, allora i led si accenderanno in sequenza uno per volta, 
			// cambiando progressivamente led da 0 a 7 con un periodi di accensione di 0,3s a LED, una volta tutti i led sono accessi,
			// uso il RIT stesso per l'accensione progressiva			
			const int pointThreeSeconds = 300 / 25;
			LedNum ledno = (LedNum)(viewingResult / pointThreeSeconds);
			LED_On(ledno);
		} else if (!timer_enabled) {
			// Se no, allora il risultato della funzione viene mostrato sui led lampeggiando a una frequenza di 3,33 Hz. 
			// mentre mi avvalgo di timer0 per il lampeggio a 3.33 Hz
			timer_enabled = 1;
			const float millis = (1.0 / 3.33) * 1000 ms;
			init_timer(Timer0, millis, 0, 1);
			enable_timer(Timer0);
		}
		
		if (viewingResult == threeSeconds) {
			  // 5)	L’output deve essere mostrato per 3 secondi, durante i quali non è possibile interagire con KEY1 e KEY2. 
			  // Quando la sequenza di visualizzazione viene terminata, ed il processo ricomincia da 2) dopo aver azzerato VAR.
				viewingResult = -1;
			  result = 0;
			  VAR = 0;
			  BUTTON_enable(BTN1_ID);
			  BUTTON_enable(BTN2_ID);
			  memset((void*)btnPressed, 0, ARRAY_SIZE(btnPressed));
			  LED_Out(NO_LEDS);
			  disable_timer(Timer0);
			  timer_enabled = 0;
		}		
		reset_RIT();
    LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	}
	if (btnPressed[BTN1_ID] >= btnPressedForHalfSecond && btnPressed[BTN2_ID]) {
		// Quando vengono contemporaneamente premuti KEY1 e KEY2 per un tempo superiore a 0,5 secondi, deve essere lanciata una funzione assembler capace di restituire 
		// 	1.	 il valore 0xFF se tale valore è un numero della serie di Fibonacci
    //  2.	 il valore della serie di Fibonacci più vicino rappresentabile su 8 bit dal valore indicato da VAR
	  result = fibonacci(VAR);
		viewingResult = 0;
		BUTTON_disable(BTN1_ID);
		BUTTON_disable(BTN2_ID);
	}
	button_handler_with_debouncing(myHandlers);
	reset_RIT();
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
}

/******************************************************************************
**                            End Of File
******************************************************************************/
