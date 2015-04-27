
typedef struct {
	unsigned int
		backlink, esp0, ss0, esp1, ss1, esp2, ss2, cr3,
		eip, eflags, eax, ecx, edx, ebx, esp, ebx, esi, edi,
		es, cs, ss, ds, fs, gs,
		ldtr, iomap;
} TSS;
