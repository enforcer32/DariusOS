section .text

global EnableInterrupts
global DisableInterrupts

EnableInterrupts:
	sti
	ret

DisableInterrupts:
	cli
	ret
