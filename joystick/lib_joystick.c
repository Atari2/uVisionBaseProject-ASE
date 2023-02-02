/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           joystick.h
** Last modified Date:  2018-12-30
** Last Version:        V1.00
** Descriptions:        Atomic joystick init functions
** Correlated files:    lib_joystick.c, funct_joystick.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "joystick.h"

/*----------------------------------------------------------------------------
  Function that initializes joysticks and switch them off
 *----------------------------------------------------------------------------*/
 
 static const uint32_t JOYDIRECTION_SIZE = 5;
 
static __attribute__((always_inline)) uint32_t make_pinsel(const uint32_t directions) {
	const uint32_t base = 18;		// the 18th bit is the first that refers to the joystick in PINSEL3
	uint32_t value = 0;
	for (uint32_t i = 0; i < JOYDIRECTION_SIZE; ++i) {
		if ((directions & (1 << (joyvalue_base+i))) != 0) {
			value |= (3 << (base+(i*2)));
		}
	}
	return value;
}

void joystick_init(const uint32_t directions) {
	/* joystick Select functionality */
	
  LPC_PINCON->PINSEL3 &= ~make_pinsel(directions);
	LPC_GPIO1->FIODIR   &= ~directions;
}

__attribute__((always_inline)) int poll_joystick(const uint32_t directions) {
	return (LPC_GPIO1->FIOPIN & directions) == 0;
}
