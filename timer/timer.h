/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           timer.h
** Last modified Date:  2023-02-20
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in the lib_timer, funct_timer, IRQ_timer .c files
** Correlated files:    lib_timer.c, funct_timer.c, IRQ_timer.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#ifndef __TIMER_H
#define __TIMER_H
#include <stdint.h>
#include "../macros.h"
/* init_timer.c */


enum TimerNo {
	Timer0 = 0,
	Timer1 = 1,
	Timer2 = 2,
	Timer3 = 3
} typedef TimerNo;


extern void power_timer(TimerNo timer_num);
extern int init_timer( TimerNo timer_num, float millis, uint32_t prescale, uint32_t priority);
extern int init_timer_k(TimerNo timer_num, uint32_t TimerInterval, uint32_t prescale, uint32_t priority);
extern int enable_timer( TimerNo timer_num );
extern int disable_timer( TimerNo timer_num );
extern int reset_timer( TimerNo timer_num );
extern void set_timer_frequency(uint32_t frequency);
extern uint32_t get_current_value(TimerNo timer_num);
/* IRQ_timer.c */
extern void TIMER0_IRQHandler (void);
extern void TIMER1_IRQHandler (void);
extern void TIMER2_IRQHandler (void);
extern void TIMER3_IRQHandler (void);

#endif /* end __TIMER_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
