ENTRY(_kernelstart)
OUTPUT_FORMAT(binary)

SECTIONS 
{
	. = 1M; /* ORIGIN STARTS AT 1MB; Load Kernel at 1MB Memory (Address 1024 * 1024 = 0x00100000 ) */

	.text : ALIGN(4096)
	{
		*(.text)
		*(.text.*)
	}
 
	.rodata : ALIGN(4096)
	{
		*(.rodata)
		*(.rodata.*)
	}

	.data : ALIGN(4096)
	{
		*(.data)
		*(.data.*)
	}

	.bss : ALIGN(4096)
	{
		__bss_start = .;
		*(COMMON)
		*(.bss)
		*(.bss.*)
		__bss_end = .;
	}
}
