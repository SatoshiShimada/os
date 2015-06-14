
#include "put_font.h"
#include "put_font_default.h"
#include "put_font_11B.h"

static int screen_mode = 1;


int init_screen(void)
{
	if(screen_mode == 0) {
		init_screen_default();
	} else {
		init_screen_11B();
	}
	return 0;
}

int puts(char *str)
{
	if(screen_mode == 0) {
		puts_default(str);
	} else {
		puts_11B(str);
	}
	return 0;
}

