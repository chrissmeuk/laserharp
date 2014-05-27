// laserharp.c - Laser harp firmware for Atmel ATMEGA328P
// (c) 2014 Chris Smith <me@chriss.me.uk>

#include <util/delay.h>
#include "uart.h"
#include "midi.h"

enum {
	NOTE_DELAY = 666,    /* 666ms ~= 90bpm */
};

 
// --------------------------------------------------------------------
// Entry point
// --------------------------------------------------------------------
int
main()
{
	int i;
	int scalea[] = { 
		NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, 
		NOTE_G4, NOTE_A4, NOTE_B4 };

	midi_init();

	while (1) {
		/* up */
		for (i = 0; i <= 6; i++) {
			midi_send_noteon(0, scalea[i], 0xff);
			_delay_ms(NOTE_DELAY);
			midi_send_noteoff(0, scalea[i]); 
		}
		/* down */
		for (i = 6; i >= 0; i--) {
			midi_send_noteon(0, scalea[i], 0xff);
			_delay_ms(NOTE_DELAY);
			midi_send_noteoff(0, scalea[i]); 
		}
	}

	return 0;
}
