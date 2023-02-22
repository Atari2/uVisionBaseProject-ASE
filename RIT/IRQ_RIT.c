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
#include "../joystick/joystick.h"
#include "../macros.h"
#include "../led/led.h"
#include <string.h>
/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

uint32_t ticks_up = 0;
uint32_t ticks_left = 0;
uint32_t ticks = 0;
uint32_t curr_vett_index = 0;
int super = -1;
extern unsigned char VAR;
extern unsigned char VETT[N_VETT];
extern unsigned int sopra_la_media(unsigned char VETT[], unsigned int n); 	

unsigned char update_with_check(unsigned char value, int32_t change) {
	if (change == 0) return value;
	unsigned char new_value = value + change;
	
	if (change > 0) {
		// a+b when b > 0 somehow resulted in a being smaller than before, overflow has occurred
		if (new_value < value)
			return 255;
		else
			return new_value;
	} else {
		// a+b when b < 0 somehow resulted in a being bigger than before, overflow has occurred
		if (new_value > value)
			return 0;
		else
			return new_value;
	}
}

void handleInt0(void) {
	VETT[curr_vett_index] = VAR;
	// almeno un valore inserito
	if (curr_vett_index > 0) {
		// Qualora il sistema abbia acquisito il numero massimo di valori (N) 
		// oppure nel caso in cui gli ultimi due valori immessi siano uguali, si invochi la seguente funzione scritta in linguaggio ASSEMBLER 
		if (curr_vett_index == (N_VETT-1) || VAR == VETT[curr_vett_index-1]) {
			curr_vett_index++;
			super = sopra_la_media(VETT, curr_vett_index);
			ticks = 0;
			return;
		}
	}
	curr_vett_index++;
	VAR = 0;
}

btn_handler_t myHandlers[3] = {handleInt0, NULL, NULL};

void RIT_IRQHandler (void)
{
	
	const int ticks_per_half_second = 500 / 10;
	
	if (super != -1) {
		 // 4)	A valle dell’esecuzione della funzione assembler, 
		 // i LED mostreranno il risultato, qualora rappresentabile con i LED
		 // la sequenza alternata dei valori 0xAA e 0x55, con periodo 10ms.
		 switch (ticks % 3) {
			 case 0:
				 LED_Out((BitLed)super);
				 break;
			 case 1:
				 LED_Out((BitLed)0xAA);
				 break;
			 case 2:
				 LED_Out((BitLed)0x55);
				 break;
		 }
		 ticks++;
		 if (poll_joystick(JoySelect)) {
			// La visualizzazione del risultato continua finchè il jostick SELECT non viene premuto; 
			// in quel caso vettore sarà considerato vuoto ed il processo ripreso da 1) con valore iniziale di VAL uguale a 0.
			 super = -1;
			 curr_vett_index = 0;
			 VAR = 0;
			 ticks = 0;
			 memset(VETT, 0, ARRAY_SIZE(VETT));
		 }
		 reset_RIT();
		 LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
		 return;
	}
	
	button_handler_with_debouncing(myHandlers);
	// 1)	Utilizzando il JOYSTICK, si implementi un “generatore di numeri senza segno” usando una variabile di tipo unsigned char chiamata VAR:
	
	if (poll_joystick(JoyUp)) {
		// UP – quando operato, incrementa VAR di 1 il valore attuale ogni 0,5 secondi pressione (se la pressione dura meno, allora il valore non subirà variazioni)
		ticks_up++;
		if (ticks_up == ticks_per_half_second) {
				ticks_up = 0;
				VAR = update_with_check(VAR, 1);
		}
	} else if (poll_joystick(JoyLeft)) {
		// LEFT – quando operato, decrementa VAR di 1 il valore attuale ogni 0,5 secondi di pressione (se la pressione dura meno, allora il valore non subirà variazioni)
		ticks_left++;
		if (ticks_left == ticks_per_half_second) {
			ticks_left = 0;
			VAR = update_with_check(VAR, -1);
		}
	} else if (poll_joystick(JoySelect)) {
		// SELECT – azzera il valore attuale (nb: il valore sia a 0 durante la fase di  boot)
		VAR = 0;
	} else {
		ticks_up = 0;
		ticks_left = 0;
	}
	LED_Out((BitLed)VAR);
	reset_RIT();
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
}

/******************************************************************************
**                            End Of File
******************************************************************************/
