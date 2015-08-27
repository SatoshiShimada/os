
#include "put_font_11B.h"
#include "print.h"

#define SCRN_X		1280
#define SCRN_Y		1024

extern unsigned short font_bitmap_data[];

char *vram = (char *)0xFD000000;

int puts_11B(char *str)
{
	int i;
	int c;
	static int x = 0;
	static int y = 0;

	for(i = 0; str[i] != '\0'; i++) {
		if(str[i] == '\n') {
			x = 0;
			y += 16;
		} else {
			print_font_11B(x, y, str[i]);
			if(x < SCRN_X - 16) {
				x += 16;
			} else {
				x = 0;
				y += 16;
			}
		}
		if(y >= SCRN_Y - 16) {
			// scroll
			for(c = 0; c < (SCRN_Y / 16 - 1); c++) {
				memcpy(vram + (3 * SCRN_X * 16 * c), vram + (3 * SCRN_X * 16 * (c + 1)), 3 * 16 * SCRN_X);
			}
			y -= 16;
		}
	}

	return 0;
}

int init_screen_11B(void)
{
	int x, y;
	int i = 0;
	char color = 0xff;

	for(y = 0; y < SCRN_Y; y++) {
		for(x = 0; x < SCRN_X; x++) {
			/* Red, Green, Blue */
			vram[i++] = color;
			vram[i++] = color;
			vram[i++] = color;
		}
	}

	return 0;
}

int print_font_11B(int init_x, int init_y, unsigned char ch)
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
	vram[(y * SCRN_X * 3 + x * 3) + 0] = r;
	vram[(y * SCRN_X * 3 + x * 3) + 1] = g;
	vram[(y * SCRN_X * 3 + x * 3) + 2] = b;

	return 0;
}
