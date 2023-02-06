/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           lib_timer.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        atomic functions to be used by higher sw levels
** Correlated files:    lib_timer.c, funct_timer.c, IRQ_timer.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "timer.h"
#include "../macros.h"

static volatile uint32_t g_frequency = 25000000; 	// 25MHz by default

void set_timer_frequency(uint32_t frequency) {
	g_frequency = frequency;
}

static uint32_t calc_count_from_ms(float millis) {
	float seconds = millis / 1000.0f;
	float count = seconds * g_frequency;
	return (uint32_t)count;
}

int init_timer( TimerNo timer_num, float millis, uint32_t prescale,  uint32_t priority)
{
	uint32_t TimerInterval = 0;
	uint32_t MCR0, MCR1, MCR2, MCR3;
	static const enum IRQn TimerIRQ[] = {TIMER0_IRQn, TIMER1_IRQn, TIMER2_IRQn, TIMER3_IRQn};
	if ((int)timer_num >= ARRAY_SIZE(TimerIRQ)) {
		return -1; 		// invalid timer number
	}
	{
			//*** <<< Use Configuration Wizard in Context Menu >>> ***
			// <h> timer0 MCR
			//   <e.0> MR0I
			//	 <i> 1 Interrupt on MR0: an interrupt is generated when MR0 matches the value in the TC. 0
			//	 <i> 0 This interrupt is disabled
			//   </e>
			//   <e.1> MR0R
			//	 <i> 1 Reset on MR0: the TC will be reset if MR0 matches it.
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.2> MR0S
			//	 <i> 1 Stop on MR0: the TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.3> MR1I
			//	 <i> 1 Interrupt on MR1: an interrupt is generated when MR0 matches the value in the TC. 0
			//	 <i> 0 This interrupt is disabled
			//   </e>
			//   <e.4> MR1R
			//	 <i> 1 Reset on MR1: the TC will be reset if MR0 matches it.
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.5> MR1S
			//	 <i> 1 Stop on MR1: the TC and PC will be stopped and TCR[1] will be set to 0 if MR1 matches the TC
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.6> MR2I
			//	 <i> 1 Interrupt on MR2: an interrupt is generated when MR2 matches the value in the TC.
			//	 <i> 0 This interrupt is disabled
			//   </e>
			//   <e.7> MR2R
			//	 <i> 1 Reset on MR2: the TC will be reset if MR2 matches it.
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.8> MR2S
			//	 <i> 1 Stop on MR2: the TC and PC will be stopped and TCR[2] will be set to 0 if MR2 matches the TC
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.9> MR3I
			//	 <i> 1 Interrupt on MR3: an interrupt is generated when MR3 matches the value in the TC.
			//	 <i> 0 This interrupt is disabled
			//   </e>
			//   <e.10> MR3R
			//	 <i> 1 Reset on MR3: the TC will be reset if MR3 matches it.
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.11> MR3S
			//	 <i> 1 Stop on MR3: the TC and PC will be stopped and TCR[3] will be set to 0 if MR3 matches the TC
			//	 <i> 0 Feature disabled.
			//   </e>
			MCR0 = 3;
			// </h>
			// <h> timer1 MCR
			//   <e.0> MR0I
			//	 <i> 1 Interrupt on MR0: an interrupt is generated when MR0 matches the value in the TC. 0
			//	 <i> 0 This interrupt is disabled
			//   </e>
			//   <e.1> MR0R
			//	 <i> 1 Reset on MR0: the TC will be reset if MR0 matches it.
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.2> MR0S
			//	 <i> 1 Stop on MR0: the TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.3> MR1I
			//	 <i> 1 Interrupt on MR1: an interrupt is generated when MR0 matches the value in the TC. 0
			//	 <i> 0 This interrupt is disabled
			//   </e>
			//   <e.4> MR1R
			//	 <i> 1 Reset on MR1: the TC will be reset if MR0 matches it.
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.5> MR1S
			//	 <i> 1 Stop on MR1: the TC and PC will be stopped and TCR[1] will be set to 0 if MR1 matches the TC
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.6> MR2I
			//	 <i> 1 Interrupt on MR2: an interrupt is generated when MR2 matches the value in the TC.
			//	 <i> 0 This interrupt is disabled
			//   </e>
			//   <e.7> MR2R
			//	 <i> 1 Reset on MR2: the TC will be reset if MR2 matches it.
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.8> MR2S
			//	 <i> 1 Stop on MR2: the TC and PC will be stopped and TCR[2] will be set to 0 if MR2 matches the TC
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.9> MR3I
			//	 <i> 1 Interrupt on MR3: an interrupt is generated when MR3 matches the value in the TC.
			//	 <i> 0 This interrupt is disabled
			//   </e>
			//   <e.10> MR3R
			//	 <i> 1 Reset on MR3: the TC will be reset if MR3 matches it.
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.11> MR3S
			//	 <i> 1 Stop on MR3: the TC and PC will be stopped and TCR[3] will be set to 0 if MR3 matches the TC
			//	 <i> 0 Feature disabled.
			//   </e>
			MCR1 = 2;
			// </h>
			// <h> timer2 MCR
			//   <e.0> MR0I
			//	 <i> 1 Interrupt on MR0: an interrupt is generated when MR0 matches the value in the TC. 0
			//	 <i> 0 This interrupt is disabled
			//   </e>
			//   <e.1> MR0R
			//	 <i> 1 Reset on MR0: the TC will be reset if MR0 matches it.
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.2> MR0S
			//	 <i> 1 Stop on MR0: the TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.3> MR1I
			//	 <i> 1 Interrupt on MR1: an interrupt is generated when MR0 matches the value in the TC. 0
			//	 <i> 0 This interrupt is disabled
			//   </e>
			//   <e.4> MR1R
			//	 <i> 1 Reset on MR1: the TC will be reset if MR0 matches it.
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.5> MR1S
			//	 <i> 1 Stop on MR1: the TC and PC will be stopped and TCR[1] will be set to 0 if MR1 matches the TC
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.6> MR2I
			//	 <i> 1 Interrupt on MR2: an interrupt is generated when MR2 matches the value in the TC.
			//	 <i> 0 This interrupt is disabled
			//   </e>
			//   <e.7> MR2R
			//	 <i> 1 Reset on MR2: the TC will be reset if MR2 matches it.
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.8> MR2S
			//	 <i> 1 Stop on MR2: the TC and PC will be stopped and TCR[2] will be set to 0 if MR2 matches the TC
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.9> MR3I
			//	 <i> 1 Interrupt on MR3: an interrupt is generated when MR3 matches the value in the TC.
			//	 <i> 0 This interrupt is disabled
			//   </e>
			//   <e.10> MR3R
			//	 <i> 1 Reset on MR3: the TC will be reset if MR3 matches it.
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.11> MR3S
			//	 <i> 1 Stop on MR3: the TC and PC will be stopped and TCR[3] will be set to 0 if MR3 matches the TC
			//	 <i> 0 Feature disabled.
			//   </e>
			MCR2 = 3;
			// </h>
			// <h> timer3 MCR
			//   <e.0> MR0I
			//	 <i> 1 Interrupt on MR0: an interrupt is generated when MR0 matches the value in the TC. 0
			//	 <i> 0 This interrupt is disabled
			//   </e>
			//   <e.1> MR0R
			//	 <i> 1 Reset on MR0: the TC will be reset if MR0 matches it.
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.2> MR0S
			//	 <i> 1 Stop on MR0: the TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.3> MR1I
			//	 <i> 1 Interrupt on MR1: an interrupt is generated when MR0 matches the value in the TC. 0
			//	 <i> 0 This interrupt is disabled
			//   </e>
			//   <e.4> MR1R
			//	 <i> 1 Reset on MR1: the TC will be reset if MR0 matches it.
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.5> MR1S
			//	 <i> 1 Stop on MR1: the TC and PC will be stopped and TCR[1] will be set to 0 if MR1 matches the TC
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.6> MR2I
			//	 <i> 1 Interrupt on MR2: an interrupt is generated when MR2 matches the value in the TC.
			//	 <i> 0 This interrupt is disabled
			//   </e>
			//   <e.7> MR2R
			//	 <i> 1 Reset on MR2: the TC will be reset if MR2 matches it.
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.8> MR2S
			//	 <i> 1 Stop on MR2: the TC and PC will be stopped and TCR[2] will be set to 0 if MR2 matches the TC
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.9> MR3I
			//	 <i> 1 Interrupt on MR3: an interrupt is generated when MR3 matches the value in the TC.
			//	 <i> 0 This interrupt is disabled
			//   </e>
			//   <e.10> MR3R
			//	 <i> 1 Reset on MR3: the TC will be reset if MR3 matches it.
			//	 <i> 0 Feature disabled.
			//   </e>
			//   <e.11> MR3S
			//	 <i> 1 Stop on MR3: the TC and PC will be stopped and TCR[3] will be set to 0 if MR3 matches the TC
			//	 <i> 0 Feature disabled.
			//   </e>
			MCR3 = 2;
			// </h>
			//*** <<< end of configuration section >>>    ***	
	}
	
	TimerInterval = calc_count_from_ms(millis);
	switch (timer_num) {
		case Timer0:
			LPC_TIM0->MR0 = TimerInterval;
		  LPC_TIM0->MCR = MCR0;
			LPC_TIM0->PR = prescale;
			break;
		case Timer1:
			LPC_TIM1->MR0 = TimerInterval;
		  LPC_TIM1->MCR = MCR1;
		  LPC_TIM1->PR = prescale;
			break;
		case Timer2:
			LPC_SC->PCONP |= (1<<22);
			LPC_TIM2->MR0 = TimerInterval;
		  LPC_TIM2->MCR = MCR2;
		  LPC_TIM2->PR = prescale;
			break;
		case Timer3:
			LPC_SC->PCONP |= (1<<23);
			LPC_TIM3->MR0 = TimerInterval;
			LPC_TIM3->MCR = MCR3;
		  LPC_TIM3->PR = prescale;
			break;
		default:
			break;
	}
	NVIC_EnableIRQ(TimerIRQ[timer_num]);
	NVIC_SetPriority(TimerIRQ[timer_num], priority);
  return 0;
}

/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		Enable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
**
******************************************************************************/
int enable_timer( TimerNo timer_num )
{	
	switch (timer_num) {
		case Timer0:
			LPC_TIM0->TCR = 1;
			break;
		case Timer1:
			LPC_TIM1->TCR = 1;
			break;
		case Timer2:
			LPC_TIM2->TCR = 1;
			break;
		case Timer3:
			LPC_TIM3->TCR = 1;
			break;
		default:
			return -1; 	// invalid timer number
	}
  return 0;
}

/******************************************************************************
** Function name:		disable_timer
**
** Descriptions:		Disable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
**
******************************************************************************/
int disable_timer( TimerNo timer_num )
{
	switch (timer_num) {
		case Timer0:
			LPC_TIM0->TCR = 0;
			break;
		case Timer1:
			LPC_TIM1->TCR = 0;
			break;
		case Timer2:
			LPC_TIM2->TCR = 0;
			break;
		case Timer3:
			LPC_TIM3->TCR = 0;
			break;
		default:
			return -1; 	// invalid timer number
	}
  return 0;
}

/******************************************************************************
** Function name:		reset_timer
**
** Descriptions:		Reset timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
**
******************************************************************************/
int reset_timer( TimerNo timer_num )
{
  uint32_t regVal;
	
	switch (timer_num) {
		case Timer0:
			regVal = LPC_TIM0->TCR;
			regVal |= 0x02;
			LPC_TIM0->TCR = regVal;
			break;
		case Timer1:
			regVal = LPC_TIM1->TCR;
			regVal |= 0x02;
			LPC_TIM1->TCR = regVal;
			break;
		case Timer2:
			regVal = LPC_TIM1->TCR;
			regVal |= 0x02;
			LPC_TIM2->TCR = regVal;
			break;
		case Timer3:
			regVal = LPC_TIM1->TCR;
			regVal |= 0x02;
			LPC_TIM3->TCR = regVal;
			break;
		default:
			return -1; 	// invalid timer number
	}
  return 0;
}
	
void power_timer(TimerNo timer_num) {
	switch (timer_num) {
		case Timer2:
			LPC_SC->PCONP |= (1<<22);
			break;
		case Timer3:
			LPC_SC->PCONP |= (1<<23);
			break;
		default:
		case Timer0:
		case Timer1:
			break;
	}
}

int init_timer_k(TimerNo timer_num, uint32_t TimerInterval, uint32_t prescale, uint32_t priority) {
	uint32_t MCR0 = 3, MCR1 = 3, MCR2 = 3, MCR3 = 3;
	static const enum IRQn TimerIRQ[] = {TIMER0_IRQn, TIMER1_IRQn, TIMER2_IRQn, TIMER3_IRQn};
	if ((int)timer_num >= ARRAY_SIZE(TimerIRQ)) {
		return -1; 		// invalid timer number
	}
	switch (timer_num) {
		case Timer0:
			LPC_TIM0->MR0 = TimerInterval;
		  LPC_TIM0->MCR = MCR0;
			LPC_TIM0->PR = prescale;
			break;
		case Timer1:
			LPC_TIM1->MR0 = TimerInterval;
		  LPC_TIM1->MCR = MCR1;
		  LPC_TIM1->PR = prescale;
			break;
		case Timer2:
			LPC_SC->PCONP |= (1<<22);
			LPC_TIM2->MR0 = TimerInterval;
		  LPC_TIM2->MCR = MCR2;
		  LPC_TIM2->PR = prescale;
			break;
		case Timer3:
			LPC_SC->PCONP |= (1<<23);
			LPC_TIM3->MR0 = TimerInterval;
			LPC_TIM3->MCR = MCR3;
		  LPC_TIM3->PR = prescale;
			break;
		default:
			break;
	}
	NVIC_EnableIRQ(TimerIRQ[timer_num]);
	NVIC_SetPriority(TimerIRQ[timer_num], priority);
  return 0;

}

/******************************************************************************
**                            End Of File
******************************************************************************/
