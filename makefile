IncludeTags = -Ilib -Ilib/libc -Ilib/ps1 -Ilib/vendor -Iinclude -Iinclude/core -Iinclude/hardware

CC = mipsel-linux-gnu-gcc
CFLAGS = $(IncludeTags) -g -Wall -Wa,--strip-local-absolute -ffreestanding -fno-builtin -fno-pic -nostdlib -fdata-sections -ffunction-sections -fsigned-char -fno-strict-overflow -march=r3000 -mabi=32 -mfp32 -mno-mt -mno-llsc -mno-abicalls -mgpopt -mno-extern-sdata -G8 -Og -mdivide-breaks

AS = mipsel-linux-gnu-gcc
AFLAGS = $(IncludeTags) -g -Wall -Wa,--strip-local-absolute -ffreestanding -fno-builtin -fno-pic -nostdlib -fdata-sections -ffunction-sections -fsigned-char -fno-strict-overflow -march=r3000 -mabi=32 -mfp32 -mno-mt -mno-llsc -mno-abicalls -mgpopt -mno-extern-sdata -G8 -Og -mdivide-breaks

LD = mipsel-linux-gnu-g++
LDFLAGS = -g -static -nostdlib -Wl,-gc-sections -T executable.ld

PYTHON = /usr/bin/python3.10
CONVERT_SCRIPT = ../tools/convertExecutable.py
TEXTURE_SCRIPT = tools/convertImage.py

# Define source files and object files
SRC_DIR := src
LIB_DIR := lib

BUILD_DIR := build

SRCS := $(strip $(wildcard $(SRC_DIR)/**/*.c) $(wildcard $(LIB_DIR)/**/*.c))
ASMS := $(strip $(wildcard $(SRC_DIR)/**/*.s) $(wildcard $(LIB_DIR)/**/*.s))

COBJS := $(SRCS:%.c=$(BUILD_DIR)/%.c.obj)
AOBJS := $(ASMS:%.s=$(BUILD_DIR)/%.s.obj)
OBJS := $(COBJS) $(AOBJS)

# Output binary names
TARGET_ELF = GAME.elf
TARGET_PSEXE = GAME.psexe


##########################################
# Convert all textures into binary files #
##########################################

# Define source directories
ASSETS_DIR := assets/textures
BPP_4_DIR := $(ASSETS_DIR)/4bpp
BPP_8_DIR := $(ASSETS_DIR)/8bpp
BPP_16_DIR := $(ASSETS_DIR)/16bpp

# Define output directories
TEXTURE_BUILD_DIR := build/assets/textures
BUILD_4_DIR := $(TEXTURE_BUILD_DIR)/4bpp
BUILD_8_DIR := $(TEXTURE_BUILD_DIR)/8bpp
BUILD_16_DIR := $(TEXTURE_BUILD_DIR)/16bpp

# Find all .png files
PNG_FILES_4BPP := $(wildcard $(BPP_4_DIR)/*.png)
PNG_FILES_8BPP := $(wildcard $(BPP_8_DIR)/*.png)
PNG_FILES_16BPP := $(wildcard $(BPP_16_DIR)/*.png)

# Define output .dat files (renamed to Data.dat)
DAT_FILES_4BPP := $(PNG_FILES_4BPP:$(BPP_4_DIR)/%.png=$(TEXTURE_BUILD_DIR)/4bpp/%Data.dat) $(PNG_FILES_4BPP:$(BPP_4_DIR)/%.png=$(TEXTURE_BUILD_DIR)/4bpp/%Palette.dat)
DAT_FILES_8BPP := $(PNG_FILES_8BPP:$(BPP_8_DIR)/%.png=$(TEXTURE_BUILD_DIR)/8bpp/%Data.dat) $(PNG_FILES_8BPP:$(BPP_8_DIR)/%.png=$(TEXTURE_BUILD_DIR)/8bpp/%Palette.dat)
DAT_FILES_16BPP := $(PNG_FILES_16BPP:$(BPP_16_DIR)/%.png=$(TEXTURE_BUILD_DIR)/16bpp/%Data.dat)

# Define output .s files
S_FILES_4BPP := $(DAT_FILES_4BPP:.dat=.s) $(wildcard $(TEXTURE_BUILD_DIR)/4bpp/*Palette.s)
S_FILES_8BPP := $(DAT_FILES_8BPP:.dat=.s) $(wildcard $(TEXTURE_BUILD_DIR)/8bpp/*Palette.s)
S_FILES_16BPP := $(DAT_FILES_16BPP:.dat=.s)

# Combine all .s files
S_FILES := $(S_FILES_4BPP) $(S_FILES_8BPP) $(S_FILES_16BPP)

# Rules for all .dat and .s files
all: convertImages build

convertImages: $(DAT_FILES) $(S_FILES)

build: $(TARGET_PSEXE)

# General rule for .dat and .palette.dat generation
$(TEXTURE_BUILD_DIR)/%Data.dat $(TEXTURE_BUILD_DIR)/%Palette.dat: $(ASSETS_DIR)/%.png | $(dir $@)
	mkdir -p $(dir $@)
	@case "$*" in \
		*4bpp*) BPP=4 ;; \
		*8bpp*) BPP=8 ;; \
		*16bpp*) BPP=16 ;; \
	esac; \
	if [ "$$BPP" = 16 ]; then \
		python3 $(TEXTURE_SCRIPT) -b $$BPP $< $(TEXTURE_BUILD_DIR)/$*Data.dat; \
	else \
		python3 $(TEXTURE_SCRIPT) -b $$BPP $< $(TEXTURE_BUILD_DIR)/$*Data.dat $(TEXTURE_BUILD_DIR)/$*Palette.dat; \
	fi

# Helper variable to extract base file name from path
BASE_NAME = $(notdir $(basename $<))

# Single rule for generating .s files for all bit depths
$(TEXTURE_BUILD_DIR)/%Data.s: $(TEXTURE_BUILD_DIR)/%Data.dat
	@echo '.section .data.$(basename $(notdir $<)), "aw"' > $@
	@echo '.balign 8' >> $@
	@echo '' >> $@
	@echo '.global $(basename $(notdir $<))' >> $@
	@echo '.type $(basename $(notdir $<)), @object' >> $@
	@echo '.size $(basename $(notdir $<)), ($(basename $(notdir $<))_end - $(basename $(notdir $<)))' >> $@
	@echo '' >> $@
	@echo '$(basename $(notdir $<)):' >> $@
	@echo '	.incbin "$(dir $@)$(basename $(notdir $<)).dat"' >> $@
	@echo '$(basename $(notdir $<))_end:' >> $@

$(TEXTURE_BUILD_DIR)/%Palette.s: $(TEXTURE_BUILD_DIR)/%Palette.dat
	@echo '.section .data.$(basename $(notdir $<)), "aw"' > $@
	@echo '.balign 8' >> $@
	@echo '' >> $@
	@echo '.global $(basename $(notdir $<))' >> $@
	@echo '.type $(basename $(notdir $<)), @object' >> $@
	@echo '.size $(basename $(notdir $<)), ($(basename $(notdir $<))_end - $(basename $(notdir $<)))' >> $@
	@echo '' >> $@
	@echo '$(basename $(notdir $<)):' >> $@
	@echo '	.incbin "$(dir $@)$(basename $(notdir $<)).dat"' >> $@
	@echo '$(basename $(notdir $<))_end:' >> $@

# Create directories if they don't exist
$(TEXTURE_BUILD_DIR)/%/:
	mkdir -p $@


##############################
# Build the rest of the code #
##############################

# Include .s files in the build
SOBJS := $(S_FILES:%.s=$(BUILD_DIR)/%.s.obj)

# Pattern rule to compile .s files into .s.obj
$(BUILD_DIR)/%.s.obj: %.s
	@mkdir -p $(dir $@)
	$(AS) $(AFLAGS) -MD -MT $@ -MF $@.d -o $@ -c $<

# Linking step
$(TARGET_ELF): $(OBJS) $(SOBJS)
	$(LD) $(LDFLAGS) -o $@ $^ -lgcc -lgcc

# Convert ELF to PS-EXE
$(TARGET_PSEXE): $(TARGET_ELF)
	@mkdir -p build
	mv $< build/
	cd build && $(PYTHON) $(CONVERT_SCRIPT) $(TARGET_ELF) $(TARGET_PSEXE)
	$(info Done!)

# Pattern rule to build C object files
$(BUILD_DIR)/%.c.obj: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MD -MT $@ -MF $@.d -o $@ -c $<

# Pattern rule to build assembly object files
$(BUILD_DIR)/%.s.obj: %.s
	@mkdir -p $(dir $@)
	$(AS) $(AFLAGS) -MD -MT $@ -MF $@.d -o $@ -c $<

# Include dependency files
-include $(COBJS:.obj=.obj.d) $(AOBJS:.obj=.obj.d) $(SOBJS:.obj=.obj.d)


# Clean rule to remove generated files
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean convertImages build

