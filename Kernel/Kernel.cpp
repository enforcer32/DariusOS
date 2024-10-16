#include <Kernel/Drivers/VGA.h>

namespace Kernel
{
	void InitKernel()
	{
		Drivers::VGA::Init();
		Drivers::VGA::ClearScreen();
		Drivers::VGA::WriteStr("DariusOS!\n");
	}
}

extern "C" void KMain()
{
	Kernel::InitKernel();

	for(;;);
}
