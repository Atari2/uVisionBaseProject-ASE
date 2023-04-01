#include <stdint.h>

/*
    * libsound.h
    *
    *  Created in 2023
    *      Author: Alessio R. (https://github.com/Atari2)
    *      MIT License
*/

enum {
	N_None = -1,
  N_Do = 261,
	N_Re = 293,
	N_Mi = 329,
	N_Fa = 349,
	N_Sol = 392,
	N_La = 440,
	N_Si = 493,
	N_C = N_Do,
	N_D = N_Re,
	N_E = N_Mi,
	N_F = N_Fa,
	N_G = N_Sol,
	N_A = N_La,
	N_B = N_Si
} typedef NoteFrequency;

enum {
	L_1,
	L_2,
	L_4,
	L_8,
	L_16,
	L_32,
	L_64
} typedef NoteLen;

struct Note {
	NoteFrequency freq;
	NoteLen length;
} typedef Note;

struct Sound {
	const uint8_t length;
	const uint16_t bpm;
	const Note notes[0xFF];
} typedef Sound;

void play_note(uint8_t bpm, const Note* note);
_Bool play_sound(const Sound* s);
void next_sound_tick(void);
void init_sound_system(void);
