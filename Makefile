NAME = main

MODULES = spi.o apa102.o hall.o 
CFLAGS = -g -Wall -Og -std=c99 -ffreestanding -I$(CS107E)/include
LDFLAGS = -nostdlib -T memmap -L$(CS107E)/lib
LDLIBS = -lpi -lgcc

SRC = RTTmeasure.c hall.c spi.c apa102.c

all : $(NAME).bin

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.elf: %.o hall.o apa102.o spi.o RTTmeasure.o
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

hall.o: hall.c hall.h
	arm-none-eabi-gcc $(CFLAGS) -c hall.c -o hall.o

apa102.o: apa102.c apa102.h
	arm-none-eabi-gcc $(CFLAGS) -c apa102.c apa102.h

spi.o: spi.c spi.h
	arm-none-eabi-gcc $(CFLAGS) -c spi.c spi.h

RTTmeasure.o: RTTmeasure.c RTTmeasure.h
	arm-none-eabi-gcc $(CFLAGS) -c RTTmeasure.c RTTmeasure.h

%.o: %.s
	arm-none-eabi-as $< -o $@

%.list: %.o
	arm-none-eabi-objdump -d $< > $@

run: $(NAME).bin
	rpi-run.py -p $<

clean:
	rm -f *.o *.bin *.elf *.list

.PHONY: all clean run

.PRECIOUS: %.elf %.o

