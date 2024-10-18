#include <Kernel/CPU/PIC.h>
#include <Kernel/CPU/Port.h>
#include <Kernel/Kern/KPrintf.h>

#define PIC1 0x20 /* IO base address for master PIC */
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1 + 1)

#define PIC2 0xA0 /* IO base address for slave PIC */
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2 + 1)

#define PIC_EOI 0x20 /* End-of-interrupt command code */

#define ICW1_ICW4 0x01 /* ICW4 (not) needed */
#define ICW1_SINGLE 0x02 /* Single (cascade) mode */
#define ICW1_INTERVAL4 0x04 /* Call address interval 4 (8) */
#define ICW1_LEVEL 0x08 /* Level triggered (edge) mode */
#define ICW1_INIT 0x10 /* Initialization - required! */

#define ICW4_8086 0x01 /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO 0x02 /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE 0x08 /* Buffered mode/slave */
#define ICW4_BUF_MASTER 0x0C /* Buffered mode/master */
#define ICW4_SFNM 0x10 /* Special fully nested (not) */

/* MAP IRQ 0-15 TO IDT ENTRIES 32-47 */
#define PIC1_OFFSET 0x20
#define PIC2_OFFSET 0x28

namespace Kernel
{
	namespace CPU
	{
		namespace PIC
		{
			int32_t Init()
			{
				KPrintf("Initializing PIC...\n");
				return Remap();
			}

			/* IRQs 0 to 7 are mapped to reserved IDT entries 8 to 15 (PROBLEM). REMAP IRQ 0-15 TO IDT ENTRIES 32-47 */
			int32_t Remap()
			{
				KPrintf("Remapping PIC...\n");

				// Save Masks
				uint8_t a1, a2;
				a1 = Port::INSB(PIC1_DATA);
				a2 = Port::INSB(PIC2_DATA);

				// Setup Master PIC
				Port::OUTB(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4); // starts the initialization sequence (in cascade mode)
				Port::OUTB(PIC1_DATA, PIC1_OFFSET); // ICW2: Master PIC Vector Offset
				Port::OUTB(PIC1_DATA, 4); // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100) (TELL MASTER HE HAS A SLAVE)
				Port::OUTB(PIC1_DATA, ICW4_8086); // x86 MODE

				// Setup Slave PIC
				Port::OUTB(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
				Port::OUTB(PIC2_DATA, PIC2_OFFSET);
				Port::OUTB(PIC2_DATA, 2); // ICW3: tell Slave PIC its cascade identity (0000 0010)
				Port::OUTB(PIC2_DATA, ICW4_8086);

				// Restore Saved Masks
				Port::OUTB(PIC1_DATA, a1);
				Port::OUTB(PIC2_DATA, a2);
				return 0;
			}

			void Disable()
			{
				Port::OUTB(PIC1_DATA, 0xFF);
			}

			// Acknowledge Interrupt
			void SendEOI(uint32_t irq)
			{
				/* INT >= 8 (meaning IRQ8 - 15), then we need to send an EOI to the slave controller */
				if (irq >= 8)
					Port::OUTB(PIC2_COMMAND, PIC_EOI);
				/* In either case, send EOI to Master Interrupt Controller */
				Port::OUTB(PIC1_COMMAND, PIC_EOI);
			}
		}
	}
}
