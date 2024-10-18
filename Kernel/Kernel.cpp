#include <Kernel/Drivers/VGA.h>
#include <Kernel/Kern/KPrintf.h>
#include <Kernel/Kern/KPanic.h>
#include <Kernel/CPU/GDT.h>
#include <Kernel/CPU/IDT.h>
#include <Kernel/CPU/PIC.h>
#include <Kernel/Interrupts/Interrupt.h>
#include <Kernel/Interrupts/IRQ.h>

namespace Kernel
{
	void SimpleIRQ(const Interrupts::InterruptFrame* frame)
	{
		KPrintf("Called IRQ: %d\n", frame->InterruptNumber - 32);
	}

	void InitKernel()
	{
		Drivers::VGA::Init();
		Drivers::VGA::ClearScreen();

		if (CPU::GDT::Init() != 0)
			KPanic("Failed To Initialize GDT\n");

		if (CPU::IDT::Init() != 0)
			KPanic("Failed to Initialize IDT\n");

		if (CPU::PIC::Init() != 0)
			KPanic("Failed to Initialize PIC\n");

		// SIMPLE IRQ - Map Keyboard IRQ to SimpleIRQ
		Interrupts::IRQInstallHandler(0, SimpleIRQ);

		Interrupts::EnableInterrupts();

		/*
		int y = 0;
		int x = 10 / y;
		(void)x;
		*/

		KPrintf("DariusOS!\n");
	}
}

extern "C" void KMain()
{
	Kernel::InitKernel();

	for(;;);
}
