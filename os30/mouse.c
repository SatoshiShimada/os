
#include "asm_func.h"

#define PORT_KEYDAT 0x0060
#define PORT_KEYSTA 0x0064
#define PORT_KEYCMD 0x0064
#define KEYSTA_SEND_NOTREADY 0x02
#define KEYCMD_WRITE_MODE 0x70
#define KBC_MODE 0x47

#define KEYCMD_SENDTO_MOUSE 0xd4
#define MOUSECMD_ENABLE 0xf4

void wait_KBC_sendready(void)
{
	/* wait at sendready of keyboard controller */
	for (;;) {
		if((in_byte(PORT_KEYSTA) & KEYSTA_SEND_NOTREADY) == 0) {
			break;
		}
	}
	return;
}

void init_keyboard(void)
{
	/* initilize keyboard controller */
	wait_KBC_sendready();
	out_byte(PORT_KEYCMD, KEYCMD_WRITE_MODE);
	wait_KBC_sendready();
	out_byte(PORT_KEYDAT, KBC_MODE);
	return;
}

void enable_mouse(void)
{
	/* mosue enable */
	wait_KBC_sendready();
	out_byte(PORT_KEYCMD, KEYCMD_SENDTO_MOUSE);
	wait_KBC_sendready();
	out_byte(PORT_KEYDAT, MOUSECMD_ENABLE);
	return;
}

