#pragma once

#include <Kernel/NXN/Types.h>

#define x86_GDT_TOTAL_SEGMENTS 5
#define x86_IDT_TOTAL_INTERRUPTS 256

namespace Kernel
{
	namespace x86
	{
		enum class SegmentSelector : uint16_t
		{
			KernelCode = 0x08,
			KernelData = 0x10,
			UserCode = 0x18,
			UserData = 0x20,
		};

		enum class InterruptGateType : uint8_t
		{
			TaskGate = 0x05,
			InterruptGate16 = 0x06,
			TrapGate16 = 0x07,
			InterruptGate32 = 0x0E,
			TrapGate32 = 0x0F
		};

		enum class CPUPrivilegeLevel : uint8_t
		{
			Ring0 = 0x00, // High Privilege
			Ring1 = 0x01,
			Ring2 = 0x02,
			Ring3 = 0x03, // Low Privilege
		};

		struct InterruptFrame
		{
			uint32_t DS; // Data Segment Selector
			uint32_t EDI, ESI, EBP, IESP, EBX, EDX, ECX, EAX; // Pushed by pushad
			uint32_t InterruptNumber, ErrorCode; // Interrupt number and error code
			uint32_t EIP, CS, EFLAGS, ESP, SS; // Pushed by processor
		};
		
		namespace Processor
		{
			int32_t Init();
			extern "C" void EnableInterrupts();
			extern "C" void DisableInterrupts();
		}
	}
}
