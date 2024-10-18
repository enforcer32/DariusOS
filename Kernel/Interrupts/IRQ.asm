section .text

extern IRQHandler

global IRQ0
global IRQ1
global IRQ2
global IRQ3
global IRQ4
global IRQ5
global IRQ6
global IRQ7
global IRQ8
global IRQ9
global IRQ10
global IRQ11
global IRQ12
global IRQ13
global IRQ14
global IRQ15

_IRQHandler:
	; Save CPU state
	pushad

	; Save the data segment descriptor
	mov ax, ds
	push eax

	; Load the kernel data segment descriptor
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	push esp
	cld
	call IRQHandler
	pop eax

	; Restore Data segment descriptor
	pop eax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	popad
	add esp, 8 ; Cleanup pushed error code and pushed IRQ No
	iret

; IRQ HANDLERS
IRQ0:
	push byte 0
	push byte 32
	jmp _IRQHandler

IRQ1:
	push byte 0
	push byte 33
	jmp _IRQHandler

IRQ2:
	push byte 0
	push byte 34
	jmp _IRQHandler

IRQ3:
	push byte 0
	push byte 35
	jmp _IRQHandler

IRQ4:
	push byte 0
	push byte 36
	jmp _IRQHandler

IRQ5:
	push byte 0
	push byte 37
	jmp _IRQHandler

IRQ6:
	push byte 0
	push byte 38
	jmp _IRQHandler
	
IRQ7:
	push byte 0
	push byte 39
	jmp _IRQHandler

IRQ8:
	push byte 0
	push byte 40
	jmp _IRQHandler

IRQ9:
	push byte 0
	push byte 41
	jmp _IRQHandler

IRQ10:
	push byte 0
	push byte 42
	jmp _IRQHandler

IRQ11:
	push byte 0
	push byte 43
	jmp _IRQHandler

IRQ12:
	push byte 0
	push byte 44
	jmp _IRQHandler

IRQ13:
	push byte 0
	push byte 45
	jmp _IRQHandler

IRQ14:
	push byte 0
	push byte 46
	jmp _IRQHandler

IRQ15:
	push byte 0
	push byte 47
	jmp _IRQHandler
