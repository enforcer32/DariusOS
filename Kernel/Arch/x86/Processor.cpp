#include <Kernel/Arch/x86/Processor.h>
#include <Kernel/NXN/KPrintf.h>
#include <Kernel/NXN/KPanic.h>
#include <Kernel/Arch/x86/GDT.h>

namespace Kernel
{
	namespace x86
	{
		namespace Processor
		{
			int32_t Init()
			{
				KPrintf("Initializing x86 Processor...\n");

				if (GDT::Init() != 0)
					KPanic("Failed To Initialize GDT\n");

				return 0;
			}
		}
	}
}
