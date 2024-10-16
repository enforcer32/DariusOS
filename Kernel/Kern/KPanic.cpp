#include <Kernel/Kern/KPanic.h>
#include <Kernel/Kern/KPrintf.h>

namespace Kernel
{
	void KPanic(const char* str)
	{
		KPrintf(str);
		while (true);
	}
}
