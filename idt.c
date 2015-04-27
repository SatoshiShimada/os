#include "idt.h"
#include "./interrupt_handler/interrupt_handler.h"

#define load_idt() ({ __asm__ __volatile__ ("lidt idtr"); })

#define NULL ((void *) 0)

GATE_DESCRIPTOR idt[100];
IDTR idtr;

int init_idt(void)
{
	int i;

	idtr.size = sizeof(GATE_DESCRIPTOR) * 100;
	idtr.base = (GATE_DESCRIPTOR *)idt;

	for(i = 0; i < 100; i++) {
		setupInterruptGate(i, NULL);
	}

	/* set interrupt handler */
	setupInterruptGate(0x20, (void *)interrupt_handler20); /* timer */
	setupInterruptGate(0x21, (void *)interrupt_handler21); /* keyboard */
	setupInterruptGate(0x26, (void *)interrupt_handler26); /* flopy disk controller */
	load_idt();
	return 0;
}

void setupInterruptGate(int num, void *interrupt_handler)
{
	setupGateDescriptor(num,
		(int)interrupt_handler,
		IDT_INT_SELECTOR,
		IDT_FLAGS_PRESENT | IDT_FLAGS_INTGATE_32BIT | IDT_FLAGS_DPL_LV0);
	return;
}

void setupGateDescriptor(int num, int base,
	unsigned short selector, unsigned char flags)
{
	idt[num].baseLow  = (unsigned short)(base & 0x0000ffff);
	idt[num].selector = selector;
	idt[num].reserved = 0x00;
	idt[num].flags    = flags;
	idt[num].baseHigh = (unsigned short)((base & 0xffff0000) >> 16);
	return;
}
