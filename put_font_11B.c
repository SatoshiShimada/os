
#define SCRN_X		1280
#define SCRN_Y		1024

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

int print_font(char *vram, char font)
{
	if(font_data & 0x01) vram[i] = color;
	if(font_data & 0x02) vram[i] = color;
	if(font_data & 0x04) vram[i] = color;
	if(font_data & 0x08) vram[i] = color;
	if(font_data & 0x10) vram[i] = color;
	if(font_data & 0x20) vram[i] = color;
	if(font_data & 0x40) vram[i] = color;
	if(font_data & 0x80) vram[i] = color;

	return 0;
}
