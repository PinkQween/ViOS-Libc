PREFIX        := /opt/ViOS
TARGET        := i686-elf
CC            := $(TARGET)-gcc
AR            := $(TARGET)-ar
AS            := nasm
CFLAGS        := -ffreestanding -nostdlib -O2 -Wall -Wextra -Iinclude -Isrc
NASMFLAGS     := -f elf

SRC_C         := $(wildcard src/*.c) $(wildcard src/ViOS/*.c) $(wildcard crt/*.c)
SRC_S         := $(wildcard crt/*.s)
SRC_ASM       := $(wildcard crt/*.asm)

OBJ_C         := $(patsubst %.c, build/%.o, $(SRC_C))
OBJ_S         := $(patsubst %.s, build/%.o, $(SRC_S))
OBJ_ASM       := $(patsubst %.asm, build/%.o, $(SRC_ASM))

LIB_NAME      := libViOSlibc.a
LIB_PATH      := build/$(LIB_NAME)

all: prepare_headers $(LIB_PATH)

prepare_headers:
	@mkdir -p src/ViOS
	@mkdir -p src/sys
	@cp include/ViOS/*.h src/ViOS/ 2>/dev/null || true
	@cp include/sys/*.h src/sys/ 2>/dev/null || true

# Create static library
$(LIB_PATH): $(OBJ_C) $(OBJ_S) $(OBJ_ASM)
	$(AR) rcs $@ $^

# Compile C files
build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Assemble .s files with GAS
build/%.o: %.s
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Assemble .asm files with NASM
build/%.o: %.asm
	@mkdir -p $(dir $@)
	$(AS) $(NASMFLAGS) $< -o $@

install: all
	mkdir -p $(PREFIX)/lib
	mkdir -p $(PREFIX)/include
	cp $(LIB_PATH) $(PREFIX)/lib/

	@echo "Installing headers..."
	cp -r include/* $(PREFIX)/include/

clean:
	rm -rf build
	rm -f src/ViOS/*.h
	rm -f src/sys/*.h
