#include "keycode.h"

void inthandler21(int keycode)
{
	key_encoder((unsigned int)keycode);
	return;
}

void inthandler2c(void)
{
	return;
}
