DEVICE=/dev/ttyACM0

laserharp: laserharp.c
	avr-gcc $(CFLAGS) -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o laserharp.o laserharp.c
	avr-gcc -mmcu=atmega328p laserharp.o -o laserharp
	avr-objcopy -O ihex -R .eeprom laserharp laserharp.hex	

prog: laserharp
	avrdude -F -V -c arduino -p ATMEGA328P -P $(DEVICE) -b 115200 -U flash:w:laserharp.hex

dumpstream:
	stty -F $(DEVICE) cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts	
	cat $(DEVICE) | hexdump -v -e '/1 "%02X\n"'
	
clean:
	rm -f laserharp *.o *.hex
