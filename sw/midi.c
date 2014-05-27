#include "uart.h"
#include "midi.h"

// --------------------------------------------------------------------
// Initialise MIDI subsystem
// --------------------------------------------------------------------
void
midi_init()
{
	uart_init();
}

// --------------------------------------------------------------------
// Send MIDI note on
// --------------------------------------------------------------------
void
midi_send_noteon(char chan, char note, char velocity)
{
	uart_putchar(MIDI_NOTEON | chan);
	uart_putchar(note);
	uart_putchar(velocity);
}

// --------------------------------------------------------------------
// Send MIDI note off
// --------------------------------------------------------------------
void
midi_send_noteoff(char chan, char note)
{
	midi_send_noteon(chan, note, 0x0);
}
