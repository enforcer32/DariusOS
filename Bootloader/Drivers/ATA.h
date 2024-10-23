#pragma once

#include <stdint.h>

namespace Bootloader
{
	namespace Drivers
	{
		namespace ATA
		{
			enum class ATADrive : uint8_t
			{
				Master = 0xE0,
				Slave = 0xF0
			};

			extern "C" int32_t ATAReadLBA(uint32_t* dst, ATADrive drive, uint32_t sectorcount, uint32_t lba);
		}
	}
}
