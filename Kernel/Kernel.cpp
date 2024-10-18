#include <Kernel/Drivers/VGA.h>
#include <Kernel/Kern/KPrintf.h>
#include <Kernel/Kern/KPanic.h>
#include <Kernel/CPU/GDT.h>
#include <Kernel/CPU/IDT.h>
#include <Kernel/Interrupts/Interrupt.h>

namespace Kernel
{
	void InitKernel()
	{
		Drivers::VGA::Init();
		Drivers::VGA::ClearScreen();

		if (CPU::GDT::Init() != 0)
			KPanic("Failed To Initialize GDT\n");

		Interrupts::DisableInterrupts();

		if (CPU::IDT::Init() != 0)
			KPanic("Failed to Initialize IDT\n");

		//Interrupts::EnableInterrupts();

		//int y = 0;
		//int x = 10 / y;
		//(void)x;

		KPrintf("DariusOS!\n");
	}
}

extern "C" void KMain()
{
	Kernel::InitKernel();

	for(;;);
}
