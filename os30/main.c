#include "asm_func.h"
#include "screen.h"
#include "put_font.h"
#include "pic.h"
#include "dsc_tbl.h"
#include "keycode.h"

void init_palette(void);
void init_screen(void);
void boxfill8(unsigned char *, int, unsigned char, int, int, int, int);
void init_mouse_cursor8(char *, char);
void putblock8_8(char *, int, int, int, int, int, char *, int);

KEYCODE keycode;

int main(void) {
	char *vram = (char *)0xa0000;
	int scrnx = 320;
	int mx, my;
	char mcursor[256];
	char c;
	char buf[100];

	cli();
	init_gdtidt();
	init_pic();
	sti();
	init_palette();
	init_screen();
	set_keytable(KEY_EN1);

	init_mouse_cursor8(mcursor, COL8_008484);
	mx = 152; my = 72;
	putblock8_8(vram, scrnx, 16, 16, mx, my, mcursor, 16);
	puts("Welcome to OS");
	buf[1] = '\0';
	for(;;) {
		c = get_keycode_ascii();
		buf[0] = c;
		puts(buf);
		hlt();
	}
	for(;;) {
		hlt();
	}
	return 0;
}

void init_screen(void)
{
	unsigned char *vram = (unsigned char *)0xa0000;
	int xsize, ysize;

	xsize = 320;
	ysize = 200;

	boxfill8(vram, xsize, COL8_008484, 0, 0, xsize - 1, ysize - 29);
	boxfill8(vram, xsize, COL8_C6C6C6, 0, ysize - 28, xsize - 1, ysize - 28);
	boxfill8(vram, xsize, COL8_FFFFFF, 0, ysize - 27, xsize - 1, ysize - 27);
	boxfill8(vram, xsize, COL8_C6C6C6, 0, ysize - 26, xsize - 1, ysize -  1);

	boxfill8(vram, xsize, COL8_FFFFFF,  3, ysize - 24, 59, ysize - 24);
	boxfill8(vram, xsize, COL8_FFFFFF,  2, ysize - 24,  2, ysize -  4);
	boxfill8(vram, xsize, COL8_848484,  3, ysize -  4, 59, ysize -  4);
	boxfill8(vram, xsize, COL8_848484, 59, ysize - 23, 59, ysize -  5);
	boxfill8(vram, xsize, COL8_000000,  2, ysize -  3, 59, ysize -  3);
	boxfill8(vram, xsize, COL8_000000, 60, ysize - 24, 60, ysize -  3);

	boxfill8(vram, xsize, COL8_848484, xsize - 47, ysize - 24, xsize -  4, ysize - 24);
	boxfill8(vram, xsize, COL8_848484, xsize - 47, ysize - 23, xsize - 47, ysize -  4);
	boxfill8(vram, xsize, COL8_FFFFFF, xsize - 47, ysize -  3, xsize -  4, ysize -  3);
	boxfill8(vram, xsize, COL8_FFFFFF, xsize -  3, ysize - 24, xsize -  3, ysize -  3);

	return;
}

void init_mouse_cursor8(char *mouse, char bc)
{
	static char cursor[16][16] = {
		"**************..",
		"*OOOOOOOOOOO*...",
		"*OOOOOOOOOO*....",
		"*OOOOOOOOO*.....",
		"*OOOOOOOO*......",
		"*OOOOOOO*.......",
		"*OOOOOOO*.......",
		"*OOOOOOOO*......",
		"*OOOO**OOO*.....",
		"*OOO*..*OOO*....",
		"*OO*....*OOO*...",
		"*O*......*OOO*..",
		"**........*OOO*.",
		"*..........*OOO*",
		"............*OO*",
		".............***"
	};
	int x, y;

	for(y = 0; y < 16; y++) {
		for(x = 0; x < 16; x++) {
			if(cursor[y][x] == '*') {
				mouse[y * 16 + x] = COL8_000000;
			} else if(cursor[y][x] == 'O') {
				mouse[y * 16 + x] = COL8_FFFFFF;
			} else if(cursor[y][x] == '.') {
				mouse[y * 16 + x] = bc; // set backgroundcolor
			}
		}
	}
	return;
}

void putblock8_8(char *vram, int vxsize, int pxsize, int pysize, int px0, int py0, char *buf, int bxsize)
{
	int x, y;
	for(y = 0; y < pysize; y++) {
		for(x = 0; x < pxsize; x++) {
			vram[(py0 + y) * vxsize + (px0 + x)] = buf[y * bxsize + x];
		}
	}
	return;
}

