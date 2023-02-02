#ifndef _DRAWING_INCL
#define _DRAWING_INCL
#include <stdint.h>

#define LCD_HEIGHT 320
#define LCD_WIDTH 240

extern volatile uint8_t PX_RT;

struct Coords {
	int16_t x;
	int16_t y;
} typedef Coords;

void set_scale(uint8_t scale);
void reset_scale(void);
void draw_image_noscale(Coords origin, int width, int height, const uint16_t image_data[height][width]);
void draw_image(Coords origin, int width, int height, const uint16_t image_data[height][width]);
void draw_image_flipped(Coords origin, int width, int height, const uint16_t image_data[height][width]);
void draw_rect(Coords origin, int width, int height, int border_thickness, uint16_t color, const uint16_t* bg_color);
void center_rect_in_rect(Coords* origin, int32_t width, int32_t height, int32_t o_width, int32_t o_height);
void center_text_in_rect(Coords* origin, int32_t width, int32_t height, uint32_t text_len, uint8_t text_scale);
void draw_text(int x, int y, const char* text, uint16_t color, uint8_t scale);
void draw_text_bg(int x, int y, const char* text, uint16_t color, uint16_t bg);
#endif
