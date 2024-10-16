#include <Kernel/Drivers/VGA.h>
#include <Kernel/Kern/KPrintf.h>
#include <Kernel/Kern/KPanic.h>

namespace Kernel
{
	void InitKernel()
	{
		Drivers::VGA::Init();
		Drivers::VGA::ClearScreen();

		KPrintf("DariusOS!\n");
		KPanic("Panicing...");
		KPrintf("32-bit Operating System!");
	}
}

extern "C" void KMain()
{
	Kernel::InitKernel();

	for(;;);
}
