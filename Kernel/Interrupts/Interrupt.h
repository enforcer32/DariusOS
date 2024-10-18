#pragma once

#include <Kernel/NXN/Types.h>

namespace Kernel
{
	namespace Interrupts
	{
		extern "C" void EnableInterrupts();
		extern "C" void DisableInterrupts();

		struct InterruptFrame
		{
			uint32_t DS; // Data Segment Selector
			uint32_t EDI, ESI, EBP, IESP, EBX, EDX, ECX, EAX; // Pushed by pushad
			uint32_t InterruptNumber, ErrorCode; // Interrupt number and error code
			uint32_t EIP, CS, EFLAGS, ESP, SS; // Pushed by processor
		};
	}
}
