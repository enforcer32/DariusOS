#pragma once

#include <Kernel/NXN/Types.h>

namespace Kernel
{
	namespace CPU
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
	}
}
