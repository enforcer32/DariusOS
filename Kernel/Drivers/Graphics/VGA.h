#pragma once

#include <Kernel/NXN/Types.h>

namespace Kernel
{
	namespace Graphics
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

		class VGA
		{
		public:
			static int32_t Init();
			static void Shutdown();

			static void ClearScreen();
			static void WriteChar(uint8_t ch);
			static void WriteCharColor(uint8_t ch, VGAColor color);
			static void WriteStr(const char* str);

			static VGAColor GetColor();
			static void SetColor(VGAColor color);

			static void EnableCursor();
			static void DisableCursor();
			static void SetCursor(uint16_t offset);
			static uint16_t GetCursor();

		private:
			static void WriteCharLocation(uint16_t col, uint16_t row, uint8_t ch, VGAColor color);
			static void ScrollDown();

		private:
			static uint16_t* s_VideoAddress;
			static uint16_t s_Col, s_Row;
			static VGAColor s_Color;
			static uint16_t s_CtrlAddressRegister;
			static uint16_t s_CtrlDataRegister;
		};
	}
}
