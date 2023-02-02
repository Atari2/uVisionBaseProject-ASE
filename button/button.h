#include <stdint.h>
#include <stdlib.h>
enum {
	BTN0_ID = 0,
	BTN1_ID = 1,
	BTN2_ID = 2
} typedef BtnIds;
typedef void(*btn_handler_t)();
extern const btn_handler_t empty_btn_handler;
void BUTTON_init(void);
void EINT0_IRQHandler(void);
void EINT1_IRQHandler(void);
void EINT2_IRQHandler(void);
// usage: call this in RIT, debouncing will be handled automatically
void button_handler_with_debouncing(btn_handler_t btnHandlers[3]);
