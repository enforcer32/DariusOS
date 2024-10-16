#pragma once

#include <Kernel/NXN/Types.h>

namespace Kernel
{
	namespace Drivers
	{
		namespace VGA
		{
			enum class VGAColor : uint8_t
			{
				Black = 0,
				Blue = 1,
				Green = 2,
				Cyan = 3,
				Red = 4,
				Magenta = 5,
				Brown = 6,
				LightGrey = 7,
				DarkGrey = 8,
				LightBlue = 9,
				LightGreen = 10,
				LightCyan = 11,
				LightRed = 12,
				LightMagenta = 13,
				LightBrown = 14,
				White = 15
			};

			int32_t Init();
			void ClearScreen();
			void WriteChar(uint8_t ch);
			void WriteCharColor(uint8_t ch, VGAColor color);
			void WriteCharLocation(uint16_t col, uint16_t row, uint8_t ch, VGAColor color);
			void WriteStr(const char* str);
			VGAColor GetColor();
			void SetColor(VGAColor color);
			void ScrollDown();

			void EnableCursor();
			void DisableCursor();
			void SetCursor(uint16_t offset);
			uint16_t GetCursor();
		}
	}
}
