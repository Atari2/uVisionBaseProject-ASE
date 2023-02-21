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
#include "../led/led.h"
#include "../button/button.h"
#include "../macros.h"
#include "../timer/timer.h"
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

extern unsigned char VAR;
extern unsigned char VETT[N_VETT];
extern uint32_t cur_vett_index;
extern int media_e_superiori_alla_media(unsigned char VETT[], unsigned int num, char* super);
volatile int media = 0;
volatile char super = 0;
int key1_pressed = 0;
uint32_t ticks = 0;

void key1Handler(void) {
	key1_pressed++;
	if (key1_pressed == 1) {
	  // 4)	In una seconda fase, alla pressione di KEY1, viene invocata una funzione scritta in linguaggio ASSEMBLER in grado di analizzare il contenuto di VETT.
		media = media_e_superiori_alla_media(VETT, cur_vett_index, (char*)&super);
		ticks = 0;
	} else if (key1_pressed == 2) {
		// Alla (ndr. seconda) pressione di KEY1
		// A.	Il contenuto del vettore VETT e di VAR vengono “azzerati” (si riporta alla configurazione iniziale con valore 0 in tutti gli elementi)
		memset(VETT, 0, ARRAY_SIZE(VETT));
		cur_vett_index = 0;
		VAR = 0;
		media = 0;
		super = 0;
		ticks = 0;
		// B.	I LED sono tutti spenti
		LED_Out(NO_LEDS);
    // C.	Il processo ricomincia da 2) aspettando il valore da inserire alla posizione 0.
		key1_pressed = 0;
	}
}

btn_handler_t myHandlers[3] = {NULL, key1Handler, NULL};

void RIT_IRQHandler (void)
{
	// timer ticks ogni 50 ms
	const int ticks_per_second = 1000 / 50;
	button_handler_with_debouncing(myHandlers);
	
	if (key1_pressed == 1) {
		// Fino alla (ndr: seconda) pressione di KEY1, le funzioni di raccolta dati sono inibite
		// 5)	I led mostrano in alternanza i risultati dell’esecuzione della funzione ASM, ad una frequenza di 0,5 Hz.
		ticks++;
		const int ticks_per_2_seconds = ticks_per_second * 2;
		if ((ticks / ticks_per_2_seconds) % 2 == 0) {
			// display super
			LED_Out((BitLed)super);
		} else {
			// display media
			LED_Out((BitLed)media);
		}	
	} else {
		if (poll_joystick(JoyUp)) {
			ticks++;
		} else if (ticks > 0) {
			// let go of joystick, save value and reset ticks
			int elapsed_seconds = ticks / ticks_per_second;
			if (elapsed_seconds < 1) {
				// Ogni volta che il Joystick viene operato in direzione UP per meno di 1 secondo, 
				// il valore di una variabile VAR, dimensionata opportunamente e inizializzata a 0, viene incrementata di valore 1 (+1)
				VAR++;
				LED_Out((BitLed)VAR);
			} else if (elapsed_seconds >= 1) {
				// Se il Joystick viene operato in direzione UP per più di un secondo, il valore di VAR viene incrementato come segue: tra 1 secondo e 2 secondi, VAR si incrementa di valore 2 (+2); 
				// tra 2 secondi e 3 secondi, VAR si incrementa di valore 4 (+4); tra 3 secondi e 4 secondi, di valore 6 (+6); e così via.
				// elapsed seconds is rounded down to nearest int
				VAR += (elapsed_seconds*2);
				LED_Out((BitLed)VAR);
			}
			ticks = 0;
		}
	}
	
	reset_RIT();
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
}

/******************************************************************************
**                            End Of File
******************************************************************************/
