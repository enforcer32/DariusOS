CC = i686-elf-g++
LD = i686-elf-ld
ASM = nasm

BOOTLOADER_BIN = Bootloader.bin
KERNEL_BIN = Kernel.elf
CPPFLAGS  := -g -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -O0 -falign-jumps -falign-functions -falign-labels -fomit-frame-pointer -finline-functions -falign-loops -fstrength-reduce -Wno-unused-function -Wno-unused-parameter -fno-builtin -Wno-unused-label -Wno-cpp -fno-rtti -fno-exceptions -Iinc
LDFLAGS := -g -relocatable
LIBS 	:= 
INCLUDES = -I.

LIBDIR	= 

BUILD_DIR		= Build
BOOTLOADER_DIR	= Bootloader
KERNEL_DIR 		= Kernel
ARCH_DIR 		= Kernel/Arch
NXN_DIR 		= Kernel/NXN
DRIVERS_DIR 	= Kernel/Drivers

include $(BOOTLOADER_DIR)/make.config
include $(KERNEL_DIR)/make.config
include $(ARCH_DIR)/make.config
include $(NXN_DIR)/make.config
include $(DRIVERS_DIR)/make.config

CFLAGS 	:= $(CPPFLAGS) $(LIBDIR)

BL_OBJS=\
$(BOOTLOADER_OBJS) \

KRNL_OBJS=\
$(KERNEL_OBJS) \
$(ARCH_OBJS) \
$(NXN_OBJS) \
$(DRIVERS_OBJS) \

BL_OBJS_OUT := $(foreach item,$(BL_OBJS),$(BUILD_DIR)/$(item))
KRNL_OBJS_OUT := $(foreach item,$(KRNL_OBJS),$(BUILD_DIR)/$(item))

.PHONY: all clean
.SUFFIXES: .o .c .cpp .asm.o .asm

all: $(BOOTLOADER_BIN) $(KERNEL_BIN)

$(BOOTLOADER_BIN): $(BL_OBJS) $(BOOTLOADER_DIR)/linker.ld
	$(ASM) -f bin $(BOOTLOADER_DIR)/Bootsector.asm -o $(BUILD_DIR)/$(BOOTLOADER_DIR)/Bootsector.bin
	$(LD) $(LDFLAGS) $(BL_OBJS_OUT) -o $(BUILD_DIR)/$(BOOTLOADER_DIR)/BootloaderObject.o -Map=$(BUILD_DIR)/$(BOOTLOADER_DIR)/BootloaderObject.map
	$(CC) -T $(BOOTLOADER_DIR)/linker.ld -o $(BUILD_DIR)/$(BOOTLOADER_DIR)/BootloaderLinked.bin $(CPPFLAGS) $(BUILD_DIR)/$(BOOTLOADER_DIR)/BootloaderObject.o $(LIBS)

	rm -rf $(BUILD_DIR)/$(BOOTLOADER_BIN)
	dd if=$(BUILD_DIR)/$(BOOTLOADER_DIR)/Bootsector.bin >> $(BUILD_DIR)/$(BOOTLOADER_BIN)
	dd if=$(BUILD_DIR)/$(BOOTLOADER_DIR)/BootloaderLinked.bin >> $(BUILD_DIR)/$(BOOTLOADER_BIN)
	dd if=/dev/zero bs=512 count=100 >> $(BUILD_DIR)/$(BOOTLOADER_BIN)

$(KERNEL_BIN): $(KRNL_OBJS) $(KERNEL_DIR)/linker.ld
	$(LD) $(LDFLAGS) $(KRNL_OBJS_OUT) -o $(BUILD_DIR)/$(KERNEL_DIR)/KernelObject.o -Map=$(BUILD_DIR)/$(KERNEL_DIR)/KernelObject.map
	$(CC) -T $(KERNEL_DIR)/linker.ld -o $(BUILD_DIR)/$(KERNEL_DIR)/KernelLinked.elf $(CPPFLAGS) $(BUILD_DIR)/$(KERNEL_DIR)/KernelObject.o $(LIBS)

	rm -rf $(BUILD_DIR)/$(KERNEL_BIN)
	dd if=$(BUILD_DIR)/$(KERNEL_DIR)/KernelLinked.elf >> $(BUILD_DIR)/$(KERNEL_BIN)
	dd if=/dev/zero bs=512 count=100 >> $(BUILD_DIR)/$(KERNEL_BIN)

.cpp.o:
	@mkdir -p $(BUILD_DIR)/$(@D)
	$(CC) -c $< -o $(BUILD_DIR)/$@ -std=c++20 $(CPPFLAGS) $(INCLUDES)

%.asm.o: %.asm
	@mkdir -p $(BUILD_DIR)/$(@D)
	$(ASM) -f elf -g $< -o $(BUILD_DIR)/$@

clean:
	rm -f $(BUILD_DIR)/$(BOOTLOADER_BIN)
	rm -f $(BUILD_DIR)/$(KERNEL_BIN)
	rm -f $(BL_OBJS) *.o */*.o */*/*.o
	rm -f $(BL_OBJS:.o=.d) *.d */*.d */*/*.d
	rm -f $(BL_OBJS:.o=.bin) *.bin */*.bin */*/*.bin
	rm -f $(KRNL_OBJS) *.o */*.o */*/*.o
	rm -f $(KRNL_OBJS:.o=.d) *.d */*.d */*/*.d
	rm -f $(KRNL_OBJS:.o=.bin) *.bin */*.bin */*/*.bin
	rm -rf $(BUILD_DIR)

run:
	qemu-system-i386 -d int,cpu_reset -no-reboot -no-shutdown -hda $(BUILD_DIR)/$(BOOTLOADER_BIN) -hdb $(BUILD_DIR)/$(KERNEL_BIN)

-include $(BL_OBJS:.o=.d)
-include $(KRNL_OBJS:.o=.d)
