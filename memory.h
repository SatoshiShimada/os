#define MEMORY_FREES					4090

typedef struct {
	unsigned int address;
	unsigned int size;
} MEMORY_CONTROL_FREE_INFO;

typedef struct {
	int free;
	int maxfree;
	int lostsize;
	int lost;
	MEMORY_CONTROL_FREE_INFO free_info[MEMORY_FREES];
} MEMORY_CONTROL;

void memory_control_init(void);
unsigned int get_memory_free_size(void);
unsigned int memory_alloc(unsigned int);
int memory_free(unsigned int, unsigned int);
unsigned int memory_alloc_4k(unsigned int);
int memory_free_4k(unsigned int, unsigned int);
