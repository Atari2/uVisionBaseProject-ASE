/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           funct_led.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        High level led management functions
** Correlated files:    lib_led.c, funct_led.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "led.h"
#include "../macros.h"
const BitLed led_mask[] = { BitLed0, BitLed1, BitLed2, BitLed3, BitLed4, BitLed5, BitLed6, BitLed7 };
const BitLed ALL_LEDS = (BitLed)0xFF;
const BitLed NO_LEDS = (BitLed)0x00;

/*----------------------------------------------------------------------------
  Function that turns on requested LED
 *----------------------------------------------------------------------------*/
void LED_On(LedNum num) {
 
  LPC_GPIO2->FIOPIN |= led_mask[num];
}

/*----------------------------------------------------------------------------
  Function that turns off requested LED
 *----------------------------------------------------------------------------*/
void LED_Off(LedNum num) {

  LPC_GPIO2->FIOPIN &= ~led_mask[num];
}

/*----------------------------------------------------------------------------
  Function that outputs value to LEDs
 *----------------------------------------------------------------------------*/
void LED_Out(BitLed value) {
  LedNum i = Led0;

  for (; i <= Led7; i++) {
    if (value & led_mask[i]) {
      LED_On (i);
    } else {
      LED_Off(i);
    }
  }
}
