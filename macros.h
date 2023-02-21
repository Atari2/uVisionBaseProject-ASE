#ifndef _MY_MACROS_INCLUDED
#define _MY_MACROS_INCLUDED

// useful macro defintions
#define ms *1.0f
#define MHz *1u
#define SCALE(x) (x-1)
#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))
#define BETWEEN(x, b, e) (x >= b && x <= e)
#define LED_NUM     8                   /* Number of user LEDs   */
#define FONT_WIDTH 8
#define FONT_HEIGHT 16

#if DEBUG
#define N_VETT 4 // Per la fase di debug si consiglia di usare N pari a 4
#else
#define N_VETT 255 // Il valore massimo per N � 255
#endif

#endif

