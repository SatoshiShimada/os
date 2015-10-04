#include "asm_func.h"
#include "screen.h"
#include "put_font.h"
#include "pic.h"
#include "dsc_tbl.h"
#include "keycode.h"
#include "mouse.h"
#include "fifo.h"

void init_palette(void);
void init_screen(void);
void boxfill8(unsigned char *, int, unsigned char, int, int, int, int);
void init_mouse_cursor8(char *, char);
void putblock8_8(char *, int, int, int, int, int, char *, int);

KEYCODE keycode;
struct FIFO8 *fifo;

int main(void) {
	char *vram = (char *)0xa0000;
	int scrnx = 320;
	int scrny = 200;
	int mx, my;
	char mcursor[256];
	char c;
	char buf[100];
	unsigned char mouse_buf[100];
	unsigned char unc;
	struct FIFO8 mouse_fifo;
	struct MOUSE_DEC mdec;
	int i;

	fifo = &mouse_fifo;

	cli();
	init_gdtidt();
	init_pic();
	fifo8_init(fifo, sizeof(mouse_buf), mouse_buf);
	init_palette();
	init_screen();
	set_keytable(KEY_EN1);
	init_keyboard(); // for mouse
	enable_mouse(&mdec);
	sti();

	init_mouse_cursor8(mcursor, COL8_008484);
	mx = 152; my = 72;
	putblock8_8(vram, scrnx, 16, 16, mx, my, mcursor, 16);
	puts("Welcome to OS");
	buf[1] = '\0';
	for(;;) {
		cli();
		c = get_keycode_ascii();
		i = fifo8_get(fifo);
		if(c == 0 && i == -1) {
			sti_hlt();
		} else {
			sti();
			if(c != 0) {
				buf[0] = c;
				puts(buf);
			}
			if(unc != -1) {
				unc = (unsigned char)i;
				i = mouse_decode(&mdec, unc);
				if(i == 1) { /* mouse data 3 byte complete */
					boxfill8((unsigned char *)vram, scrnx, COL8_008484, mx, my, mx + 15, my + 15);
					mx += mdec.x;
					my += mdec.y;
					if(mx < 0) mx = 0;
					if(my < 0) my = 0;
					if(mx > scrnx - 16) mx = scrnx - 16;
					if(my > scrny - 16) my = scrny - 16;
					putblock8_8(vram, scrnx, 16, 16, mx, my, mcursor, 16);
				}
			}
		}
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

