#include "keycode.h"
#include "fifo.h"
#include "asm_func.h"

#define PIC0_OCW2    0x0020
#define PIC1_OCW2    0x00a0

extern struct FIFO8 *fifo;

// for PS/2 Keyboard
void inthandler21(int keycode)
{
	key_encoder((unsigned int)keycode);
	return;
}

// for PS/2 Mouse
void inthandler2c(int data)
{
	fifo8_put(fifo, (unsigned char)data);
	out_byte(PIC1_OCW2, 0x64);
	out_byte(PIC0_OCW2, 0x62);
	return;
}
