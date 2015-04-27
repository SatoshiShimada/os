
#define IDT_FLAGS_INTGATE_16BIT	0x06
#define IDT_FLAGS_TSKGATE		0x05
#define IDT_FLAGS_CALL_GATE		0x0c
#define IDT_FLAGS_INTGATE_32BIT	0x0e
#define IDT_FLAGS_TRAPGATE		0x0f
#define IDT_FLAGS_DPL_LV0		0x00
#define IDT_FLAGS_DPL_LV1		0x20
#define IDT_FLAGS_DPL_LV2		0x40
#define IDT_FLAGS_DPL_LV3		0x60
#define IDT_FLAGS_PRESENT		0x80
#define IDT_INT_SELECTOR		0x08 /* code segment */


typedef struct {
	unsigned short baseLow;
	unsigned short selector;
	unsigned char  reserved;
	unsigned char  flags;
	unsigned short baseHigh;
} __attribute__ ((packed)) GATE_DESCRIPTOR;

typedef struct {
	unsigned short  size;
	GATE_DESCRIPTOR *base;
} __attribute__ ((packed)) IDTR;

int init_idt(void);
void setupInterruptGate(int, void *);
void setupGateDescriptor(int, int, unsigned short, unsigned char);
