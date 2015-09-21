
/*!
 * @file memory.c
 * @date Aug 27, 2015
 * @auther S.Shimada
 * @brief memory controll
 */

#include "memory.h"

void
memory_manager_init(struct s_memory_manager *man)
{
	man->frees    = 0;
	man->maxfrees = 0;
	man->lostsize = 0;
	man->losts    = 0;

	return;
}

/*
 * get total free memory size
 */
unsigned int
memory_manager_total(struct s_memory_manager *man)
{
	unsigned int i, t = 0;

	for(i = 0; i < man->frees; i++) {
		t += man->free[i].size;
	}

	return t;
}

unsigned int
memory_manager_alloc(
	struct s_memory_manager *man, unsigned int size)
{
	unsigned int i, a;

	for(i = 0; i < man->frees; i++) {
		if(man->free[i].size >= size) {
			a = man->free[i].size;
			man->free[i].addr += size;
			man->free[i].size -= size;
			if(man->free[i].size == 0) {
				man->frees--;
				for(; i < man->frees; i++) {
					man->free[i] = man->free[i + 1];
				}
			}
			return a;
		}
	}
	return 0;
}

int
memory_manager_free(
	struct s_memory_manager *man, unsigned int addr, unsigned int size)
{
	int i, j;

	for(i = 0; i < man->frees; i++) {
		if(man->free[i].addr > addr) {
			break;
		}
	}

	if(i > 0) {
		if(man->free[i - 1].addr + man->free[i - 1].size == addr) {
			man->free[i - 1].size += size;
			if(i < man->frees) {
				if(addr + size == man->free[i].addr) {
					man->free[i - 1].size += man->free[i].size;
					man->frees--;
					for(; i < man->frees; i++) {
						man->free[i] = man->free[i + 1];
					}
				}
			}
			return 0;
		}
	}

	if(i < man->frees) {
		if(addr + size == man->free[i].addr) {
			man->free[i].addr = addr;
			man->free[i].size += size;
			return 0;
		}
	}

	if(man->frees < MEMORY_MANAGER_FREES) {
		for(j = man->frees; j > i; j--) {
			man->free[j] = man->free[j - 1];
		}
		man->frees++;
		if(man->maxfrees < man->frees) {
			man->maxfrees = man->frees;
		}
		man->free[i].addr = addr;
		man->free[i].size = size;
		return 0;
	}

	man->losts++;
	man->lostsize += size;
	return -1;
}

unsigned int
memory_alloc_4k(struct s_memory_manager *man, unsigned int size)
{
	unsigned int a;

	size = (size + 0xfff) & 0xfffff000;
	a = memory_manager_alloc(man, size);
	return a;
}

int
memory_free_4k(struct s_memory_manager *man, unsigned int addr, unsigned int size)
{
	int i;
	size = (size + 0xfff) & 0xfffff000;
	i = memory_manager_free(man, addr, size);
	return i;
}
