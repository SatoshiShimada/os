
#include "asm_func.h"
#include "set_screen_mode.h"

extern SCREEN_INFO screen;

int set_vga0reg(int reg, int data)
{
	out_word(0x01CE, reg);
	out_word(0x01CF, data);

	return 0;
}

/*
 * VGA mode change
 * x: x pixel(320, 640, 800, 1024)
 * y: x pixel(200, 240, 400, 480, 600, 768)
 * c: bit colors(4, 8, 15, 16, 24, 32)
 * flag:
 *  bit0: setting enable
 *  bit1: 
 *  bit2: 
 *  bit3: 
 *  bit4: 
 *  bit5: 
 *  bit6: linner access mode
 *  bit7: vram clear(all black)
 */
int init_vga0(int x, int y, int c, int flag)
{
	set_vga0reg(0x0004, 0x0000);
	set_vga0reg(0x0001, x);
	set_vga0reg(0x0002, y);
	set_vga0reg(0x0003, c);
	set_vga0reg(0x0005, 0x0000);
	set_vga0reg(0x0004, flag);

	screen.x = x;
	screen.y = y;
	screen.mode = c;
	if((flag & 0x40) == 0)
		screen.vram = (char *)0x000a0000;
	else
		screen.vram = (char *)0xe0000000;

	return 0;
}
