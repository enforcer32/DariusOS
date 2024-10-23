[ORG 0x7c00]
[BITS 16]

CODE_SEG equ gdt_code - gdt_start ; Selector 0x08 will be our code segment offset
DATA_SEG equ gdt_data - gdt_start ; Selector 0x10 will be our data segment offset

; BIOS PARAMETER BLOCK
_bpb:
	jmp short _pre
	nop
	times 33 db 0

_pre:
	jmp 0x0:_bootsector

_bootsector:
	; Clear interrupts
	cli
	
	; clear registers
	mov ax, 0x00
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov sp, 0x7c00

	; load gdt
	lgdt[gdt_descriptor]

	; set PE (PROTECTION ENABLED) bit in cr0
	mov eax, cr0
	or al, 1
	mov cr0, eax

	; Far jump to selector 8h (gdt 32-bit code segment offset)
	; Load 2nd Stage Bootloader
	jmp CODE_SEG:Bootloader

gdt_start:
	; offset 0x00
	gdt_null:
		dd 0
		dd 0

	; offset 0x08
	gdt_code:
		dw 0xffff ;16-bits of limit
		dw 0 ; 16-bits of base
		db 0 ; 8-bits of base
		db 10011010b ; 4-bit privilege + 4-bit type flags
		db 11001111b ; 4-bit other flags + 4 bits of limit
		db 0 ; 8 bits of base

	; offset 0x10
	gdt_data:
		dw 0xffff
		dw 0
		db 0
		db 10010010b
		db 11001111b
		db 0
gdt_end:

; GDT Pointer to base and limit
gdt_descriptor:
	dw gdt_end - gdt_start - 1 ; size
	dd gdt_start ; base

[BITS 32]
Bootloader:
	mov eax, 1 ; Load from Sector 1. (Sector 0 = Bootsector. LBA0 = Sector 0) (Sector 1 = 2nd Stage Bootloader. LBA0 = Sector 0) LBA1 = Bootloader, LBA3 = Kernel
	mov ecx, 100 ; Load 100 sector
	mov edi, 0x000085D0 ; Address we load them into. 0x000085D0
	call ATALBARead
	jmp CODE_SEG:0x000085D0

ATALBARead:
	mov ebx, eax ; save lba
	
	; send highest 8-bits of lba to hard disk controller
	shr eax, 24
	or eax, 0xE0 ; Select the master drive
	mov dx, 0x1F6 ; Port to send drive and bit 24 - 27 of LBA
	out dx, al

	; Send number of sectors to read
	mov eax, ecx
	mov dx, 0x1F2 ; Port to send number of sectors
	out dx, al

	; Send more bits
	mov eax, ebx ; restore lba
	mov dx, 0x1F3 ; Port to send bit 0 - 7 of LBA
	out dx, al

	mov eax, ebx ; restore lba
	mov dx, 0x1F4 ; Port to send bit 8 - 15 of LBA
	shr eax, 8 ; Get bit 8-15 in AL
	out dx, al

	mov eax, ebx ; restore lba
	mov dx, 0x1F5 ; Port to send bit 16 - 23 of LBA
	shr eax, 16 ; Get bit 16-23 in AL
	out dx, al

	mov edx, 0x1F7 ; command port
	mov al, 0x20 ; read with retry
	out dx, al

.NextSector:
	push ecx ; ecx is decremented at loop; 100 Sectors => 99 sectors => 98 sectors...

; check if its ready to read
.Retry:
	mov dx, 0x1F7 ; command port
	in al, dx
	test al, 8 ; the sector buffer requires servicing.
	jz .Retry ; until the sector buffer is ready.

	mov ecx, 256 ; Read 256 words = 1 sector
	mov dx, 0x1F0 ; Data port, in and out
	; read word from io/port specified in dx into memory location specified in es:(E)DI
	; Read a word from port and store it in 0x0100000
	; repeat 256 times - 1sector - uses ecx register
	rep insw
	pop ecx
	loop .NextSector
	ret

times 510-($-$$) db 0
dw 0xAA55
