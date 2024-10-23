#include <Bootloader/BootInfo.h>
#include <Kernel/Drivers/Graphics/VGA.h>
#include <Kernel/NXN/KPrintf.h>
#include <Kernel/NXN/KPanic.h>
#include <Kernel/Arch/x86/Processor.h>

namespace Kernel
{
	void InitKernel()
	{
		Graphics::VGA::Init();
		Graphics::VGA::ClearScreen();

		if(x86::Processor::Init() != 0)
			KPanic("Failed to Initialize x86 Processor!\n");

		int x = 0;
		int y = 10 / x;
		(void)y;

		KPrintf("Darius Operating System\n");
	}
}

extern "C" void KMain(const BootInfo* bootInfo)
{
	Kernel::InitKernel();
	for(;;);
}
