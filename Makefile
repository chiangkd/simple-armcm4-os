CROSS_COMPILE ?= arm-none-eabi-
CC := $(CROSS_COMPILE)gcc
AS := $(CROSS_COMPILE)as

CMSIS_DIRS := core device

STARTUP := CMSIS/device/startup_stm32f30x.s
SYSTEM  := CMSIS/device/system_stm32f30x.c
KERNEL  := kernel/port_asm.s kernel/port.c

CFLAGS = -fno-common -ffreestanding -O0 \
	 -gdwarf-2 -g3 -Wall -Werror \
	 -mcpu=cortex-m4 -mthumb \
	 -Wl,-Tstm32f303ze.ld -nostartfiles \

CFLAGS += $(foreach d,$(CMSIS_DIRS), -ICMSIS/$(d))
CFLAGS += -ISPL
CFLAGS += -Ikernel
CFLAGS += -DUSE_STDPERIPH_DRIVER

FPU_FLAGS = -mfpu=fpv4-sp-d16 \
	 -mfloat-abi=hard

C_SRCS := main.c \
		led.c \
		uart.c \
		$(wildcard SPL/*c) \
		$(SYSTEM)

SRCS := $(C_SRCS) $(STARTUP) $(KERNEL)

OBJ_DIR := build

OBJS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(C_SRCS))) \
        $(OBJ_DIR)/startup_stm32f30x.o \
		$(OBJ_DIR)/port_asm.o \
		$(OBJ_DIR)/port.o


TARGET = final.bin

all: $(OBJ_DIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(FPU_FLAGS) $^ -o final.elf
	$(CROSS_COMPILE)objcopy -Obinary final.elf final.bin
	$(CROSS_COMPILE)objdump -S final.elf > final.list


# Compile .c to .o
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: SPL/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: CMSIS/device/%.c
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/startup_stm32f30x.o: $(STARTUP)
	$(AS) $(ASFLAGS) -c $< -o $@

$(OBJ_DIR)/port_asm.o: kernel/port_asm.s
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/port.o: kernel/port.c
	$(CC) $(CFLAGS) -c $< -o $@


upload:
	openocd -f interface/stlink.cfg -f target/stm32f3x.cfg -c " program final.elf verify reset exit "

debug:
	openocd -f interface/stlink.cfg -f target/stm32f3x.cfg

clean:
	rm -rf build
	rm *.bin *.elf *.list