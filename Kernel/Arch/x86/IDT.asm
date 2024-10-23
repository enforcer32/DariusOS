section .text

global IDTLoad

IDTLoad:
	push ebp
	mov ebp, esp
	mov ebx, [ebp+8]
	lidt[ebx]
	pop ebp
	ret
