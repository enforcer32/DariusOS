#include <Bootloader/BootInfo.h>

#define VGA_TEXT_ENCODE(ch, color) ((color << 8) | ch)

namespace Kernel
{
	void InitKernel()
	{
		short* VGA = (short*)0xB8000;
		VGA[4] = VGA_TEXT_ENCODE('S', 2);
	}
}

extern "C" void KMain(const BootInfo* bootInfo)
{
	short* VGA = (short*)0xB8000;
	VGA[3] = VGA_TEXT_ENCODE(bootInfo->Letter, 2);
	Kernel::InitKernel();

	for(;;);
}
