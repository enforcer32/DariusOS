ENTRY(_bootloader)
OUTPUT_FORMAT(binary)

SECTIONS 
{
	. = 0x000085D0; /* Load 2nd Stage Bootloader at 0x000085D0 */

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
		*(COMMON)
		*(.bss)
		*(.bss.*)
	}
}
