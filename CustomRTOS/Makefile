#=================================================
# Toolchain
#=================================================

CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

#=================================================
# MCU Configuration
#=================================================

CPU     = cortex-m4
FPU     = fpv4-sp-d16
FLOAT   = hard

#=================================================
# Compiler Flags
#=================================================

CFLAGS  = -mcpu=$(CPU)
CFLAGS += -mthumb
CFLAGS += -mfpu=$(FPU)
CFLAGS += -mfloat-abi=$(FLOAT)
CFLAGS += -Wall
CFLAGS += -O0
CFLAGS += -g3
CFLAGS += -std=gnu99
CFLAGS += -ffunction-sections
CFLAGS += -fdata-sections

#=================================================
# Include Paths
#=================================================

INCLUDES = \
-I RTOS \
-I Drivers
#=================================================
# Linker Flags
#=================================================

LDFLAGS  = -T Core/linker.ld
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -mcpu=$(CPU)
LDFLAGS += -mthumb
LDFLAGS += -mfpu=$(FPU)
LDFLAGS += -mfloat-abi=$(FLOAT)

#=================================================
# Sources
#=================================================

SRC = \
Core/main.c \
Core/startup_stm32f4xx.c \
RTOS/scheduler.c \
RTOS/systick.c \
RTOS/pendsv_handler.c \
Drivers/gpio.c \
Drivers/spi.c \
Drivers/i2c.c

#=================================================
# Objects
#=================================================

OBJ = $(SRC:.c=.o)

#=================================================
# Target
#=================================================

TARGET = CustomRTOS

#=================================================
# Build
#=================================================

all: $(TARGET).elf

$(TARGET).elf: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@
	$(SIZE) $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

#=================================================
# Binary Output
#=================================================

hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $(TARGET).elf $(TARGET).hex

bin: $(TARGET).elf
	$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin

#=================================================
# Clean
#=================================================

clean:
	rm -f Core/*.o
	rm -f RTOS/*.o
	rm -f Drivers/*.o
	rm -f *.elf
	rm -f *.hex
	rm -f *.bin

#=================================================
# Flash (ST-Link + OpenOCD)
#=================================================

flash:
	openocd -f interface/stlink.cfg \
	         -f target/stm32f4x.cfg \
	         -c "program $(TARGET).elf verify reset exit"

.PHONY: all clean flash hex bin