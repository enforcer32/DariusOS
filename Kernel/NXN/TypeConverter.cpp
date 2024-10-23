#include <Kernel/NXN/TypeConverter.h>
#include <Kernel/NXN/CString.h>

namespace Kernel
{
	namespace NXN
	{
		namespace TypeConverter
		{
			int32_t IntToStr(int32_t num, char* buf, uint32_t len, uint32_t base)
			{
				uint32_t i = 0;
				uint8_t neg = 0;

				if (len == 0)
					return -1;

				if (num == 0)
				{
					buf[i] = '0';
					buf[++i] = '\0';
					return 0;
				}

				if (num < 0 && base == 10)
				{
					neg = 1;
					num = -num;
				}

				while (num != 0 && i < len)
				{
					int rem = num % base;
					buf[i++] = (rem > 9) ? (rem - 10) + 'A' : rem + '0';
					num /= base;
				}

				if (neg)
					buf[i++] = '-';

				buf[i] = '\0';

				NXN::Strrev(buf, i);

				return 0;
			}

			int32_t CharToInt(char ch)
			{
				return ch - 48;
			}
		}
	}
}
