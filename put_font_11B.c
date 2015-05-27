
#define SCRN_X		1280
#define SCRN_Y		1024

int put_pixel(int x, int y, unsigned char r, unsigned char g, unsigned char b);

char *vram = (char *)0xFD000000;

int init_screen_(void)
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

unsigned char font_A[] = {
	0x00, 0x00,
	0x01, 0x80,
	0x03, 0xc0,
	0x02, 0x40,
	0x06, 0x60,
	0x0c, 0x30,
	0x0c, 0x30,
	0x18, 0x18,
	0x18, 0x18,
	0x1f, 0xf8,
	0x3f, 0xfc,
	0x30, 0x0c,
	0x30, 0x0c,
	0x30, 0x0c,
	0x30, 0x0c,
	0x00, 0x00,
};

//int print_font(char *vram, char font)
int print_font(int init_x, int init_y)
{
	int i;
	unsigned char font_data;
	int x = 0, y = 0;

	x = init_x;
	y = init_y;

	for(i = 0; i < 16 * 2; i++) {
		font_data = font_A[i];

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

		if(i % 2 == 1) {
			y++;
			x = init_x;
		}
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
