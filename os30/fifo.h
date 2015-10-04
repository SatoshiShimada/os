
#define FIFO_FLAGS_OVERRUN 0x01

struct FIFO8 {
	unsigned char *buf;
	int p, q, size, free, flags;
};

void fifo8_init(struct FIFO8 *, int, unsigned char *);
int fifo8_put(struct FIFO8 *, unsigned char data);
int fifo8_get(struct FIFO8 *);
int fifo8_status(struct FIFO8 *);

