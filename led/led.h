/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           timer.h
** Last modified Date:  2023-02-20
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in the lib_led, funct_led .c files
** Correlated files:    lib_led.c, funct_led.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

enum {
	Led0 = 0,
	Led1 = 1,
	Led2 = 2,
	Led3 = 3,
	Led4 = 4,
	Led5 = 5,
	Led6 = 6,
	Led7 = 7
} typedef LedNum;

enum {
	BitLed0 = 1 << 0,
	BitLed1 = 1 << 1,
	BitLed2 = 1 << 2,
	BitLed3 = 1 << 3,
	BitLed4 = 1 << 4,
	BitLed5 = 1 << 5,
	BitLed6 = 1 << 6,
	BitLed7 = 1 << 7
} typedef BitLed;

extern const BitLed ALL_LEDS;
extern const BitLed NO_LEDS;

/* lib_led */
void LED_init(void);
void LED_deinit(void);

/* funct_led */
void LED_On (LedNum num);
void LED_Off (LedNum num);
void LED_Out(BitLed value);

