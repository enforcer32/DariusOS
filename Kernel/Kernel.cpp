#include <Bootloader/BootInfo.h>
#include <Kernel/Drivers/Graphics/VGA.h>
#include <Kernel/NXN/KPrintf.h>
#include <Kernel/NXN/KPanic.h>

namespace Kernel
{
	void InitKernel()
	{
		Graphics::VGA::Init();
		Graphics::VGA::ClearScreen();

		KPrintf("Darius Operating System\n");
		KPanic("Panic!!!!!");
	}
}

extern "C" void KMain(const BootInfo* bootInfo)
{
	Kernel::InitKernel();
	for(;;);
}
