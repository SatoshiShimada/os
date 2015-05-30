
typedef struct {
	char *vram;
	int x, y;
	int color_bit;
	/*
	 * screen mode
	 * 0: text
	 * 1: graphic
	 */
	int mode;
} SCREEN_INFO;

int set_vga0reg(int, int);
int init_vga0(int, int, int, int);
