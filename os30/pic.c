#include "asm_func.h"

#define PORT_PIC_MASTER_COMMAND	0x20
#define PORT_PIC_MASTER_STATUS	0x20
#define PORT_PIC_MASTER_DATA	0x21
#define PORT_PIC_MASTER_IMR		0x21

#define PORT_PIC_SLAVE_COMMAND	0xa0
#define PORT_PIC_SLAVE_STATUS	0xa0
#define PORT_PIC_SLAVE_DATA		0xa1
#define PORT_PIC_SLAVE_IMR		0xa1

#define PIC_IMR_MASK_IRQ0		(~0x01)
#define PIC_IMR_MASK_IRQ1		(~0x02)
#define PIC_IMR_MASK_IRQ2		(~0x04)
#define PIC_IMR_MASK_IRQ3		(~0x08)
#define PIC_IMR_MASK_IRQ4		(~0x10)
#define PIC_IMR_MASK_IRQ5		(~0x20)
#define PIC_IMR_MASK_IRQ6		(~0x40)
#define PIC_IMR_MASK_IRQ7		(~0x80)
#define PIC_IMR_MASK_IRQ_ALL	(~0xff)

/*
 * PIC IRQ and functions
 *
 * --------------------------------------
 * 0x20	master	IRQ0	timer
 * 0x21	master	IRQ1	keyboard
 * 0x22	master	IRQ2	slave PIC
 * 0x23	master	IRQ3	serial port2
 * 0x24	master	IRQ4	serial port1
 * 0x25	master	IRQ5	reserved
 * 0x26	master	IRQ6	FDD
 * 0x27	master	IRQ7	parallel
 * 0x28	slave	IRQ8	CMOS RTC
 * 0x29	slave	IRQ9	CGA
 * 0x2a	slave	IRQ10	reserved
 * 0x2b	slave	IRQ11	reserved
 * 0x2c	slave	IRQ12	AUX device
 * 0x2d	slave	IRQ13	FPU
 * 0x2e	slave	IRQ14	HDD
 * 0x2f	slave	IRQ15	reserved
 * --------------------------------------
 */
int init_pic(void)
{
	/* all interrupt clear */
	out_byte(PORT_PIC_MASTER_IMR, 0xff);
	out_byte(PORT_PIC_SLAVE_IMR, 0xff);

	/*
	 * send ICW1 to master & slave PIC command register
	 */
	out_byte(PORT_PIC_MASTER_COMMAND, 0x11);
	out_byte(PORT_PIC_SLAVE_COMMAND, 0x11);

	/*
	 * send ICW2 to master and slave PIC data register
	 */
	out_byte(PORT_PIC_MASTER_DATA, 0x20);
	out_byte(PORT_PIC_SLAVE_DATA, 0x28);

	/*
	 * send ICW3 to master and slave PIC data register
	 */
	out_byte(PORT_PIC_MASTER_DATA, 0x04);
	out_byte(PORT_PIC_SLAVE_DATA, 0x02);

	/*
	 * send ICW4 to master and slave PIC data register
	 */
	out_byte(PORT_PIC_MASTER_DATA, 0x01);
	out_byte(PORT_PIC_SLAVE_DATA, 0x01);

	/*
	 * PIC mask setting
	 * master and slave PIC
	 */
	/* enable Timer & keyboard */
	out_byte(PORT_PIC_MASTER_IMR,
		//PIC_IMR_MASK_IRQ0 & PIC_IMR_MASK_IRQ1);
		PIC_IMR_MASK_IRQ1);
	/* enable all */
	out_byte(PORT_PIC_SLAVE_IMR,
		PIC_IMR_MASK_IRQ_ALL);

	return 0;
}
