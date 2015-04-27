
/*
 * IRQ0: master first device
 * programmable interval timer
 * for 8253 timer/counter IC
 */

#include "../asm_func.h"

#define DEF_PIT_CLOCK				(1193181.67)
#define PIT_REGISTER_COUNTER0		0x0040
#define PIT_REGISTER_COUNTER1		0x0041
#define PIT_REGISTER_COUNTER2		0x0042
#define PIT_REGISTER_CONTROL		0x0043

#define DEF_PIT_COMMAND_MASK_BINCOUNT	0x01
#define DEF_PIT_COMMAND_MASK_MODE		0x0e
#define DEF_PIT_COMMAND_MASK_RL			0x30
#define DEF_PIT_COMMAND_MASK_COUNTER	0xc0

#define DEF_PIT_COMMAND_BINCOUNT_BIN	0x00
#define DEF_PIT_COMMAND_BINCOUNT_BCD	0x01

#define DEF_PIT_COMMAND_MODE_TERMINAL	0x00
#define DEF_PIT_COMMAND_MODE_PROGONE	0x02
#define DEF_PIT_COMMAND_MODE_RATEGEN	0x04
#define DEF_PIT_COMMAND_MODE_SQUAREWAVE	0x06
#define DEF_PIT_COMMAND_MODE_SOFTRIG	0x08
#define DEF_PIT_COMMAND_MODE_HARDTIG	0x0a

#define DEF_PIT_COMMAND_RL_LATCH		0x00
#define DEF_PIT_COMMAND_RL_LSBONLY		0x10
#define DEF_PIT_COMMAND_RL_MSBONLY		0x20
#define DEF_PIT_COMMAND_RL_DATA			0x30

#define DEF_PIT_COMMAND_COUNTER0		0x00
#define DEF_PIT_COMMAND_COUNTER1		0x40
#define DEF_PIT_COMMAND_COUNTER2		0x80

int set_pit_counter(int freq, unsigned char counter, unsigned char mode);

int set_pit_counter(int freq, unsigned char counter, unsigned char mode)
{
	unsigned short count;
	unsigned char  command;

	/* frequency */
	//count = (unsigned short)(DEF_PIT_CLOCK / freq);
	count = (unsigned short)(1193181 / freq);

	/* send command */
	command = mode | DEF_PIT_COMMAND_RL_DATA | counter;
	out_byte(PIT_REGISTER_CONTROL, command);

	/* send counter value */
	out_byte(PIT_REGISTER_COUNTER0, (unsigned char)(count & 0xff));
	out_byte(PIT_REGISTER_COUNTER0, (unsigned char)((count >> 8) & 0xff));

	return 0;
}

void init_pit(void)
{
	/* set counter0 [100Hz] */
	set_pit_counter(100, DEF_PIT_COMMAND_COUNTER0,
		DEF_PIT_COMMAND_MODE_SQUAREWAVE);

	return;
}
