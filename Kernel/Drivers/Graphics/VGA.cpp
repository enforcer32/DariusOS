#include <Kernel/Drivers/Graphics/VGA.h>
#include <Kernel/Arch/x86/IO.h>
#include <Kernel/NXN/CString.h>

#define VGA_VIDEO_ADDRESS 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_TEXT_ENCODE(ch, color) ((color << 8) | ch)
#define VGA_GET_TEXT_OFFSET(col, row) ((row * VGA_WIDTH) + col)

#define EXT_MISC_OUT_READ_REG 0x3CC
#define EXT_MISC_OUT_WRITE_REG 0x3C2
#define EXT_INPUT_STATUS_MONO_REG1 0x3BA
#define EXT_INPUT_STATUS_COLOR_REG1 0x3DA

#define CTRL_CURSOR_START_REG 0x0A
#define CTRL_CURSOR_END_REG 0x0B
#define CTRL_CURSOR_LOCATION_HIGH_REG 0x0E
#define CTRL_CURSOR_LOCATION_LOW_REG 0x0F

#define SET_BIT(num, n) (num |= (1 << n))
#define CLEAR_BIT(num, n) (num &= ~(1 << n))
#define TOGGLE_BIT(num, n) (num ^= (1 << n))
#define CHECK_BIT(num, n) ((num >> n) & 1)

namespace Kernel
{
	namespace Graphics
	{
		uint16_t* VGA::s_VideoAddress = nullptr;
		uint16_t VGA::s_Col = 0, VGA::s_Row = 0;
		VGAColor VGA::s_Color = VGAColor::LightBrown;
		uint16_t VGA::s_CtrlAddressRegister = 0x3D4;
		uint16_t VGA::s_CtrlDataRegister = 0x3D5;

		int32_t VGA::Init()
		{
			s_VideoAddress = (uint16_t*)VGA_VIDEO_ADDRESS;
			s_Col = 0;
			s_Row = 0;
			s_Color = VGAColor::LightBrown;

			// SETUP REGISTERS
			uint8_t IOAS = ((x86::IO::INSB(EXT_MISC_OUT_READ_REG) >> 0) & 1);
			if(!IOAS)
			{
				s_CtrlAddressRegister = 0x3B4;
				s_CtrlDataRegister = 0x3B5;
			}

			DisableCursor();
			EnableCursor();

			WriteStr("Initialized VGA...\n");
			return 0;
		}

		void VGA::Shutdown()
		{
			WriteStr("VGA Shutting Down....\n");
		}

		void VGA::ClearScreen()
		{
			for (uint16_t y = 0; y < VGA_HEIGHT; y++)
				for (uint16_t x = 0; x < VGA_WIDTH; x++)
					WriteCharLocation(x, y, ' ', s_Color);
			SetCursor(0);
		}

		void VGA::WriteChar(uint8_t ch)
		{
			WriteCharColor(ch, s_Color);
		}

		void VGA::WriteCharColor(uint8_t ch, VGAColor color)
		{
			if(ch == '\0')
				return;

			if (s_Row >= VGA_HEIGHT)
				ScrollDown();

			if (ch == '\n')
			{
				s_Col = 0;
				s_Row += 1;
				return;
			}

			WriteCharLocation(s_Col, s_Row, ch, color);
			s_Col += 1;

			if (s_Col >= VGA_WIDTH)
			{
				s_Col = 0;
				s_Row += 1;
			}

			SetCursor(VGA_GET_TEXT_OFFSET(s_Col, s_Row));
		}

		void VGA::WriteStr(const char* str)
		{
			for (uint32_t i = 0; i < NXN::Strlen(str); i++)
				WriteChar(str[i]);
		}

		VGAColor VGA::GetColor()
		{
			return s_Color;
		}

		void VGA::SetColor(VGAColor color)
		{
			s_Color = color;
		}

		void VGA::EnableCursor()
		{
			uint8_t addrRegBak = x86::IO::INSB(s_CtrlAddressRegister);
			x86::IO::OUTB(s_CtrlAddressRegister, CTRL_CURSOR_START_REG);
			uint8_t cursorStartRegData = x86::IO::INSB(s_CtrlDataRegister);
			CLEAR_BIT(cursorStartRegData, 5);
			x86::IO::OUTB(s_CtrlDataRegister, cursorStartRegData);
			x86::IO::OUTB(s_CtrlAddressRegister, addrRegBak);
		}

		void VGA::DisableCursor()
		{
			uint8_t addrRegBak = x86::IO::INSB(s_CtrlAddressRegister);
			x86::IO::OUTB(s_CtrlAddressRegister, CTRL_CURSOR_START_REG);
			uint8_t cursorStartRegData = x86::IO::INSB(s_CtrlDataRegister);
			SET_BIT(cursorStartRegData, 5);
			x86::IO::OUTB(s_CtrlDataRegister, cursorStartRegData);
			x86::IO::OUTB(s_CtrlAddressRegister, addrRegBak);
		}

		void VGA::SetCursor(uint16_t offset)
		{
			// Low Bits
			uint8_t addrRegBak = x86::IO::INSB(s_CtrlAddressRegister);
			x86::IO::OUTB(s_CtrlAddressRegister, CTRL_CURSOR_LOCATION_LOW_REG);
			x86::IO::OUTB(s_CtrlDataRegister, (offset & 0xFF));
			// High Bits
			x86::IO::OUTB(s_CtrlAddressRegister, CTRL_CURSOR_LOCATION_HIGH_REG);
			x86::IO::OUTB(s_CtrlDataRegister, ((offset >> 8) & 0xFF));
			x86::IO::OUTB(s_CtrlAddressRegister, addrRegBak);
		}

		uint16_t VGA::GetCursor()
		{
			uint16_t offset = 0;
			// Low Bits
			uint8_t addrRegBak = x86::IO::INSB(s_CtrlAddressRegister);
			x86::IO::OUTB(s_CtrlAddressRegister, CTRL_CURSOR_LOCATION_LOW_REG);
			offset = x86::IO::INSB(s_CtrlDataRegister);
			// High Bits
			x86::IO::OUTB(s_CtrlAddressRegister, CTRL_CURSOR_LOCATION_HIGH_REG);
			offset |= (x86::IO::INSB(s_CtrlDataRegister) << 8);
			x86::IO::OUTB(s_CtrlAddressRegister, addrRegBak);
			return offset;
		}

		void VGA::WriteCharLocation(uint16_t col, uint16_t row, uint8_t ch, VGAColor color)
		{
			s_VideoAddress[(row * VGA_WIDTH) + col] = VGA_TEXT_ENCODE(ch, (uint8_t)color);
		}

		void VGA::ScrollDown()
		{
			uint8_t* start = (uint8_t*)s_VideoAddress + VGA_WIDTH * 2;
			size_t size = s_Row * VGA_WIDTH * 2;
			NXN::Memcpy(s_VideoAddress, start, size);
			start = (uint8_t*)s_VideoAddress + size;
			NXN::Memsetw(start, VGA_TEXT_ENCODE(' ', (uint8_t)VGAColor::Black), size);
			s_Row--;
		}
	}
}
