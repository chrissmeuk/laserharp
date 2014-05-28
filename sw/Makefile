CC=avr-gcc
OBJCOPY=avr-objcopy
override CFLAGS += -c -Os -DF_CPU=16000000 -mmcu=atmega328p
LDFLAGS=-mmcu=atmega328p
DEVICE=/dev/ttyACM0
SOURCES=laserharp.c midi.c
OBJECTS=$(SOURCES:.c=.o)
IMAGE=laserharp

all: $(SOURCES) $(IMAGE)
	
$(IMAGE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	$(OBJCOPY) -O ihex -R .eeprom $(IMAGE) $(IMAGE).hex

.c.o:
	$(CC) $(CFLAGS) $< -o $@

prog: $(IMAGE)
	avrdude -F -V -c arduino -p ATMEGA328P -P $(DEVICE) -b 115200 -U flash:w:$(IMAGE).hex

dumpstream:
	stty -F $(DEVICE) cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts	
	cat $(DEVICE) | hexdump -v -e '/1 "%02X\n"'
	
clean:
	rm -f laserharp *.o *.hex
