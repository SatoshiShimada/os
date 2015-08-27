
/*!
 * @file memory.h
 * @date Aug 27, 2015
 * @auther S.Shimada
 * @brief memory controll
 */


#define MEMORY_MANAGER_FREES		4090

struct s_free_info {
	unsigned int addr;
	unsigned int size;
};

struct s_memory_manager {
	int frees;
	int maxfrees;
	int lostsize;
	int losts;
	struct s_free_info free[MEMORY_MANAGER_FREES];
};

/* functions */
void
memory_manager_init(struct s_memory_manager *);
unsigned int
memory_manager_total(struct s_memory_manager *);
unsigned int
memory_manager_alloc(struct s_memory_manager *, unsigned int);
int
memory_manager_free(struct s_memory_manager *, unsigned int, unsigned int);
