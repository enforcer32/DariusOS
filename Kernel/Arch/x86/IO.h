#pragma once

#include <stdint.h>

namespace Kernel
{
	namespace x86
	{
		namespace IO
		{
			extern "C"
			{
				uint8_t INSB(uint16_t port);
				void OUTB(uint16_t port, uint8_t data);
				uint16_t INSW(uint16_t port);
				void OUTW(uint16_t port, uint16_t data);
				uint32_t INSD(uint32_t port);
				uint32_t OUTD(uint32_t port, uint32_t data);
			}
		}
	}
}
