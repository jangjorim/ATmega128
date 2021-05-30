###############################################################################
# Makefile for the project ADC_LCD_Display_VR_CdS
###############################################################################

## General Flags
PROJECT = ADC_LCD_Display_VR_CdS
MCU = atmega128
TARGET = ADC_LCD_Display_VR_CdS.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99 -DF_CPU=16000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=ADC_LCD_Display_VR_CdS.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = ADC_LCD_Display_VR_CdS.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) ADC_LCD_Display_VR_CdS.hex ADC_LCD_Display_VR_CdS.eep ADC_LCD_Display_VR_CdS.lss size

## Compile
ADC_LCD_Display_VR_CdS.o: ../ADC_LCD_Display_VR_CdS.c
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
	-rm -rf $(OBJECTS) ADC_LCD_Display_VR_CdS.elf dep/* ADC_LCD_Display_VR_CdS.hex ADC_LCD_Display_VR_CdS.eep ADC_LCD_Display_VR_CdS.lss ADC_LCD_Display_VR_CdS.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

