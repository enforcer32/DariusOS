#include <Kernel/Kern/KPrintf.h>
#include <Kernel/Drivers/VGA.h>
#include <Kernel/NXN/TypeConverter.h>

namespace Kernel
{
	void KPrint(const char* str)
	{
		Drivers::VGA::WriteStr(str);
	}

	void KPrintChar(char ch)
	{
		Drivers::VGA::WriteChar(ch);
	}

	int32_t KPrintf(const char* fmt, ...)
	{
		va_list ap;
		const char* ptr;
		char* c;
		int32_t val;

		va_start(ap, fmt);
		for (ptr = fmt; *ptr; ptr++)
		{
			if (*ptr != '%')
			{
				KPrintChar(*ptr);
				continue;
			}

			switch (*++ptr)
			{
			case 'd':
			case 'u':
			case 'i':
			{
				val = va_arg(ap, int);
				char tmp[12];
				NXN::TypeConverter::IntToStr(val, tmp, sizeof(tmp), 10);
				KPrint(tmp);
				break;
			}
			case 'x':
			{
				val = va_arg(ap, int);
				char tmp[12];
				NXN::TypeConverter::IntToStr(val, tmp, sizeof(tmp), 16);
				KPrint(tmp);
				break;
			}
			case 'c':
			{
				char ch = va_arg(ap, int);
				KPrintChar(ch);
				break;
			}
			case 's':
			{
				c = va_arg(ap, char*);
				KPrint(c);
				break;
			}
			default:
				KPrintChar(*ptr);
				break;
			}
		}
		va_end(ap);

		return 0;
	}
}
