
void boxfill8(unsigned char *vram, int xsize, unsigned char c,
	int x0, int y0, int x1, int y1)
{
	int x, y;

	for(y = y0; y <= y1; y++) {
		for(x = x0; x <= x1; x++) {
			vram[y * xsize + x] = c;
		}
	}
	return;
}
