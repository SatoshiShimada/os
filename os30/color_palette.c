
#include "asm_func.h"

void init_palette(void);
void set_palette(int start, int end, unsigned char *rgb);

void init_palette(void)
{
	static unsigned char table_rgb[16 * 3] = {
		0x00, 0x00, 0x00, /* Black */
		0xff, 0x00, 0x00, /* Red */
		0x00, 0xff, 0x00, /* Green */
		0xff, 0xff, 0x00, /* Yellow */
		0x00, 0x00, 0xff, /* Blue */
		0xff, 0x00, 0xff, /* Parple */
		0x00, 0xff, 0xff, /* Cyan */
		0xff, 0xff, 0xff, /* White */
		0xc6, 0xc6, 0xc6, /* Gray */
		0x84, 0x00, 0x00, /* Dark Red */
		0x00, 0x84, 0x00, /* Dark Green */
		0x84, 0x84, 0x00, /* Dark Yellow */
		0x00, 0x00, 0x84, /* Dark Blue */
		0x84, 0x00, 0x84, /* Dark Parple */
		0x00, 0x84, 0x84, /* Dark Cyan */
		0x84, 0x84, 0x84  /* Dark Gray */
	};
	set_palette(0, 15, table_rgb);
	
	return;
}

void set_palette(int start, int end, unsigned char *rgb)
{
	int i;
	int eflags;

	eflags = load_eflags();
	cli();
	out_byte(0x03c8, start);
	for(i = start; i <= end; i++) {
		out_byte(0x03c9, rgb[0] / 4);
		out_byte(0x03c9, rgb[1] / 4);
		out_byte(0x03c9, rgb[2] / 4);
		rgb += 3;
	}
	store_eflags(eflags);

	return;
}

