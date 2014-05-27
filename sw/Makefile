
laserharp: laserharp.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o laserharp.o laserharp.c
	avr-gcc -mmcu=atmega328p laserharp.o -o laserharp
	avr-objcopy -O ihex -R .eeprom laserharp laserharp.hex	

prog: laserharp
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:laserharp.hex
	
clean:
	rm -f laserharp *.o *.hex
