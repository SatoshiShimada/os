#include "memory.h"

MEMORY_CONTROL memory_control;
MEMORY_CONTROL *mem = &memory_control;

void memory_control_init(void)
{
	mem->free = 0;
	mem->maxfree = 0;
	mem->lostsize = 0;
	mem->lost = 0;
	return;
}

unsigned int get_memory_free_size(void)
{
	unsigned int i, total;

	for(i = 0, total = 0; i < mem->free; i++) {
		total += mem->free_info[i].size;
	}

	return total;
}

unsigned int memory_alloc(unsigned int size)
{
	unsigned int i, addr;

	for(i = 0; i < mem->free; i++) {
		if(mem->free_info[i].size >= size) {
			addr = mem->free_info[i].address;
			mem->free_info[i].address += size;
			mem->free_info[i].size -= size;
			if(mem->free_info[i].size == 0) {
				mem->free--;
				for(; i < mem->free; i++) {
					mem->free_info[i] = mem->free_info[i + 1];
				}
			}
			return addr;
		}
	}
	return 0; /* memory allocate error */
}

int memory_free(unsigned int addr, unsigned int size)
{
	int i, j;

	for(i = 0; i < mem->free; i++) {
		if(mem->free_info[i].address > addr) {
			break;
		}
	}

	if(i > 0) {
		if(mem->free_info[i - 1].address + mem->free_info[i - 1].size
			== addr) {
			mem->free_info[i - 1].size += size;
			if(i < mem->free) {
				if(addr + size == mem->free_info[i].address) {
					mem->free_info[i - 1].size += mem->free_info[i].size;
					mem->free--;
					for(; i < mem->free; i++) {
						mem->free_info[i] = mem->free_info[i + 1];
					}
				}
			}
			return 0;
		}
	}

	if(i < mem->free) {
		if(addr + size == mem->free_info[i].address) {
			mem->free_info[i].address = addr;
			mem->free_info[i].size += size;
			return 0;
		}
	}

	if(mem->free < MEMORY_FREES) {
		for(j = mem->free; j > i; j--) {
			mem->free_info[j] = mem->free_info[j - 1];
		}
		mem->free++;
		if(mem->maxfree < mem->free) {
			mem->maxfree = mem->free;
		}
		mem->free_info[i].address = addr;
		mem->free_info[i].size = size;
		return 0;
	}

	mem->lost++;
	mem->lostsize += size;

	return -1;
}

unsigned int memory_alloc_4k(unsigned int size)
{
	unsigned int addr;

	size = (size + 0xfff) & 0xfffff000;
	addr = memory_alloc(size);
	return addr;
}

int memory_free_4k(unsigned int addr, unsigned int size)
{
	int i;

	size = (size + 0xfff) & 0xfffff000;
	i = memory_free(addr, size);
	return i;
}
