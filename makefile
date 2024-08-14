CC = mipsel-linux-gnu-gcc
CFLAGS = -Ilib -Ilib/libc -Iinclude -g -Wall -Wa,--strip-local-absolute -ffreestanding -fno-builtin -fno-pic -nostdlib -fdata-sections -ffunction-sections -fsigned-char -fno-strict-overflow -march=r3000 -mabi=32 -mfp32 -mno-mt -mno-llsc -mno-abicalls -mgpopt -mno-extern-sdata -G8 -Og -mdivide-breaks

AS = mipsel-linux-gnu-gcc
AFLAGS = -Ilib -Ilib/libc -Iinclude -g -Wall -Wa,--strip-local-absolute -ffreestanding -fno-builtin -fno-pic -nostdlib -fdata-sections -ffunction-sections -fsigned-char -fno-strict-overflow -march=r3000 -mabi=32 -mfp32 -mno-mt -mno-llsc -mno-abicalls -mgpopt -mno-extern-sdata -G8 -Og -mdivide-breaks

LD = mipsel-linux-gnu-g++
LDFLAGS = -g -static -nostdlib -Wl,-gc-sections -T executable.ld

PYTHON = /usr/bin/python3.10
CONVERT_SCRIPT = ../tools/convertExecutable.py

# Define source files and object files
SRC_DIR := src
LIB_DIR := lib

BUILD_DIR := build

SRCS := $(strip $(wildcard $(SRC_DIR)/**/*.c) $(wildcard $(LIB_DIR)/**/*.c))
ASMS := $(strip $(wildcard $(SRC_DIR)/**/*.s) $(wildcard $(LIB_DIR)/**/*.s))

COBJS := $(SRCS:%.c=$(BUILD_DIR)/%.c.obj)
AOBJS := $(ASMS:%.S=$(BUILD_DIR)/%.s.obj)
OBJS := $(COBJS) $(AOBJS)

# Output binary names
TARGET_ELF = GAME.elf
TARGET_PSEXE = GAME.psexe

# Default target
all: $(TARGET_PSEXE)

# Linking step
$(TARGET_ELF): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^ -lgcc -lgcc

# Convert ELF to PS-EXE
$(TARGET_PSEXE): $(TARGET_ELF)
	@mkdir -p build
	mv $< build/
	cd build && $(PYTHON) $(CONVERT_SCRIPT) $(TARGET_ELF) $(TARGET_PSEXE)

# Pattern rule to build C object files
$(BUILD_DIR)/%.c.obj: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MD -MT $@ -MF $@.d -o $@ -c $<

# Pattern rule to build assembly object files
$(BUILD_DIR)/%.s.obj: %.s
	@mkdir -p $(dir $@)
	$(AS) $(AFLAGS) -MD -MT $@ -MF $@.d -o $@ -c $<

# Include dependency files
-include $(COBJS:.obj=.obj.d) $(SAOBJS:.obj=.obj.d)

# Clean rule
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean



























