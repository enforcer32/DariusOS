section .text

[BITS 32]

global _kernelstart

extern __bss_start
extern __bss_end
extern KMain

CODE_SEG equ 0x08 ; Selector 0x08 will be our code segment offset
DATA_SEG equ 0x10 ; Selector 0x10 will be our data segment offset

_kernelstart:

	; Save BootInfo Header
	mov ebx, [esp+4]

	; zero .bss section
	;mov edi, __bss_start
	;mov ecx, __bss_end
	;sub ecx, __bss_start
	;mov al, 0
	;rep stosb

	; set data segment
	mov eax, DATA_SEG
	mov ds, eax
	mov es, eax
	mov fs, eax
	mov gs, eax
	mov ss, eax
	mov ebp, 0x00200000
	mov esp, ebp

	; Kernel
	push ebx
	call KMain

	; Halt
	cli
.hang:
	hlt
	jmp .hang

times 512-($-$$) db 0
