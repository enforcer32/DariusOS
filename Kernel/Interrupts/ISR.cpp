#include <Kernel/Interrupts/ISR.h>
#include <Kernel/CPU/IDT.h>
#include <Kernel/Interrupts/Interrupt.h>
#include <Kernel/Kern/KPanic.h>

namespace Kernel
{
	namespace Interrupts
	{
		/* ISRs reserved for CPU exceptions */
		extern "C" void ISR0();
		extern "C" void ISR1();
		extern "C" void ISR2();
		extern "C" void ISR3();
		extern "C" void ISR4();
		extern "C" void ISR5();
		extern "C" void ISR6();
		extern "C" void ISR7();
		extern "C" void ISR8();
		extern "C" void ISR9();
		extern "C" void ISR10();
		extern "C" void ISR11();
		extern "C" void ISR12();
		extern "C" void ISR13();
		extern "C" void ISR14();
		extern "C" void ISR15();
		extern "C" void ISR16();
		extern "C" void ISR17();
		extern "C" void ISR18();
		extern "C" void ISR19();
		extern "C" void ISR20();
		extern "C" void ISR21();
		extern "C" void ISR22();
		extern "C" void ISR23();
		extern "C" void ISR24();
		extern "C" void ISR25();
		extern "C" void ISR26();
		extern "C" void ISR27();
		extern "C" void ISR28();
		extern "C" void ISR29();
		extern "C" void ISR30();
		extern "C" void ISR31();

		// 32 Exception Messages
		const char* ExceptionMessages[] = { "Division By Zero",
									   "Debug",
									   "Non Maskable Interrupt",
									   "Breakpoint",
									   "Into Detected Overflow",
									   "Out of Bounds",
									   "Invalid Opcode",
									   "No Coprocessor",
									   "Double Fault",
									   "Coprocessor Segment Overrun",
									   "Bad TSS",
									   "Segment Not Present",
									   "Stack Fault",
									   "General Protection Fault",
									   "Page Fault",
									   "Unknown Interrupt",
									   "Coprocessor Fault",
									   "Alignment Check",
									   "Machine Check",
									   "Reserved",
									   "Reserved",
									   "Reserved",
									   "Reserved",
									   "Reserved",
									   "Reserved",
									   "Reserved",
									   "Reserved",
									   "Reserved",
									   "Reserved",
									   "Reserved",
									   "Reserved",
									   "Reserved" };


		void ISRInstall()
		{
			CPU::IDT::SetGate(0, (uint32_t)ISR0, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(1, (uint32_t)ISR1, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(2, (uint32_t)ISR2, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(3, (uint32_t)ISR3, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(4, (uint32_t)ISR4, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(5, (uint32_t)ISR5, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(6, (uint32_t)ISR6, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(7, (uint32_t)ISR7, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(8, (uint32_t)ISR8, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(9, (uint32_t)ISR9, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(10, (uint32_t)ISR10, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(11, (uint32_t)ISR11, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(12, (uint32_t)ISR12, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(13, (uint32_t)ISR13, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(14, (uint32_t)ISR14, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(15, (uint32_t)ISR15, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(16, (uint32_t)ISR16, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(17, (uint32_t)ISR17, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(18, (uint32_t)ISR18, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(19, (uint32_t)ISR19, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(20, (uint32_t)ISR20, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(21, (uint32_t)ISR21, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(22, (uint32_t)ISR22, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(23, (uint32_t)ISR23, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(24, (uint32_t)ISR24, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(25, (uint32_t)ISR25, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(26, (uint32_t)ISR26, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(27, (uint32_t)ISR27, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(28, (uint32_t)ISR28, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(29, (uint32_t)ISR29, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(30, (uint32_t)ISR30, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
			CPU::IDT::SetGate(31, (uint32_t)ISR31, CPU::SegmentSelector::KernelCode, CPU::InterruptGateType::InterruptGate32, CPU::CPUPrivilegeLevel::Ring0);
		}

		extern "C" void ISRFaultHandler(const InterruptFrame* frame)
		{
			if (frame->InterruptNumber < 32)
				KPanic(ExceptionMessages[frame->InterruptNumber]);
		}
	}
}
