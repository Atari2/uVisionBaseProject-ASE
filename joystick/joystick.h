																			 /*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           joystick.h
** Last modified Date:  2018-12-30
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in the lib_joystick, funct_joystick .c files
** Correlated files:    lib_joystick.c, funct_joystick.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/
#include <stdint.h>

static const uint32_t joyvalue_base = 25;

enum JoystickDirection {
	JoySelect = 1 << (joyvalue_base+0),
	JoyDown = 1 << (joyvalue_base+1),
	JoyLeft = 1 << (joyvalue_base+2),
	JoyRight = 1 << (joyvalue_base+3),
	JoyUp = 1 << (joyvalue_base+4)
} typedef JoystickDirection;
/* lib_joystick */
void joystick_init(const uint32_t directions);
__attribute__((always_inline)) int poll_joystick(const uint32_t directions);
