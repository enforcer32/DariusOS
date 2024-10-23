#pragma once

#include <stdint.h>

struct BootInfo
{
	uint32_t Signature;
	uint16_t Letter;
	uint32_t* KernelAddress;
};
