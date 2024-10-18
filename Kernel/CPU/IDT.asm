section .text

global IDTLoad
global EnableInterrupts
global DisableInterrupts

IDTLoad:
	push ebp
	mov ebp, esp
	mov ebx, [ebp+8]
	lidt[ebx]
	pop ebp
	ret

EnableInterrupts:
	sti
	ret

DisableInterrupts:
	cli
	ret
