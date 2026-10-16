# ============================================================================
#  AVR bare-metal relay project — ATmega328P (16 MHz)
#  Targets: make | make flash | make size | make clean
# ============================================================================

MCU        = atmega328P
F_CPU      = 16000000UL
TARGET     = relay_2s_main
SRC        = relay_2s_main.c

# avrdude connection — adjust PORT for your programmer:
#   Linux  : /dev/ttyUSB0 or /dev/ttyACM0
#   Windows: COM5
PROGRAMMER = arduino
PORT       = COM5
BAUD       = 115200

CC      = avr-gcc
OBJCOPY = avr-objcopy
SIZE    = avr-size
AVRDUDE = avrdude

CFLAGS  = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Wextra -std=c99
HEX     = $(TARGET).hex

.PHONY: all flash size clean

all: $(HEX)

$(TARGET).elf: $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

$(HEX): $(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

size: $(TARGET).elf
	$(SIZE) --mcu=$(MCU) -C $< || $(SIZE) $<

flash: $(HEX)
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$<:i

clean:
	del /Q $(TARGET).elf $(HEX) 2>NUL || rm -f $(TARGET).elf $(HEX)
