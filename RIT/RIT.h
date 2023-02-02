/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           RIT.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in the lib_RIT, funct_RIT, IRQ_RIT .c files
** Correlated files:    lib_RIT.c, funct_RIT.c, IRQ_RIT.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#ifndef __RIT_H
#define __RIT_H
#include <stdint.h>
/* init_RIT.c */
extern int init_RIT(float millis, uint32_t priority);
extern void enable_RIT( void );
extern void disable_RIT( void );
extern void reset_RIT( void );
extern void set_rit_frequency(uint32_t frequency);
/* IRQ_RIT.c */
extern void RIT_IRQHandler (void);

#endif /* end __RIT_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
