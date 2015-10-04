
struct MOUSE_DEC {
	unsigned char buf[3];
	unsigned char phase;
	int x, y;
	int btn;
};

void wait_KBC_sendready(void);
void init_keyboard(void);
void enable_mouse(struct MOUSE_DEC *);
int mouse_decode(struct MOUSE_DEC *, unsigned char);

