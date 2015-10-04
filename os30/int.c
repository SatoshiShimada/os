#include "keycode.h"

// for PS/2 Keyboard
void inthandler21(int keycode)
{
	key_encoder((unsigned int)keycode);
	return;
}

// for PS/2 Mouse
void inthandler2c(void)
{
	return;
}
