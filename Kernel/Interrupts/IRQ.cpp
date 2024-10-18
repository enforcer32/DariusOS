#include <Kernel/Interrupts/IRQ.h>
#include <Kernel/CPU/IDT.h>
#include <Kernel/CPU/PIC.h>

namespace Kernel
{
	namespace Interrupts
	{
		/* IRQ FUNCTIONS */
		extern "C" void IRQ0();
		extern "C" void IRQ1();
		extern "C" void IRQ2();
		extern "C" void IRQ3();
		extern "C" void IRQ4();
		extern "C" void IRQ5();
		extern "C" void IRQ6();
		extern "C" void IRQ7();
		extern "C" void IRQ8();
		extern "C" void IRQ9();
		extern "C" void IRQ10();
		extern "C" void IRQ11();
		extern "C" void IRQ12();
		extern "C" void IRQ13();
		extern "C" void IRQ14();
		extern "C" void IRQ15();

		/* IRQ HANDLERS */
		void (*IRQRoutines[16])(const InterruptFrame* frame) {};

		void IRQInstall()
		{
			CPU::IDT::SetGate(32, (uint32_t)IRQ0, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(33, (uint32_t)IRQ1, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(34, (uint32_t)IRQ2, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(35, (uint32_t)IRQ3, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(36, (uint32_t)IRQ4, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(37, (uint32_t)IRQ5, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(38, (uint32_t)IRQ6, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(39, (uint32_t)IRQ7, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(40, (uint32_t)IRQ8, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(41, (uint32_t)IRQ9, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(42, (uint32_t)IRQ10, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(43, (uint32_t)IRQ11, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(44, (uint32_t)IRQ12, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(45, (uint32_t)IRQ13, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(46, (uint32_t)IRQ14, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(47, (uint32_t)IRQ15, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
		}

		void IRQInstallHandler(uint32_t irq, void (*handler)(const InterruptFrame* frame))
		{
			IRQRoutines[irq] = handler;
		}

		void IRQUninstallHandler(uint32_t irq)
		{
			IRQRoutines[irq] = 0;
		}

		extern "C" void IRQHandler(const InterruptFrame* frame)
		{
			void (*handler)(const InterruptFrame* frame);

			/* Handler CUSTOM IRQs */
			handler = IRQRoutines[frame->InterruptNumber - 32];
			if (handler && frame->InterruptNumber - 32 != 0)
				handler(frame);

			CPU::PIC::SendEOI(frame->InterruptNumber - 32);

			/* TIMER IRQ- PERFORM TASK SWITCH AFTER SENDING EOI TO INTERRUPT CONTROLLER */
			if (handler && frame->InterruptNumber - 32 == 0)
				handler(frame);
		}
	}
}
