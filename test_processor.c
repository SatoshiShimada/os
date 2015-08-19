#include "test_processor.h"
#include "asm_func.h"
#include "print.h"

struct cpu_type cpu;

int test_processor(void)
{
	unsigned long eflags;

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

int exe_cpuid(void)
{
	unsigned char buf[100];

	if(!cpu.f_after486) {
		return -1;
	}

	cpuid_vendor_id(buf);
	memcpy(cpu.vendor_id, buf, 12);

	cpuid_processor_brand_string(buf);
	memcpy(cpu.processor_brand_string, buf, 48);

	return 0;
}
