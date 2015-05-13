#include "put_font.h"


static int pos_x, pos_y;
static char is_initialize = 0;

int put_char(char c, int color, int bgcolor, int x, int y)
{
	char *font = (char *)0xb8000;

	font[(x + (X_CHAR_COUNT * y)) * 2] = c;
	font[(x + (X_CHAR_COUNT * y)) * 2 + 1] = color & 0xff;

	return c;
}

int puts_position(char *str, int x, int y)
{
	for(; *str != '\0'; str++) {
		put_char(*str, COLOR_WHITE, COLOR_BLACK, x, y);
		x++;
	}
	return 0;
}

int puts(char *str)
{
	int tabstop = 4;
	
	if(is_initialize) init_screen();
	
	for(; *str != '\0'; str++) {
		if(pos_x == X_CHAR_COUNT) {
			pos_x = 0;
			pos_y++;
		}
		if(pos_y == Y_CHAR_COUNT) {
			pos_x = 0;
			pos_y = 0;
		}

		switch(*str) {
		case '\n':
			pos_y++;
			pos_x = 0;
			break;
		case '\r':
			pos_x = 0;
			break;
		case '\t':
			pos_x += tabstop - (pos_x % tabstop);
			break;
		case '\b':
			put_char(' ', COLOR_WHITE, COLOR_BLACK, --pos_x, pos_y);
			break;
		default:
			goto do_put_char;
		}
		continue;

do_put_char:
		put_char(*str, COLOR_WHITE, COLOR_BLACK, pos_x, pos_y);
		pos_x++;
	}

	return 0;
}

int init_screen(void)
{
	static char f_init = 0;
	int x, y;

	if(f_init) return -1;
	f_init = 1;

	pos_x = 0; pos_y = 0;

	for(y = 0; y < Y_CHAR_COUNT; y++) {
		for(x = 0; x < X_CHAR_COUNT; x++) {
			put_char(' ', COLOR_BLACK, COLOR_BLACK, x, y);
		}
	}
	
	is_initialize = 1;
	return 0;
}
