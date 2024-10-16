set auto-load safe-path .
set disassembly-flavor intel

add-symbol-file ./Build/KernelObject.o 0x00100000
break Kernel.cpp:KMain
target remote | qemu-system-i386 -hda ./Build/DariusOS.bin -S -gdb stdio

define hook-stop
print/x $eax
print/x $ebx
print/x $ecx
print/x $edx
print $eflags
x/xw $esp

disassemble $eip, +10

end
