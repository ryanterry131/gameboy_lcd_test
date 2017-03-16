#include <stdlib.h>
#include "MiniFB.h"

static const int WIDTH = 160;
static const int HEIGHT = 144;
static const int PADDING = 30;
static const int WINDOW_WIDTH = WIDTH + PADDING;
static const int WINDOW_HEIGHT = HEIGHT + PADDING;

typedef uint32_t color_t;
// The greenish GameBoy color palette
static const color_t LCD_WHITE = MFB_RGB(0x9B, 0xBC, 0x1B);
static const color_t LCD_LIGHT = MFB_RGB(0x8B, 0xAC, 0x17);
static const color_t LCD_DARK  = MFB_RGB(0x30, 0x62, 0x30);
static const color_t LCD_BLACK = MFB_RGB(0x16, 0x38, 0x0F);

static color_t lcd_buffer[WINDOW_WIDTH * WINDOW_HEIGHT];

#define SET(x, y, color)\
	lcd_buffer[x + (y * WINDOW_WIDTH) + (PADDING * WINDOW_WIDTH)] = color;


#include "test_screen.h"

void printttestscreen()
{
	for(int i = 0; i < sizeof(test_screen)/sizeof(int); i++)
	{
		int x = i % 160;
		int y = i / 160;
		uint32_t color = test_screen[i] == 0x00? LCD_WHITE : (test_screen[i] == 0x01)? LCD_LIGHT : (test_screen[i] == 0x02)? LCD_DARK : (test_screen[i] == 0x03)? LCD_BLACK : LCD_WHITE;
		SET(x, y, color);
	}
}

int main()
{
	if(mfb_open("GameBoy Test", WINDOW_WIDTH, WINDOW_HEIGHT) == 0)
	{
		return -1;
	}

	for(;;)
	{
		printttestscreen();

		if(mfb_update(lcd_buffer) == -1)
		{
			break;
		}
	}

	mfb_close();
	return 0;
}
