IncludeTags = -Ilib -Ilib/libc -Ilib/ps1 -Ilib/vendor -Iinclude -Iinclude/core -Iinclude/hardware -Iinclude/software

# Detect which toolchain is available
ifneq ($(shell which mipsel-none-elf-gcc 2>/dev/null),)
CC_PREFIX = mipsel-none-elf
else
ifneq ($(shell which mipsel-linux-gnu-gcc 2>/dev/null),)
CC_PREFIX = mipsel-linux-gnu
else
$(error A mipsel-none-elf or mipsel-linux-gnu GCC toolchain must be installed and added to PATH)
endif
endif

ifneq ($(shell which py 2>/dev/null),)
PYTHON = py -3
else
PYTHON = python3
endif

CC = $(CC_PREFIX)-gcc
CFLAGS_DEBUG = $(IncludeTags) -g -Wall -Wa,--strip-local-absolute -ffreestanding -fno-builtin -fno-pic -nostdlib -fdata-sections -ffunction-sections -fsigned-char -fno-strict-overflow -march=r3000 -mabi=32 -mfp32 -mno-mt -mno-llsc -mno-abicalls -mgpopt -mno-extern-sdata -G8 -Og -mdivide-breaks
CFLAGS_RELEASE = $(IncludeTags)  -Wall -Wa,--strip-local-absolute -ffreestanding -fno-builtin -fno-pic -nostdlib -fdata-sections -ffunction-sections -fsigned-char -fno-strict-overflow -march=r3000 -mabi=32 -mfp32 -mno-mt -mno-llsc -mno-abicalls -mgpopt -mno-extern-sdata     -O3 -mdivide-breaks

# By default, use the debug flags
CFLAGS = $(CFLAGS_DEBUG)

# If 'release' target is specified, override CFLAGS
ifeq ($(MAKECMDGOALS),release)
CFLAGS = $(CFLAGS_RELEASE)
endif

AS = $(CC_PREFIX)-gcc
AFLAGS = $(CFLAGS)

LD = $(CC_PREFIX)-gcc
LDFLAGS = -g -static -nostdlib -Wl,-gc-sections -G8 -Texecutable.ld

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
TEXTURES_DIR := assets/textures
BPP_4_DIR := $(TEXTURES_DIR)/4bpp
BPP_8_DIR := $(TEXTURES_DIR)/8bpp
BPP_16_DIR := $(TEXTURES_DIR)/16bpp

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

##########################################
# Include .vag audio files in the binary #
##########################################

AUDIO_DIR := assets/audio
AUDIO_BUILD_DIR := build/assets/audio

# Find all .vag files
VAG_FILES := $(wildcard $(AUDIO_DIR)/*.vag)

# Define output .dat and .s files for .vag
DAT_FILES_VAG := $(VAG_FILES:$(AUDIO_DIR)/%.vag=$(AUDIO_BUILD_DIR)/%Audio.dat)
S_FILES_VAG := $(DAT_FILES_VAG:.dat=.s)

# Add audio .s files to the list of all .s files
S_FILES := $(S_FILES) $(S_FILES_VAG)

# Rule to copy .vag files to .dat in the build directory
$(AUDIO_BUILD_DIR)/%Audio.dat: $(AUDIO_DIR)/%.vag
	@mkdir -p $(dir $@)  # Ensure directory exists
	cp $< $@  # Copy .vag file to .dat file

# Rule to generate .s files from .dat files for audio
$(AUDIO_BUILD_DIR)/%Audio.s: $(AUDIO_BUILD_DIR)/%Audio.dat
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



release: all
all: convertImages convertAudio build buildCD

convertImages: $(DAT_FILES) $(S_FILES)

convertAudio: $(DAT_FILES_VAG) $(S_FILES_VAG)

build: $(TARGET_PSEXE)

# General rule for .dat and .palette.dat generation
$(TEXTURE_BUILD_DIR)/%Data.dat $(TEXTURE_BUILD_DIR)/%Palette.dat: $(TEXTURES_DIR)/%.png | $(dir $@)
	mkdir -p $(dir $@)
	@case "$*" in \
		*4bpp*) BPP=4 ;; \
		*8bpp*) BPP=8 ;; \
		*16bpp*) BPP=16 ;; \
	esac; \
	if [ "$$BPP" = 16 ]; then \
		$(PYTHON) $(TEXTURE_SCRIPT) -b $$BPP $< $(TEXTURE_BUILD_DIR)/$*Data.dat; \
	else \
		$(PYTHON) $(TEXTURE_SCRIPT) -b $$BPP $< $(TEXTURE_BUILD_DIR)/$*Data.dat $(TEXTURE_BUILD_DIR)/$*Palette.dat; \
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
	$(LD) $(LDFLAGS) $^ -o $@ -lgcc

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

buildCD:
	cp build/$(TARGET_PSEXE) CDROM
	mv CDROM/$(TARGET_PSEXE) CDROM/GAME.EXE
	mkpsxiso -y CDROM/mkpsxiso.xml
	mv GAME.bin CDROM/GAME.bin
	mv GAME.cue CDROM/GAME.cue

# Clean rule to remove generated files
clean:
	rm -rf $(BUILD_DIR)
	rm -f CDROM/$(TARGET_PSEXE)
	rm -f CDROM/GAME.cue CDROM/GAME.bin CDROM/GAME.EXE

.PHONY: all clean convertImages build release asm

