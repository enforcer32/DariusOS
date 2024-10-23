section .text

global INSB
global OUTB
global INSW
global OUTW
global INSD
global OUTD

INSB:
	push ebp
	mov ebp, esp
	xor eax, eax
	mov edx, [ebp+8]
	in al, dx
	pop ebp
	ret

OUTB:
	push ebp
	mov ebp, esp
	mov eax, [ebp+12]
	mov edx, [ebp+8]
	out dx, al
	pop ebp
	ret

INSW:
	push ebp
	mov ebp, esp
	xor eax, eax
	mov edx, [ebp+8]
	in ax, dx
	pop ebp
	ret

OUTW:
	push ebp
	mov ebp, esp
	mov eax, [ebp+12]
	mov edx, [ebp+8]
	out dx, ax
	pop ebp
	ret

INSD:
	push ebp
	mov ebp, esp
	xor eax, eax
	mov edx, [ebp+8]
	in eax, dx
	pop ebp
	ret

OUTD:
	push ebp
	mov ebp, esp
	xor eax, eax
	mov eax, [ebp+12]
	mov edx, [ebp+8]
	out dx, eax
	pop ebp
	ret
