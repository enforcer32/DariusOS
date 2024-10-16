#include <Kernel/Drivers/VGA.h>
#include <Kernel/CPU/Port.h>
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
	namespace Drivers
	{
		namespace VGA
		{
			static uint16_t* s_VideoAddress = nullptr;
			static uint16_t s_Col = 0, s_Row = 0;
			static VGAColor s_Color = VGAColor::LightBrown;

			static int16_t CTRL_ADDRESS_REG = 0x3D4;
			static int16_t CTRL_DATA_REG = 0x3D5;

			int32_t Init()
			{
				s_VideoAddress = (uint16_t*)VGA_VIDEO_ADDRESS;
				s_Col = 0;
				s_Row = 0;
				s_Color = VGAColor::LightBrown;


				// SETUP REGISTERS
				uint8_t IOAS = ((CPU::Port::INSB(EXT_MISC_OUT_READ_REG) >> 0) & 1);
				if(!IOAS)
				{
					CTRL_ADDRESS_REG = 0x3B4;
					CTRL_DATA_REG = 0x3B5;
				}

				DisableCursor();
				EnableCursor();

				return 0;
			}

			void ClearScreen()
			{
				for (uint16_t y = 0; y < VGA_HEIGHT; y++)
					for (uint16_t x = 0; x < VGA_WIDTH; x++)
						WriteCharLocation(x, y, ' ', s_Color);
				SetCursor(0);
			}

			void WriteChar(uint8_t ch)
			{
				WriteCharColor(ch, s_Color);
			}

			void WriteCharColor(uint8_t ch, VGAColor color)
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

			void WriteCharLocation(uint16_t col, uint16_t row, uint8_t ch, VGAColor color)
			{
				s_VideoAddress[(row * VGA_WIDTH) + col] = VGA_TEXT_ENCODE(ch, (uint8_t)color);
			}

			void WriteStr(const char* str)
			{
				for (size_t i = 0; i < NXN::Strlen(str); i++)
					WriteChar(str[i]);
			}

			VGAColor GetColor()
			{
				return s_Color;
			}

			void SetColor(VGAColor color)
			{
				s_Color = color;
			}
			
			void ScrollDown()
			{
				uint8_t* start = (uint8_t*)s_VideoAddress + VGA_WIDTH * 2;
				size_t size = s_Row * VGA_WIDTH * 2;
				NXN::Memcpy(s_VideoAddress, start, size);
				start = (uint8_t*)s_VideoAddress + size;
				NXN::Memsetw(start, VGA_TEXT_ENCODE(' ', (uint8_t)VGAColor::Black), size);
				s_Row--;
			}

			void EnableCursor()
			{
				uint8_t addrRegBak = CPU::Port::INSB(CTRL_ADDRESS_REG);
				CPU::Port::OUTB(CTRL_ADDRESS_REG, CTRL_CURSOR_START_REG);
				uint8_t cursorStartRegData = CPU::Port::INSB(CTRL_DATA_REG);
				CLEAR_BIT(cursorStartRegData, 5);
				CPU::Port::OUTB(CTRL_DATA_REG, cursorStartRegData);
				CPU::Port::OUTB(CTRL_ADDRESS_REG, addrRegBak);
			}

			void DisableCursor()
			{
				uint8_t addrRegBak = CPU::Port::INSB(CTRL_ADDRESS_REG);
				CPU::Port::OUTB(CTRL_ADDRESS_REG, CTRL_CURSOR_START_REG);
				uint8_t cursorStartRegData = CPU::Port::INSB(CTRL_DATA_REG);
				SET_BIT(cursorStartRegData, 5);
				CPU::Port::OUTB(CTRL_DATA_REG, cursorStartRegData);
				CPU::Port::OUTB(CTRL_ADDRESS_REG, addrRegBak);
			}

			void SetCursor(uint16_t offset)
			{			
				// Low Bits
				uint8_t addrRegBak = CPU::Port::INSB(CTRL_ADDRESS_REG);
				CPU::Port::OUTB(CTRL_ADDRESS_REG, CTRL_CURSOR_LOCATION_LOW_REG);
				CPU::Port::OUTB(CTRL_DATA_REG, (offset & 0xFF));
				// High Bits
				CPU::Port::OUTB(CTRL_ADDRESS_REG, CTRL_CURSOR_LOCATION_HIGH_REG);
				CPU::Port::OUTB(CTRL_DATA_REG, ((offset >> 8) & 0xFF));
				CPU::Port::OUTB(CTRL_ADDRESS_REG, addrRegBak);
			}
			uint16_t GetCursor()
			{
				uint16_t offset = 0;
				// Low Bits
				uint8_t addrRegBak = CPU::Port::INSB(CTRL_ADDRESS_REG);
				CPU::Port::OUTB(CTRL_ADDRESS_REG, CTRL_CURSOR_LOCATION_LOW_REG);
				offset = CPU::Port::INSB(CTRL_DATA_REG);
				// High Bits
				CPU::Port::OUTB(CTRL_ADDRESS_REG, CTRL_CURSOR_LOCATION_HIGH_REG);
				offset |= (CPU::Port::INSB(CTRL_DATA_REG) << 8);
				CPU::Port::OUTB(CTRL_ADDRESS_REG, addrRegBak);
				return offset;
			}
		}
	}
}
