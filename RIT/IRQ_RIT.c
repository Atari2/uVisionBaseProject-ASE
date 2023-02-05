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
#include "../joystick/joystick.h"
#include "../macros.h"
#include "../timer/timer.h"
#include "../led/led.h"
#include <stdlib.h>
#include <string.h>

extern volatile Mode system_mode;
extern unsigned char duty_cycle(unsigned char valore_iniziale, unsigned int tempo_totale, unsigned int tempi_variazioni[], unsigned char numero_variazioni);
/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

uint8_t valore_iniziale = 0;
uint32_t tempi_variazioni[5] = {0, 0, 0, 0, 0};

void RIT_IRQHandler (void)
{
	const uint32_t freq_ms = 2000; // 1/2 hertz (2000 ms)
	const uint32_t rit_ticks = freq_ms / 25; 
	static int curr_index = 0;
	static Mode previous_mode = Monitor;
	static int previous_val = 0;
	static int curr_tick = 0;
	static _Bool is_duty_cycle = 0;
	
	// 3)	In modalita' Acquisizione, il tasto UP del joystick viene campionato con una frequenza di 25 millisecondi. 
	int signal_val = poll_joystick(JoyUp);
	if (previous_mode != system_mode) {
		// Il valore iniziale del segnale (appena si entra nella modalita' Acquisizione) viene memorizzato in una variabile dedicata chiamata "valore_iniziale", 
		if (system_mode == Acquisizione) { 		
			curr_index = 0;
			previous_val = 0;
			valore_iniziale = signal_val; 
			memset(tempi_variazioni, 0, sizeof(tempi_variazioni));
		}
		previous_mode = system_mode;
	} else if (system_mode == Acquisizione) {
		if (signal_val != previous_val) {
			// mentre ad ogni variazione del segnale di UP (da 0 a 1 e viceversa), 
			// un vettore chiamato "tempi_variazioni" viene utilizzato per raccogliere le informazioni relative alle variazioni registrate.
			tempi_variazioni[curr_index++] = LPC_TIM3->TC;
			if (curr_index == 5) {
				// dopo 5 variazioni, il sistema ferma il TIMER3 ed entra nella modalita' Monitor
				system_mode = Monitor;
				disable_timer(Timer3);
			}
		}
	} else {
		// monitor
		curr_tick++;
		if (curr_tick == rit_ticks) {
			// Il LED D7 e' utilizzato per indicare il tipo di misura (acceso per il numero di variazioni, spento per il duty-cycle), mentre D0-D6 sono utilizzati per indicarne il valore. 
			if (is_duty_cycle) {
				// calculate duty cycle (e led 7 spento)
				uint32_t duty_cycle_val = duty_cycle(valore_iniziale, LPC_TIM3->TC, tempi_variazioni, curr_index);
				LED_Out((BitLed)(duty_cycle_val & (~BitLed7)));
			} else {
				// numero di variazioni (e led 7 acceso)
				LED_Out((BitLed)(BitLed7 | curr_index));
			}
			curr_tick = 0;
			is_duty_cycle = !is_duty_cycle;
		}
	}
	previous_val = signal_val;
	reset_RIT();
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
}

/******************************************************************************
**                            End Of File
******************************************************************************/
