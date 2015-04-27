#include "test_processor.h"
#include "asm_func.h"

struct cpu_type cpu;

int test_processor(void)
{
	unsigned int eflags;

	eflags = load_eflags();
	eflags |= EFLAGS_AC_BIT;
	store_eflags(eflags);
	eflags = load_eflags();
	if(eflags & EFLAGS_AC_BIT) {
		cpu.f_after486 = 1;
	}
	eflags &= ~EFLAGS_AC_BIT;
	store_eflags(eflags);

	return 0;
}
