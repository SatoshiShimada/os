#include "put_font.h"
#include "test_processor.h"
#include "asm_func.h"
#include "memory_test.h"
#include "print.h"
#include "idt.h"
#include "pic.h"
#include "keycode.h"
#include "./interrupt_device/interrupt.h"
#include "memory.h"
#include "fat12.h"
#include "fdd.h"

#define MEMORY_MANAGER_ADDRESS		0x003f0000

KEYCODE keycode; // interrupt_handler/keycode_encoder.c
unsigned int memory_total;

/*
 * called by asembler 
 * entry point
 */
int main(void)
{
	extern struct cpu_type cpu;
	struct s_memory_manager *memman;
	unsigned int *counter = (unsigned int *)0x1000000;
	int i;
	char buf[100];
	char cmd_buf[100];

	init_idt();
	init_pic();
	init_pit();
	/* init variavle */
	memman = (struct s_memory_manager *)MEMORY_MANAGER_ADDRESS;
	*counter = 0;
	set_keytable(KEY_EN1);
	keycode.len = 0;
	keycode.i_write = keycode.i_read = 0; /* index of write/read */

	sti(); /* enable interrupt */
	/* cpu after 486 check. if after 486 disable cache */
	/* get cpu information */
	test_processor();
	exe_cpuid();
	memory_total = memory_test(cpu, 0x00400000, 0xffffffff);

	/* memory initilize */
	memory_manager_init(memman);
	memory_manager_free(memman, 0x00001000, 0x0009e000);
	memory_manager_free(memman, 0x00400000, memory_total - 0x00400000);

	/* screen initilize */
	init_screen();

	/* Welcome message & print information */
	puts("=================================\n");
	puts("= Welcome to My OperatingSystem =\n");
	puts("=================================\n");
	puts("\n\n");

	puts("****** DEBUG INFORMATION **********************\n");
	puts("buf address: ");
	itoa(buf, (int)buf);
	puts(buf);
	puts("\n");
	puts("f_keystatus address: ");
	itoa(buf, (int)&(keycode.f_keystatus));
	puts(buf);
	puts("\n");
	puts("***********************************************\n");
	puts("\n");
	puts("*************** CPU INFORMATION ***************\n");
	puts("CPU: ");
	memcpy(buf, cpu.vendor_id, 16);
	buf[16] = '\0';
	puts(buf);
	puts("\n");
	puts(cpu.processor_brand_string);
	puts("\n");
	puts("***********************************************\n");
	puts("\n");
	puts("************** MEMORY INFORMATION *************\n");
	puts("total memory size: ");
	itoa(buf, memory_total / (1024 * 1024));
	puts(buf);
	puts("MB\nfree memory size : ");
//	/*
	itoa(buf, (unsigned int)(memory_manager_total(memman) / (1024 * 1024)));
	puts(buf);
//	*/
	puts("MB\n");
	puts("***********************************************\n");
	puts("\n\n$ ");

	cmd_buf[0] = '\0';
	for(;;) {
		hlt();
		itoa(buf, *counter / 100);

		buf[0] = get_keycode_ascii();
		buf[1] = '\0';
		if(buf[0] == '\n') {
			puts("\n");
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

