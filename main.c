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
	int i;
	char buf[100];
	char cmd_buf[100];

	init_idt();
	init_pic();
	init_pit();
	/* init variavle */
	*counter = 0;
	set_keytable(KEY_EN1);
	keycode.len = 0;
	keycode.i_write = keycode.i_read = 0;

	sti();
	test_processor();
	memory_total = memory_test(cpu, 0x00400000, 0xffffffff);

	memory_control_init();
	memory_free(0x00001000, 0x0009e000);
	memory_free(0x00400000, memory_total - 0x00400000);

	init_screen();

	/* Welcome message & print information */
	puts("Welcome to My OperatingSystem\n");

	itoa(buf, memory_total / (1024 * 1024));
	puts("Memory: ");
	puts(buf);
	puts(" MB\n");

	for(;;) {
		hlt();
		itoa(buf, *counter / 100);

		buf[0] = get_keycode_ascii();
		buf[1] = '\0';
		if(buf[0] == '\n') {
			puts("\n");
			//do_command(cmd_buf);
			puts("$ ");
			cmd_buf[0] = '\0'; /* clear buf */
		} else if(buf[0] == '\t') {
			puts("    ");
		} else if(buf[0] != 0) {
			puts(buf);
			if(strlen(cmd_buf) >= 100) continue;
			if(buf[0] == '\b') {
				for(i = 0; cmd_buf[i] != 0; i++) ;
				cmd_buf[i - 1] = 0;
			} else {
				strcat(cmd_buf, buf);
			}
		}
	}

	return 0;
}

