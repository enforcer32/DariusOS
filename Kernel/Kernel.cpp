#include <Bootloader/BootInfo.h>
#include <Kernel/Drivers/Graphics/VGA.h>

namespace Kernel
{
	void InitKernel()
	{
		Graphics::VGA::Init();
		Graphics::VGA::ClearScreen();

		Graphics::VGA::WriteStr("Darius Operating System");
	}
}

extern "C" void KMain(const BootInfo* bootInfo)
{
	Kernel::InitKernel();
	for(;;);
}
