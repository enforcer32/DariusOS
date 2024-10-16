#include <Kernel/Drivers/VGA.h>
#include <Kernel/NXN/CString.h>

#define VGA_VIDEO_ADDRESS 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_TEXT_ENCODE(ch, color) ((color << 8) | ch)

namespace Kernel
{
	namespace Drivers
	{
		namespace VGA
		{
			static uint16_t* s_VideoAddress = nullptr;
			static uint16_t s_Col = 0, s_Row = 0;
			static VGAColor s_Color = VGAColor::LightBrown;

			int32_t Init()
			{
				s_VideoAddress = (uint16_t*)VGA_VIDEO_ADDRESS;
				s_Col = 0;
				s_Row = 0;
				s_Color = VGAColor::LightBrown;
				return 0;
			}

			void ClearScreen()
			{
				for (uint16_t y = 0; y < VGA_HEIGHT; y++)
					for (uint16_t x = 0; x < VGA_WIDTH; x++)
						WriteCharLocation(x, y, ' ', s_Color);
				//SetCursor(0);
			}

			void WriteChar(uint8_t ch)
			{
				WriteCharColor(ch, s_Color);
			}

			void WriteCharColor(uint8_t ch, VGAColor color)
			{
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

				//SetCursor(VGA_GET_OFFSET(s_Col, s_Row));
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
		}
	}
}
