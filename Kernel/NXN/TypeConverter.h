#pragma once

#include <Kernel/NXN/Types.h>

namespace Kernel
{
	namespace NXN
	{
		namespace TypeConverter
		{
			int32_t IntToStr(int32_t num, char* buf, uint32_t len, uint32_t base);
			int32_t CharToInt(char ch);
		}
	}
}
