#include <Kernel/Drivers/VGA.h>

namespace Kernel
{
	void InitKernel()
	{
		Drivers::VGA::Init();
		Drivers::VGA::ClearScreen();
		Drivers::VGA::WriteStr("DariusOS!\n");
		Drivers::VGA::WriteStr("32-bit Operating System!");
	}
}

extern "C" void KMain()
{
	Kernel::InitKernel();

	for(;;);
}
