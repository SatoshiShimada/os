#include "memory_test.h"
#include "asm_func.h"

unsigned int memory_test(struct cpu_type cpu, unsigned int start, unsigned int end)
{
	unsigned int i;
	unsigned int before;
	unsigned int *p;
	unsigned int pat0 = 0xaa55aa55, pat1=0x55aa55aa;

	if(cpu.f_after486) cache_disable();

	for(i = start; i <= end; i += 0x1000) {
		p = (unsigned int *)(i + 0xffc);
		before = *p;

		*p = pat0;
		*p ^= 0xffffffff;
		if(*p != pat1) {
not_be_memory:
			*p = before;
			break;
		}
		*p ^= 0xffffffff;
		if(*p != pat0) {
			goto not_be_memory;
		}
		*p = before;
	}

	if(cpu.f_after486) cache_enable();

	return i;
}
