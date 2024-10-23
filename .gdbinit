set architecture i386
set auto-load safe-path .
set disassembly-flavor intel

add-symbol-file ./Build/Bootloader/BootloaderObject.o 0x000085D0
add-symbol-file ./Build/Kernel/KernelObject.o 0x00100000
break Bootloader/BLMain.cpp:BLMain
break Kernel/Kernel.asm:_kernelstart
break Kernel/Kernel.cpp:KMain
target remote | qemu-system-i386 -hda ./Build/Bootloader.bin -hdb ./Build/Kernel.bin -S -gdb stdio

define hook-stop
print/x $eax
print/x $ebx
print/x $ecx
print/x $edx
print $eflags
x/xw $esp

disassemble $eip, +10

end
