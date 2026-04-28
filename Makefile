CROSS_COMPILE ?= arm-none-eabi-
CC := $(CROSS_COMPILE)gcc

CFLAGS = -fno-common -ffreestanding -O0 \
	 -gdwarf-2 -g3 -Wall -Werror \
	 -mcpu=cortex-m4 -mthumb \
	 -Wl,-Thello.ld -nostartfiles \

FPU_FLAGS = -mfpu=fpv4-sp-d16 \
	 -mfloat-abi=hard

TARGET = final.bin
all: $(TARGET)

$(TARGET): main.c startup.c
	$(CC) $(CFLAGS) $(FPU_FLAGS) $^ -o final.elf
	$(CROSS_COMPILE)objcopy -Obinary final.elf final.bin
	$(CROSS_COMPILE)objdump -S final.elf > final.list



upload:
	openocd -f interface/stlink.cfg -f target/stm32f3x.cfg -c " program final.elf verify reset exit "
