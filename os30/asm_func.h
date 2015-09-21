
#ifndef _ASM_FUNC_H_
#define _ASM_FUNC_H_

int load_eflags(void);
void store_eflags(int);

void cache_enable(void);
void cache_disable(void);

unsigned int memory_test2(int, int);

int in_byte(int);
void out_byte(int, int);

void sti(void);
void cli(void);

void hlt(void);

void cpuid_vendor_id(unsigned char *);
void cpuid_processor_brand_string(unsigned char *);
#endif /* _ASM_FUNC_H_ */
