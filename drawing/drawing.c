/*
    * drawing.c
    *
    *  Created in 2023
    *      Author: Alessio R. (https://github.com/Atari2)
    *      MIT License
*/

#include "LPC17xx.h"
#include <string.h>
#include "../GLCD/GLCD.h" 
#include "../GLCD/AsciiLib.h"
#include "drawing.h"
#include "../macros.h"

volatile _Bool drawing = 0;
volatile uint8_t PX_RT = 4;

void set_scale(uint8_t scale) {
	PX_RT = scale;
}
void reset_scale(void) {
	PX_RT = 4;
}

// this function only handles either straight vertical or straight horizontal lines
// it also assumes that x1 < x2 and y1 < y2
static __attribute__((always_inline)) void draw_straight_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
	if (x1 == x2) {
		// vertical line
		for (uint16_t i = y1; i <= y2; ++i) {
			LCD_SetPoint(x1, i, color);
		}
	} else {
		// horizontal line
		for (uint16_t i = x1; i <= x2; ++i) {
			LCD_SetPoint(i, y1, color);
		}
	}
}

static __attribute__((always_inline)) void draw_color_at(int x, int y, uint16_t color) {
	const int real_x = x * PX_RT;
	const int real_y = y * PX_RT;
	for (int i = 0; i < PX_RT; ++i) {
		for (int j = 0; j < PX_RT; ++j) {
			LCD_SetPoint(real_x + j, real_y + i, color); 
		}
	}
}

void draw_image_noscale(Coords origin, int width, int height, const uint16_t image_data[height][width]) {
	int i, j;
	drawing = 1;
	for (i = 0; i < height; ++i) {
		for (j = 0; j < width; ++j) {
			if (LCD_GetPoint(origin.x + j, origin.y + i) >= 0xFBFF) {
				LCD_SetPoint(origin.x + j, origin.y + i, image_data[i][j]);
			}
		}
	}
	drawing = 0;
}

void draw_image(Coords origin, int width, int height, const uint16_t image_data[height][width]) {
	int i, j;
	drawing = 1;
	for (i = 0; i < height; ++i) {
		for (j = 0; j < width; ++j) {
			draw_color_at(origin.x + j, origin.y + i, image_data[i][j]);
		}
	}
	drawing = 0;
}

void draw_image_flipped(Coords origin, int width, int height, const uint16_t image_data[height][width]) {
	int i, j;
	drawing = 1;
	for (i = 0; i < height; ++i) {
		for (j = width - 1; j >= 0; --j) {
			draw_color_at(origin.x + (width - 1) - j, origin.y + i, image_data[i][j]);
		}
	}
	drawing = 0;
}

void draw_rect(Coords origin, int width, int height, int border_thickness, uint16_t color, const uint16_t* bg_color) {
	int i = 0;
	uint16_t bg_color_value = 0;
	drawing = 1;
	for (i = 0; i < border_thickness; ++i) {
		draw_straight_line(origin.x, origin.y, origin.x + width, origin.y, color); // top line
		draw_straight_line(origin.x, origin.y + height, origin.x + width, origin.y + height, color); // bottom line
		draw_straight_line(origin.x, origin.y, origin.x, origin.y + height, color); // left line
		draw_straight_line(origin.x + width, origin.y, origin.x + width, origin.y + height, color); // right line
		origin.x++;
		origin.y++;
		width -= 2;
		height -= 2;
	}
	if (bg_color) {
		bg_color_value = *bg_color;
		for (i = origin.y; i <= origin.y + height; ++i) {
			draw_straight_line(origin.x, i, origin.x + width, i, bg_color_value);
		} 
	}
	drawing = 0;
}

void draw_char_expanded(uint16_t x, uint16_t y, char c, uint16_t charColor, uint8_t scale) {
	uint16_t i, j, k;
	uint8_t buffer[16], tmp_char;
	GetASCIICode(buffer,c);
	for(i=0; i<FONT_HEIGHT*scale; i += scale) {
		tmp_char = buffer[i / scale];
		for(j=0; j<FONT_WIDTH*scale; j += scale) {
			if(((tmp_char >> ((FONT_WIDTH-1) - (j / scale))) & 0x01) == 0x01) {
				for (k = 0; k < scale; ++k) {
					draw_straight_line(x + j, y + i + k, x  + j + scale, y + i + k, charColor);
				}
			}
		}
	}
}
void draw_char(uint16_t x, uint16_t y, char c, uint16_t charColor) {
	uint16_t i, j;
	uint8_t buffer[16], tmp_char;
	GetASCIICode(buffer,c);
	for(i=0; i<FONT_HEIGHT; i++) {
		tmp_char = buffer[i];
		for(j=0; j<FONT_WIDTH; j++) {
			if(((tmp_char >> ((FONT_WIDTH-1) - j)) & 0x01) == 0x01) {
				LCD_SetPoint(x + j, y + i, charColor);
			}
		}
	}
}

void draw_text(int x, int y, const char* text, uint16_t color, uint8_t scale) {
	char TempChar;
	const uint16_t fw = FONT_WIDTH * scale;
	const uint16_t fh = FONT_HEIGHT * scale;
	drawing = 1;
	do {
		TempChar = *text++;
		if (scale == 1) {
			draw_char(x, y, TempChar, color);
		} else {
			draw_char_expanded(x, y, TempChar, color, scale);    
		}
		if(x < MAX_X - fw) {
			x += fw;
		} else if (y < MAX_Y - fh) {
			x = 0;
			y += fh;
		} else {
			x = 0;
			y = 0;
		}    
	} while (*text != 0);
	drawing = 0;
}

void draw_text_bg(int x, int y, const char* text, uint16_t color, uint16_t bg) {
	drawing = 1;
	GUI_Text(x, y, (uint8_t*)text, color, bg);
	drawing = 0;
}

void center_rect_in_rect(Coords* origin, int32_t width, int32_t height, int32_t o_width, int32_t o_height) {
	origin->x = origin->x + (width / 2) - (o_width / 2);
	origin->y = origin->y + (height / 2) - (o_height / 2);
}

void center_text_in_rect(Coords* origin, int32_t width, int32_t height, uint32_t text_len, uint8_t text_scale) {
	const uint32_t pixel_text_width = (text_len * (text_scale* FONT_WIDTH));
	const uint32_t pixel_text_height = (text_scale *FONT_HEIGHT);
	
	center_rect_in_rect(origin, width, height, pixel_text_width, pixel_text_height);
}
