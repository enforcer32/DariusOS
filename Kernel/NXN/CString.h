#pragma once

#include <Kernel/NXN/Types.h>

namespace Kernel
{
	namespace NXN
	{
		size_t Strlen(const char* str);
		void Strrev(char* str, size_t num);

		void* Memset(void* dst, int32_t ch, size_t num);
		void* Memsetw(void* dst, uint16_t ch, size_t num);
		void* Memcpy(void* dst, const void* src, size_t num);
		int32_t Memcmp(const void* src1, const void* src2, size_t num);
	}
}
