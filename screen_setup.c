
//void io_out16(int port, int data);
void out_word(int port, int data);

void set_qemuvga0_reg(int reg, int dat)
{
	out_word(0x10ce, reg);
	out_word(0x01cf, dat);
	return ;
}

void init_qemuvga0(int x, int y, int c, int flag)
{
	set_qemuvga0_reg(0x0004, 0x0000);
	set_qemuvga0_reg(0x0001, x);
	set_qemuvga0_reg(0x0002, y);
	set_qemuvga0_reg(0x0003, c);
	set_qemuvga0_reg(0x0005, 0x0000);
	set_qemuvga0_reg(0x0004, flag);

	return ;
}

