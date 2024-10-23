#include <Kernel/Arch/x86/GDT.h>
#include <Kernel/NXN/KPrintf.h>

namespace Kernel
{
	namespace x86
	{
		GDTRDesc GDT::s_GDTR;
		GDTDesc GDT::s_GDT[GDT_TOTAL_SEGMENTS]{};

		extern "C" void GDTLoad(GDTRDesc * gdtr);

		int32_t GDT::Init()
		{
			KPrintf("Initializing GDT...\n");

			// GDTR SETUP
			s_GDTR.Limit = sizeof(s_GDT) - 1;
			s_GDTR.Base = (uint32_t)s_GDT;

			// NULL DESCRIPTOR
			SetGate(0, 0, 0, 0, 0);

			/* KERNEL Code and Data Descriptor
			* Base Address 0
			* Limit is 4gb
			* 4kb gran
			* 32bit opcodes
			* Selector 0x08 will be our code segment offset
			* Selector 0x10 will be our data segment offset
			*/
			SetGate(1, 0, 0xffffffff, 0x9a, 0xcf); // Kernel Code Segment
			SetGate(2, 0, 0xffffffff, 0x92, 0xcf); // Kernel Data Segment

			/* USER Code and Data Descriptor
			* Base Address 0
			* Limit is 4gb
			* 4kb gran
			* 32bit opcodes
			* Selector 0x18 will be our code segment offset
			* Selector 0x20 will be our data segment offset
			*/
			SetGate(3, 0, 0xffffffff, 0xf8, 0xcf); // User Code Segment
			SetGate(4, 0, 0xffffffff, 0xf2, 0xcf); // User Data Segment

			// NO TSS?

			GDTLoad(&s_GDTR);
			return 0;
		}

		void GDT::SetGate(uint32_t seg, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
		{
			/* Setup Base */
			s_GDT[seg].BaseLow = (base & 0xffff); // 16bit
			s_GDT[seg].BaseMid = (base >> 16) & 0xff; // 24bits of base
			s_GDT[seg].BaseHigh = (base >> 24) & 0xff; // 32bits of base (16 + 8 + 8 = 32bits);

			/* Setup Segment Limits */
			s_GDT[seg].LimitLow = (limit & 0x0000ffff); // 16bits of limit
			s_GDT[seg].Granularity = ((limit >> 16) & 0x0F); // 4bits of limit (16 + 4 = 20bits MAX SIZE)

			/* Setup granularity */
			s_GDT[seg].Granularity |= (gran & 0xF0); // Toggle first two bits of flags. (b1 = Granularity, b2=32bit pm segment, b3,4=AVL)
			s_GDT[seg].Access = access; // Present, Privilege, Type Flags
		}
	}
}
