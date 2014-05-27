#ifndef __MIDI_H
#define __MIDI_H

enum {
	NOTE_C4 = 0x3c,
	NOTE_D4 = 0x3e,
	NOTE_E4 = 0x40,
	NOTE_F4 = 0x41,
	NOTE_G4 = 0x43,
	NOTE_A4 = 0x45,
	NOTE_B4 = 0x47
};

enum {
	DUR_SEMI = 1,
	DUR_MINIM = 2,
	DUR_CROCHET = 4,
	DUR_QUAVER = 8
};

enum {
	MIDI_NOTEON = 0x90, 
};

void midi_init();
void midi_send_noteon(char chan, char note, char velocity);
void midi_send_noteoff(char chan, char note);

#endif
