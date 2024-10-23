section .text

extern x86ISRFaultHandler

global ISR0
global ISR1
global ISR2
global ISR3
global ISR4
global ISR5
global ISR6
global ISR7
global ISR8
global ISR9
global ISR10
global ISR11
global ISR12
global ISR13
global ISR14
global ISR15
global ISR16
global ISR17
global ISR18
global ISR19
global ISR20
global ISR21
global ISR22
global ISR23
global ISR24
global ISR25
global ISR26
global ISR27
global ISR28
global ISR29
global ISR30
global ISR31

_ISRHandler:
	; Save CPU State (Push EAX, ECX, EDX, EBX, original ESP, EBP, ESI, and EDI.)
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
	cld ; C code following the sysV ABI requires DF to be clear on function entry
	call x86ISRFaultHandler
	pop eax

	; Restore Data segment descriptor
	pop eax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	popad
	add esp, 8 ; Cleanup pushed error code and pushed ISR Number
	iret
	
; ISR HANDLERS
; 0: Divide By Zero Exception
ISR0:
    push byte 0
    push byte 0
    jmp _ISRHandler

; 1: Debug Exception
ISR1:
    push byte 0
    push byte 1
    jmp _ISRHandler

; 2: Non Maskable Interrupt Exception
ISR2:
    push byte 0
    push byte 2
    jmp _ISRHandler

; 3: Int 3 Exception
ISR3:
    push byte 0
    push byte 3
    jmp _ISRHandler

; 4: INTO Exception
ISR4:
    push byte 0
    push byte 4
    jmp _ISRHandler

; 5: Out of Bounds Exception
ISR5:
    push byte 0
    push byte 5
    jmp _ISRHandler

; 6: Invalid Opcode Exception
ISR6:
    push byte 0
    push byte 6
    jmp _ISRHandler

; 7: Coprocessor Not Available Exception
ISR7:
    push byte 0
    push byte 7
    jmp _ISRHandler

; 8: Double Fault Exception (With Error Code!)
ISR8:
	push byte 0
    push byte 8
    jmp _ISRHandler

; 9: Coprocessor Segment Overrun Exception
ISR9:
    push byte 0
    push byte 9
    jmp _ISRHandler

; 10: Bad TSS Exception (With Error Code!)
ISR10:
	push byte 0
    push byte 10
    jmp _ISRHandler

; 11: Segment Not Present Exception (With Error Code!)
ISR11:
	push byte 0
    push byte 11
    jmp _ISRHandler

; 12: Stack Fault Exception (With Error Code!)
ISR12:
	push byte 0
    push byte 12
    jmp _ISRHandler

; 13: General Protection Fault Exception (With Error Code!)
ISR13:
	push byte 0
    push byte 13
    jmp _ISRHandler

; 14: Page Fault Exception (With Error Code!)
ISR14:
	push byte 0
    push byte 14
    jmp _ISRHandler

; 15: Reserved Exception
ISR15:
    push byte 0
    push byte 15
    jmp _ISRHandler

; 16: Floating Point Exception
ISR16:
    push byte 0
    push byte 16
    jmp _ISRHandler

; 17: Alignment Check Exception
ISR17:
    push byte 0
    push byte 17
    jmp _ISRHandler

; 18: Machine Check Exception
ISR18:
    push byte 0
    push byte 18
    jmp _ISRHandler

; 19: Reserved
ISR19:
    push byte 0
    push byte 19
    jmp _ISRHandler

; 20: Reserved
ISR20:
    push byte 0
    push byte 20
    jmp _ISRHandler

; 21: Reserved
ISR21:
    push byte 0
    push byte 21
    jmp _ISRHandler

; 22: Reserved
ISR22:
    push byte 0
    push byte 22
    jmp _ISRHandler

; 23: Reserved
ISR23:
    push byte 0
    push byte 23
    jmp _ISRHandler

; 24: Reserved
ISR24:
    push byte 0
    push byte 24
    jmp _ISRHandler

; 25: Reserved
ISR25:
    push byte 0
    push byte 25
    jmp _ISRHandler

; 26: Reserved
ISR26:
    push byte 0
    push byte 26
    jmp _ISRHandler

; 27: Reserved
ISR27:
    push byte 0
    push byte 27
    jmp _ISRHandler

; 28: Reserved
ISR28:
    push byte 0
    push byte 28
    jmp _ISRHandler

; 29: Reserved
ISR29:
    push byte 0
    push byte 29
    jmp _ISRHandler

; 30: Reserved
ISR30:
    push byte 0
    push byte 30
    jmp _ISRHandler

; 31: Reserved
ISR31:
    push byte 0
    push byte 31
    jmp _ISRHandler
