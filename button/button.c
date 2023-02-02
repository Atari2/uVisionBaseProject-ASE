#include "button.h"
#include "lpc17xx.h"

/**
 * @brief  Function that initializes Buttons
 */
void BUTTON_init(void) {

  LPC_PINCON->PINSEL4    |= (1 << 20);		 /* External interrupt 0 pin selection */
  LPC_GPIO2->FIODIR      &= ~(1 << 10);    /* PORT2.10 defined as input          */

  LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
  LPC_GPIO2->FIODIR      &= ~(1 << 11);    /* PORT2.11 defined as input          */
  
  LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
  LPC_GPIO2->FIODIR      &= ~(1 << 12);    /* PORT2.12 defined as input          */

  LPC_SC->EXTMODE = 0x7;

  NVIC_EnableIRQ(EINT2_IRQn);              /* enable irq in nvic                 */
  NVIC_EnableIRQ(EINT1_IRQn);              /* enable irq in nvic                 */
  NVIC_EnableIRQ(EINT0_IRQn);              /* enable irq in nvic                 */
}

volatile int btnPressed[3] = {0, 0, 0};
const btn_handler_t empty_btn_handler = NULL;
static const enum IRQn IRQ_Numbers[3] = {EINT0_IRQn, EINT1_IRQn, EINT2_IRQn};

void button_handler_with_debouncing(btn_handler_t btnHandlers[3])
{			
	volatile int i = 0;
	for (i = BTN0_ID; i <= BTN2_ID; ++i) {
		if (btnPressed[i] != 0) {
			btnPressed[i]++;
			if ((LPC_GPIO2->FIOPIN & (1<<(10 + i))) == 0) {
				switch (btnPressed[i]) {
					case 2:
						if (btnHandlers[i] != empty_btn_handler) {
							btnHandlers[i]();
						}
						break;
					default:
						break;
				}
			} else {
				btnPressed[i] = 0;
				NVIC_EnableIRQ(IRQ_Numbers[i]);
				LPC_PINCON->PINSEL4 |= (1 << (20 + i*2));		 /* External interrupt 0 pin selection */
			}
		}
	} 
  return;
}
