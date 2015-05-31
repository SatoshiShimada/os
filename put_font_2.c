
#include "set_screen_mode.h"

extern SCREEN_INFO screen;
extern unsigned short font_data[];

int put16(int columns, int rows, char c)
{
	unsigned int *vram = (unsigned int *)screen.vram;
	int x, y;
	int i = c * 16;

	for(y = 0; y < 16; y++) {
		for(x = 0; x < 16; x++) {
			if((font_data[i + y] & (0x01 << (15 - x))) != 0) {
				vram[(y + rows) * screen.x + (x + columns)] = 0xffffffff;
			} else {
				vram[(y + rows) * screen.x + (x + columns)] = 0xff000000;
			}
		}
	}

	return 0;
}
