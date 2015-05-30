
#include "set_screen_mode.h"
//#include "font_data.h"

extern SCREEN_INFO screen;
extern unsigned short *font_data;

int put16(char c)
{
	unsigned int *vram = (unsigned int *)screen.vram;
	int x, y;
	int i = c * 16;

	vram = (unsigned int *)0xfd000000;

	for(x = 0; x < 100; x++)
		*(vram + x) = 0xffffffff;

	i = 0;
	for(y = 0; y < 16; y++) {
		for(x = 0; x < 16; x++) {
			if(font_data[i] & (0x01 << (15 - i))) {
				vram[y * screen.x + x] = 0xffffffff;
				*(vram + y * screen.x + x) = 0xffffffff;
			}
		}
		i++;
	}

	return 0;
}
