
static char memory_ctrl[125000];

int init_memory(void)
{
	extern unsigned int memory_total;
	int used_memory_addr;
	int i, index;

	for(i = 0; i < sizeof(memory_ctrl); i++) {
		memory_ctrl[i] = 0x00;
	}
	/* Mark used memory, BIOS and System memory using. */
	used_memory_addr = 0x400000;
	for(i = 0;
		(i / 0x1000) < sizeof(memory_ctrl) && i < used_memory_addr;
		i += 0x1000)
	{
		index = i / 0x1000 - 1;
		memory_ctrl[index / 8] |= (1 << (index % 8));
	}

	/* Mark over memory area */
	for(i = memory_total; i < sizeof(memory_ctrl); i += 0x1000) {
		index = i / 0x1000 - 1;
		memory_ctrl[index / 8] |= (1 << (index % 8));
	}

	return 0;
}

void *malloc(unsigned int size)
{
	int i;

	return (void*)0x00;
}

void free(void *p)
{
	return;
}

