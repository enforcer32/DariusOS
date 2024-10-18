#pragma once

#include <Kernel/NXN/Types.h>

namespace Kernel
{
	namespace CPU
	{
		namespace PIC
		{
			int32_t Init();
			void Disable();
			int32_t Remap();
			void SendEOI(uint32_t irq);
		}
	}
}
