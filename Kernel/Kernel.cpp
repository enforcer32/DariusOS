#include <Kernel/Drivers/VGA.h>
#include <Kernel/Kern/KPrintf.h>
#include <Kernel/Kern/KPanic.h>
#include <Kernel/CPU/GDT.h>

namespace Kernel
{
	void InitKernel()
	{
		Drivers::VGA::Init();
		Drivers::VGA::ClearScreen();

		if (CPU::GDT::Init() != 0)
			KPanic("Failed To Initialize GDT\n");

		KPrintf("DariusOS!\n");
	}
}

extern "C" void KMain()
{
	Kernel::InitKernel();

	for(;;);
}
