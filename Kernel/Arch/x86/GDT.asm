section .text

global GDTLoad

GDTLoad:
	push ebp
	mov ebp, esp
	mov ebx, [ebp+8]
	lgdt[ebx]
	pop ebp
	ret
