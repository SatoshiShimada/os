#include "put_font.h"
#include "test_processor.h"
#include "asm_func.h"
#include "memory_test.h"
#include "print.h"
#include "idt.h"
#include "pic.h"
#include "keycode.h"
#include "./interrupt_device/interrupt.h"
#include "shell.h"
#include "memory.h"
#include "fat12.h"
#include "fdd2.h"

KEYCODE keycode;
unsigned int memory_total;

/*
 * called by asembler 
 * entry point
 */
int main(void)
{
	extern struct cpu_type cpu;
	unsigned int *counter = (unsigned int *)0x1000000;
	char keybuf;
	char buf[100];
	char console_buf[100];

	init_idt();
	init_pic();
	init_pit();
	/* init variavle */
	*counter = 0;
	set_keytable(KEY_EN1);
	keycode.len = 0;
	keycode.i_write = keycode.i_read = 0;

	//fdc0_init();
	//read_data_fdd(0, 0, 1, 1);

	sti();
	test_processor();
	memory_total = memory_test(cpu, 0x00400000, 0xffffffff);

	memory_control_init();
	memory_free(0x00001000, 0x0009e000);
	memory_free(0x00400000, memory_total - 0x00400000);

	init_screen();

	get_rootdir_file();

	/* Welcome message & print information */
	puts("Welcome to My OperatingSystem\n$ ");
	memset(console_buf, 0, sizeof(console_buf));

	for(;;) {
		hlt();
		itoa(buf, *counter / 100);
		puts_position(buf, X_CHAR_COUNT - 3, 0);

		keybuf = get_keycode_ascii();
		buf[0] = keybuf;
		buf[1] = '\0';
		puts(buf);
		if(keybuf == '\n') {
			do_command(console_buf);
			memset(console_buf, 0, sizeof(console_buf));
			puts("$ ");
		} else {
			strcat(console_buf, buf);
		}
	}

	return 0;
}

