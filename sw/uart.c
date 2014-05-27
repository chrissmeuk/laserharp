#include <avr/io.h>

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

