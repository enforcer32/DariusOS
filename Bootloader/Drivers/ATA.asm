section .text

global ATAReadLBA

ATAReadLBA: ; ATAReadLBA(uint32_t* dst, uint8_t drive, uint32_t sectorcount, uint32_t lba)
	push ebp
	mov ebp, esp

	; 8 = addr, 12 = drive, 16 = sectorcount, 20 = lba

	mov eax, [ebp+20] ; LBA Address
	mov ecx, [ebp+16] ; Sector Conter
	mov edi, [ebp+8] ; Memory Address

	; save lba
	mov ebx, eax
	
	; send highest 8-bits of lba to hard disk controller
	shr eax, 24
	or eax, [ebp+12] ; Select Driver
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

	pop ebp
	ret
