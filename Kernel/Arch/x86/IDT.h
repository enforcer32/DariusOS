#pragma once

#include <Kernel/Arch/x86/Processor.h>

namespace Kernel
{
	namespace x86
	{
		struct IDTDesc
		{
			uint16_t OffsetLow;
			uint16_t Selector;
			uint8_t _Reserved;
			uint8_t Flags;
			uint16_t OffsetHigh;
		} __attribute__((packed));

		struct IDTRDesc
		{
			uint16_t Limit;
			uint32_t Base;
		} __attribute__((packed));

		class IDT
		{
		public:
			static int32_t Init();
			static void SetGate(uint32_t interrupt, uint32_t base, SegmentSelector selector, InterruptGateType gate, CPUPrivilegeLevel dpl);

		private:
			static IDTRDesc s_IDTR;
			static IDTDesc s_IDT[x86_IDT_TOTAL_INTERRUPTS];
		};
	}
}
