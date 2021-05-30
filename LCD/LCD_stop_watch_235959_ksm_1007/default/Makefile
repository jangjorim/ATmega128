###############################################################################
# Makefile for the project LCD_stop_watch_235959_ksm_1007
###############################################################################

## General Flags
PROJECT = LCD_stop_watch_235959_ksm_1007
MCU = atmega128
TARGET = LCD_stop_watch_235959_ksm_1007.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99   -DF_CPU=16000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=LCD_stop_watch_235959_ksm_1007.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = LCD_stop_watch_235959_ksm_1007.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) LCD_stop_watch_235959_ksm_1007.hex LCD_stop_watch_235959_ksm_1007.eep LCD_stop_watch_235959_ksm_1007.lss size

## Compile
LCD_stop_watch_235959_ksm_1007.o: ../LCD_stop_watch_235959_ksm_1007.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) LCD_stop_watch_235959_ksm_1007.elf dep/* LCD_stop_watch_235959_ksm_1007.hex LCD_stop_watch_235959_ksm_1007.eep LCD_stop_watch_235959_ksm_1007.lss LCD_stop_watch_235959_ksm_1007.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

