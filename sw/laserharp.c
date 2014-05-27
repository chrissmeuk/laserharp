#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

enum {
	MIDI_NOTEON = 0x90, 
	NOTE_DELAY = 666,    /* 666ms ~= 90bpm */
};

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


// --------------------------------------------------------------------
// Intialise UART and configure for_SEMI     1
// --------------------------------------------------------------------
void
uart_init()
{
#undef BAUD
#ifdef DBGDUMP
#define BAUD 9600
#else
#define BAUD 31250
#endif
#include <util/setbaud.h>
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
#if USE_2X
	UCSR0A |= _BV(U2X0);
#else
	UCSR0A &= ~(_BV(U2X0));
#endif
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
	UCSR0B = _BV(TXEN0);
}

// --------------------------------------------------------------------
// Put a character on the UART
// --------------------------------------------------------------------
void 
uart_putchar(char c)
{
	// wait  any outgoing TX to finish
	loop_until_bit_is_set(UCSR0A, UDRE0);
	// send char
	UDR0 = c;
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
 
// --------------------------------------------------------------------
// Entry point
// --------------------------------------------------------------------
int
main()
{
	int i;
	int scalea[] = { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4 };

	uart_init();

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
