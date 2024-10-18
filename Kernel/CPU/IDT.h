#pragma once

#include <Kernel/CPU/CPU.h>

namespace Kernel
{
	namespace CPU
	{
		namespace IDT
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

			int32_t Init();
			void SetGate(uint32_t interrupt, uint32_t base, SegmentSelector selector, InterruptGateType gate, CPUPrivilegeLevel dpl);
		}
	}
}
