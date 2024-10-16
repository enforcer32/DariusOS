ENTRY(_start)
OUTPUT_FORMAT(binary)

SECTIONS 
{
	. = 1M; /* ORIGIN STARTS AT 1MB; We are required to load our kernel at 1MB Memory (Address 1024 * 1024 = 0x00100000 ) */

	.text : ALIGN(4096)
	{
		*(.text)
	}
 
	.rodata : ALIGN(4096)
	{
		*(.rodata)
	}

	.data : ALIGN(4096)
	{
		*(.data)
	}

	.bss : ALIGN(4096)
	{
		__bss_start = .;
		*(COMMON)
		*(.bss)
		__bss_end = .;
	}
}
