
#include "put_font.h"

#if 0
	#define SCRN_X		1280
	#define SCRN_Y		1024
	char *vram = (char *)0xFD000000;
#else
	#define SCRN_X		320
	#define SCRN_Y		200
	char * const vram = (char *)0xA0000;
#endif

extern unsigned short font_bitmap_data[];


int puts(char *str)
{
	int i;
	static int x = 0;
	static int y = 0;

	for(i = 0; str[i] != '\0'; i++) {
		if(str[i] == '\n') {
			x = 0;
			y += 16;
		} else {
			print_font(x, y, str[i]);
			if(x < SCRN_X - 16) {
				x += 16;
			} else {
				x = 0;
				y += 16;
			}
		}
	}

	return 0;
}

int print_font(int init_x, int init_y, unsigned char ch)
{
	int i;
	unsigned short font_data;
	int x = 0, y = 0;

	x = init_x;
	y = init_y;

	for(i = 0; i < 16; i++) {
		font_data = font_bitmap_data[ch * 16 + i];

		if(font_data & 0x8000) put_pixel(x, y, 0x00, 0x00, 0x00);
		x++;
		if(font_data & 0x4000) put_pixel(x, y, 0x00, 0x00, 0x00);
		x++;
		if(font_data & 0x2000) put_pixel(x, y, 0x00, 0x00, 0x00);
		x++;
		if(font_data & 0x1000) put_pixel(x, y, 0x00, 0x00, 0x00);
		x++;
		if(font_data & 0x0800) put_pixel(x, y, 0x00, 0x00, 0x00);
		x++;
		if(font_data & 0x0400) put_pixel(x, y, 0x00, 0x00, 0x00);
		x++;
		if(font_data & 0x0200) put_pixel(x, y, 0x00, 0x00, 0x00);
		x++;
		if(font_data & 0x0100) put_pixel(x, y, 0x00, 0x00, 0x00);
		x++;
		if(font_data & 0x80) put_pixel(x, y, 0x00, 0x00, 0x00);
		x++;
		if(font_data & 0x40) put_pixel(x, y, 0x00, 0x00, 0x00);
		x++;
		if(font_data & 0x20) put_pixel(x, y, 0x00, 0x00, 0x00);
		x++;
		if(font_data & 0x10) put_pixel(x, y, 0x00, 0x00, 0x00);
		x++;
		if(font_data & 0x08) put_pixel(x, y, 0x00, 0x00, 0x00);
		x++;
		if(font_data & 0x04) put_pixel(x, y, 0x00, 0x00, 0x00);
		x++;
		if(font_data & 0x02) put_pixel(x, y, 0x00, 0x00, 0x00);
		x++;
		if(font_data & 0x01) put_pixel(x, y, 0x00, 0x00, 0x00);
		x++;

		y++;
		x = init_x;
	}

	return 0;
}

int put_pixel(int x, int y,
	unsigned char r, unsigned char g, unsigned char b)
{
	vram[y * SCRN_X + x] = 0;

	return 0;
}
