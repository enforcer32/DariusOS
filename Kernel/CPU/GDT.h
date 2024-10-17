#pragma once

#include <Kernel/NXN/Types.h>

namespace Kernel
{
	namespace CPU
	{
		namespace GDT
		{
			struct GDTDesc
			{
				uint16_t LimitLow;
				uint16_t BaseLow;
				uint8_t BaseMid;
				uint8_t Access;
				uint8_t Granularity;
				uint8_t BaseHigh;
			} __attribute__((packed));

			struct GDTRDesc
			{
				uint16_t Limit;
				uint32_t Base;
			} __attribute__((packed));

			int32_t Init();
			void SetGate(uint32_t seg, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
			void Reload();
		}
	}
}
