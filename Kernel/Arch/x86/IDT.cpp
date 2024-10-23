#include <Kernel/Arch/x86/IDT.h>
#include <Kernel/NXN/KPrintf.h>

namespace Kernel
{
	namespace x86
	{
		IDTRDesc IDT::s_IDTR;
		IDTDesc IDT::s_IDT[x86_IDT_TOTAL_INTERRUPTS]{};

		extern "C" void IDTLoad(IDTRDesc * idtr);

		int32_t IDT::Init()
		{
			KPrintf("Initializing IDT...\n");

			s_IDTR.Limit = sizeof(s_IDT) - 1;
			s_IDTR.Base = (uint32_t)s_IDT;
			
			IDTLoad(&s_IDTR);
			return 0;
		}

		void IDT::SetGate(uint32_t interrupt, uint32_t base, SegmentSelector selector, InterruptGateType gate, CPUPrivilegeLevel dpl)
		{
			s_IDT[interrupt].OffsetLow = (base & 0xFFFF);
			s_IDT[interrupt].Selector = static_cast<uint16_t>(selector);
			s_IDT[interrupt]._Reserved = 0;
			s_IDT[interrupt].Flags = ((1 << 7) | (static_cast<uint8_t>(dpl) << 5) | static_cast<uint8_t>(gate));
			s_IDT[interrupt].OffsetHigh = (base >> 16) & 0xFFFF;
		}
	}
}
