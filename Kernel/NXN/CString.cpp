#include <Kernel/NXN/CString.h>

namespace Kernel
{
	namespace NXN
	{
		size_t Strlen(const char* str)
		{
			size_t len = 0;
			while (str[len++]);
			return len;
		}

		void* Memset(void* dst, int32_t ch, size_t num)
		{
			uint8_t* p1 = (uint8_t*)dst;
			while (num--)
				*p1++ = ch;
			return dst;
		}

		void* Memsetw(void* dst, uint16_t ch, size_t num)
		{
			uint16_t* p1 = (uint16_t*)dst;
			while (num--)
				*p1++ = ch;
			return dst;
		}

		void* Memcpy(void* dst, const void* src, size_t num)
		{
			uint8_t* p1 = (uint8_t*)dst;
			const uint8_t* p2 = (uint8_t*)src;
			while (num--)
				*p1++ = *p2++;
			return dst;
		}

		int32_t Memcmp(const void* src1, const void* src2, size_t num)
		{
			const uint8_t* p1 = (uint8_t*)src1;
			const uint8_t* p2 = (uint8_t*)src2;
			for (size_t i = 0; i < num; i++, p1++, p2++) {
				if (*p1 < *p2)
					return -1;
				else if (*p1 > *p2)
					return 1;
			}
			return 0;
		}
	}
}
