#include <Kernel/NXN/KPanic.h>
#include <Kernel/NXN/KPrintf.h>

namespace Kernel
{
	void KPanic(const char* str)
	{
		KPrintf(str);
		while (true);
	}
}
