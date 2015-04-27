#define EFLAGS_AC_BIT		0x00040000

#ifndef TEST_PROCESSOR
#define TEST_PROCESSOR
struct cpu_type {
	int f_after486;
};
#endif

int test_processor(void);
