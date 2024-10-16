CC = i686-elf-g++
LD = i686-elf-ld
ASM = nasm

BIN = DariusOS.bin
CPPFLAGS  := -g -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -O0 -falign-jumps -falign-functions -falign-labels -fomit-frame-pointer -finline-functions -falign-loops -fstrength-reduce -Wno-unused-function -Wno-unused-parameter -fno-builtin -Wno-unused-label -Wno-cpp -fno-rtti -fno-exceptions -Iinc
LDFLAGS := -g -relocatable
LIBS 	:= 
INCLUDES = -I.

LIBDIR	= 

BUILDDIR  = Build
BOOTDIR   = Kernel/Boot
KERNELDIR = Kernel

include $(BOOTDIR)/make.config
include $(KERNELDIR)/make.config

CFLAGS 	:= $(CPPFLAGS) $(LIBDIR)

OBJS=\
$(BOOT_OBJS) \
$(KERNEL_OBJS) \

OBJS_OUT := $(foreach item,$(OBJS),$(BUILDDIR)/$(item))

.PHONY: all clean
.SUFFIXES: .o .c .cpp .asm.o .asm

all: $(BIN)

$(BIN): $(OBJS) $(KERNELDIR)/linker.ld
	$(ASM) -f bin $(BOOTDIR)/Bootloader.asm -o $(BUILDDIR)/$(BOOTDIR)/Bootloader.bin
	$(LD) $(LDFLAGS) $(OBJS_OUT) -o $(BUILDDIR)/KernelObject.o
	$(CC) -T $(KERNELDIR)/linker.ld -o $(BUILDDIR)/Kernel.bin $(CPPFLAGS) $(BUILDDIR)/KernelObject.o $(LIBS)

	rm -rf $(BUILDDIR)/$(BIN)
	dd if=$(BUILDDIR)/$(BOOTDIR)/Bootloader.bin >> $(BUILDDIR)/$(BIN)
	dd if=$(BUILDDIR)/Kernel.bin >> $(BUILDDIR)/$(BIN)
	dd if=/dev/zero bs=512 count=100 >> $(BUILDDIR)/$(BIN)

.cpp.o:
	@mkdir -p $(BUILDDIR)/$(@D)
	$(CC) -c $< -o $(BUILDDIR)/$@ -std=c++20 $(CPPFLAGS) $(INCLUDES)

%.asm.o: %.asm
	@mkdir -p $(BUILDDIR)/$(@D)
	$(ASM) -f elf -g $< -o $(BUILDDIR)/$@

clean:
	rm -f $(BUILDDIR)/$(BIN)
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d
	rm -f $(OBJS:.o=.bin) *.bin */*.bin */*/*.bin
	rm -rf $(BUILDDIR)

run:
	qemu-system-i386 -hda $(BUILDDIR)/$(BIN)

-include $(OBJS:.o=.d)
