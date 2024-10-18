#pragma once

#include <Kernel/Interrupts/Interrupt.h>

namespace Kernel
{
	namespace Interrupts
	{
		void IRQInstall();
		void IRQInstallHandler(uint32_t irq, void (*handler)(const InterruptFrame* frame));
		void IRQUninstallHandler(uint32_t irq);
	}
}
