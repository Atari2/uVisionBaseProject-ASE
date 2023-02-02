#include "libsound.h"
#include "../timer/timer.h"
#include "LPC17xx.h"
#include "../macros.h"

static uint8_t current_tick = 0;
const float sound_timer = 50 ms;		// start up checking for sounds every 50 ms
static const int16_t SinTableAdjusted[45] = {
	0, 71, 141, 207, 271, 328, 379, 423, 459, 
	486, 503, 511, 508, 496, 473, 442, 402, 354, 
	299, 239, 174, 106, 35, -37, -108, -175, -241, 
	-301, -356, -404, -444, -475, -498, -510, -512, -505, 
	-488, -461, -425, -381, -330, -271, -209, -142, -72
};
static const int32_t HALF_POINT_SIN = 512;

static uint32_t note_to_k(uint32_t hz) {
#ifndef SIMULATOR
	return 25000000 / (hz * ARRAY_SIZE(SinTableAdjusted));
#else
	return 25000000 / (hz * 10);
#endif
}

// returns milliseconds
static float note_len_from_sound(uint8_t bpm, NoteLen note_len) {
	const float quarter_note_duration = 1000.0f / ((float)bpm / 60.0f);
	switch (note_len) {
		case L_1:
			return quarter_note_duration * 4;
		case L_2:
			return quarter_note_duration * 2;
		case L_4:
			return quarter_note_duration;
		case L_8:
			return quarter_note_duration / 2;
		case L_16:
			return quarter_note_duration / 4;
		case L_32:
			return quarter_note_duration / 8;
		case L_64:
			return quarter_note_duration / 16;
		default:
			return quarter_note_duration;
	}
}

static void set_dacr_value(int16_t v) {
  uint32_t val = (int32_t)v + HALF_POINT_SIN; // adjust according to current volume			
	LPC_DAC->DACR = ((val & 0x3ff) << 6);  		   					 			 // shift by 6 because DACR uses bits 6..15 for the value, rest is reserved
}

void init_sound_system(void) {
	init_timer(Timer2, sound_timer, SCALE(1), 2);
	enable_timer(Timer2);
}

void next_sound_tick(void) {
	set_dacr_value(SinTableAdjusted[current_tick++]);
	if (current_tick == ARRAY_SIZE(SinTableAdjusted)) {
		current_tick = 0;
	}
}
void play_note(uint8_t bpm, const Note* note) {
	reset_timer(Timer2);
	init_timer(Timer2, note_len_from_sound(bpm, note->length), SCALE(1), 2);
	if (note->freq != N_None) {
		reset_timer(Timer3);
		init_timer_k(Timer3, note_to_k(note->freq), SCALE(1), 1);
		enable_timer(Timer3);
	}
	enable_timer(Timer2);
}
_Bool play_sound(const Sound* s) {
	static int cur_note = 0;
	current_tick = 0;
	if (s->length > 0) {
		if (cur_note > 0) {
			disable_timer(Timer3);
			reset_timer(Timer3);
		}
		if (cur_note == s->length) {
			// at end of sound			
			cur_note = 0;
			reset_timer(Timer2);
			init_timer(Timer2, sound_timer, SCALE(1), 2);
			enable_timer(Timer2);
			return 1;
		} else {
			play_note(s->bpm, &s->notes[cur_note]);
			cur_note++;
			return 0;
		}
	} else {
		return 1;
	}
}
